/******************************
 * PixelWeaver - BMP Editor
 * Language: ANSI C
 * Author: You!
 ******************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************** Structs ***************/

// RGB pixel structure
typedef struct {
    unsigned char r, g, b;
} Pixel;

// Image metadata and pixel grid
typedef struct {
    int width, height;
    Pixel **pixels;
} Image;

// BMP file header (packed to avoid padding)
#pragma pack(push, 1)
typedef struct {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
    unsigned int header_size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int image_size;
    int x_ppm;
    int y_ppm;
    unsigned int clr_used;
    unsigned int clr_important;
} BMPHeader;
#pragma pack(pop)

/*************** BMP Loader ***************/

// Load 24-bit BMP image
Image* load_bmp(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("File not found: %s\n", filename);
        return NULL;
    }

    BMPHeader header;
    fread(&header, sizeof(BMPHeader), 1, fp);

    if (header.type != 0x4D42 || header.bpp != 24) {
        printf("Invalid BMP format. Only 24-bit BMP supported.\n");
        fclose(fp);
        return NULL;
    }

    Image *img = malloc(sizeof(Image));
    img->width = header.width;
    img->height = header.height;

    img->pixels = malloc(sizeof(Pixel*) * img->height);
    for (int i = 0; i < img->height; i++)
        img->pixels[i] = malloc(sizeof(Pixel) * img->width);

    fseek(fp, header.offset, SEEK_SET);
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            fread(&img->pixels[i][j], sizeof(Pixel), 1, fp);
        }
    }

    fclose(fp);
    return img;
}

/*************** BMP Saver ***************/

// Save BMP image to new file
void save_bmp(const char *filename, Image *img) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Could not write file.\n");
        return;
    }

    BMPHeader header = {0};
    header.type = 0x4D42;
    header.offset = sizeof(BMPHeader);
    header.header_size = 40;
    header.width = img->width;
    header.height = img->height;
    header.planes = 1;
    header.bpp = 24;
    header.image_size = img->width * img->height * 3;
    header.size = header.offset + header.image_size;

    fwrite(&header, sizeof(BMPHeader), 1, fp);
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            fwrite(&img->pixels[i][j], sizeof(Pixel), 1, fp);
        }
    }

    fclose(fp);
}

/*************** Image Processing ***************/

// Convert image to grayscale
void grayscale(Image *img) {
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            unsigned char avg = (img->pixels[i][j].r + img->pixels[i][j].g + img->pixels[i][j].b) / 3;
            img->pixels[i][j].r = img->pixels[i][j].g = img->pixels[i][j].b = avg;
        }
    }
}

// Flip image horizontally
void flip_horizontal(Image *img) {
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width / 2; j++) {
            Pixel tmp = img->pixels[i][j];
            img->pixels[i][j] = img->pixels[i][img->width - j - 1];
            img->pixels[i][img->width - j - 1] = tmp;
        }
    }
}

// Flip image vertically
void flip_vertical(Image *img) {
    for (int i = 0; i < img->height / 2; i++) {
        Pixel *tmp = img->pixels[i];
        img->pixels[i] = img->pixels[img->height - i - 1];
        img->pixels[img->height - i - 1] = tmp;
    }
}

// Resize image using nearest-neighbor scaling
Image* resize(Image *img, float scale) {
    int new_width = img->width * scale;
    int new_height = img->height * scale;

    Image *new_img = malloc(sizeof(Image));
    new_img->width = new_width;
    new_img->height = new_height;
    new_img->pixels = malloc(sizeof(Pixel*) * new_height);

    for (int i = 0; i < new_height; i++)
        new_img->pixels[i] = malloc(sizeof(Pixel) * new_width);

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            new_img->pixels[i][j] = img->pixels[(int)(i / scale)][(int)(j / scale)];
        }
    }

    return new_img;
}

/*************** Memory Management ***************/

void free_image(Image *img) {
    for (int i = 0; i < img->height; i++)
        free(img->pixels[i]);
    free(img->pixels);
    free(img);
}

/*************** Main Menu ***************/

int main() {
    char filename[100];
    printf("🎨 Enter BMP file name: ");
    scanf("%s", filename);

    Image *img = load_bmp(filename);
    if (!img) {
        printf("Failed to load image.\n");
        return 1;
    }

    int choice;
    do {
        printf("\n🧾 PixelWeaver Menu\n");
        printf("1. Convert to Grayscale\n");
        printf("2. Flip Horizontally\n");
        printf("3. Flip Vertically\n");
        printf("4. Resize Image\n");
        printf("5. Save Image\n");
        printf("0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 1) grayscale(img);
        else if (choice == 2) flip_horizontal(img);
        else if (choice == 3) flip_vertical(img);
        else if (choice == 4) {
            float scale;
            printf("Scale factor (e.g., 0.5 or 2.0): ");
            scanf("%f", &scale);
            Image *new_img = resize(img, scale);
            free_image(img);
            img = new_img;
        }
        else if (choice == 5) {
            char outname[100];
            printf("Filename to save: ");
            scanf("%s", outname);
            save_bmp(outname, img);
            printf("✅ Saved successfully.\n");
        }
    } while (choice != 0);

    free_image(img);
    printf("👋 Goodbye!\n");
    return 0;
}