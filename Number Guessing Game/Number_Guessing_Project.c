#include<stdio.h>
#include<stdlib.h> //for rand() - random number generator
#include<time.h> // for time(Null)

int main(){
    int random, guess;
    int no_of_guess = 0;
    srand(time(NULL));
    //Greeting
    printf("Welcome to Our Number Guessing Game!\n");
    random = rand() % 100 + 1; //Important line - keep numbers 1 - 100

    do
    {
        //User Input
        printf("Enter the Number for Guessing (1 - 100): ");
        scanf("%d", &guess);
        no_of_guess++;

        //checking the guess based on input
        if (guess > random)
        {
             printf("Too high! Try guessing a smaller number.\n");
        } 
        else if (guess < random)
        {
             printf("Too low! Try guessing a larger number.\n");
        }
        else
        {
            printf("🎉 Congratulations! You guessed the number in %d attempts.\n", no_of_guess);
        }
        
        //Ending Loop by guessing correctly!
    } while (guess !=random);
    printf("👋 Thanks for playing. Goodbye!\n");
    printf("Coding by SHIVAM");
    return 0;
    
}