#include <stdio.h>

// Make a simple calculator using switch statement.

int main()
{
    int options;
    printf("1. Addition\n");
    printf("2. Substraction\n");
    printf("3. Multiplication\n");
    printf("4. Divison\n");
    printf("Choose one Option from Above: ");
    scanf("%d", &options);

    float firstNumb, secondNumb;
    printf("Enter first number: ");
    scanf("%f", &firstNumb);

    printf("Enter second number: ");
    scanf("%f", &secondNumb);

    switch (options)
    {
    case 1:
        printf("The Addition is: %f", firstNumb + secondNumb);
        break;

    case 2:
        printf("The Substraction is: %f", firstNumb - secondNumb);
        break;
    case 3:
        printf("The Multiplication is: %f", firstNumb * secondNumb);
        break;
    case 4:
        if (secondNumb == 0)
            printf("Error: Division by zero is not allowed!");
        else
            printf("The Division is: %f", firstNumb / secondNumb);
        break;

    default:
        printf("Invalid Choice!");
        break;
    }
    return 0;
}
