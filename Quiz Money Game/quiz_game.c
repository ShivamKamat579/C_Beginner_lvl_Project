#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Beginner Level Quiz Money Game

#define MAX_LEN 300
#define MAX_OPTION_LEN 100

int main()
{
    // File IO
    FILE *file;
    file = fopen("questions.txt", "r");
    if (!file)
    {
        printf("Error openning file :(");
        return 1;
    }

    char question[MAX_LEN];
    char options[4][MAX_OPTION_LEN];
    char correctAnswer, userAnswer;
    int questionNumber = 1;
    int totalPrice = 0;

    printf("Welcome To Quiz Money Game :}\n\n");
    //Display Question
    while (fgets(question, sizeof(question), file))
    {
        printf("Q %d: %s", questionNumber, question);

        // // Read and display 4 options
        for (int i = 0; i < 4; i++)
        {
            fgets(options[i], sizeof(options[i]), file);
            printf("%s", options[i]);
        }
        // Read the correct answer character (e.g., 'A', 'B', etc.)
        correctAnswer = fgetc(file);
        fgetc(file); //Newline after correct Answer
        fgetc(file); //Skip blank Line

        printf("Your Correct Answer (A/B/C/D) : ");
        scanf(" %c", &userAnswer);

        if (toupper(correctAnswer) == toupper(userAnswer))
        {
            totalPrice += 10000;
            printf("Correct! You Have won ₹%d so far.\n\n", totalPrice);
        }
        else
        {
            printf("Wrong! Correct Answer is %c ", correctAnswer);
            printf("You have Won %d", totalPrice);
            break;
        }
        questionNumber++;
    }
    fclose(file);
    return 0;
}