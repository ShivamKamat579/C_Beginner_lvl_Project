#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HABIT 10
#define TOTAL_DAYS 7

char habitNames[MAX_HABIT][30];         // Store names of habit
int totalHabits = 0;                    // Total number of habits
int habitStatus[MAX_HABIT][TOTAL_DAYS]; // 1 = done, 0 = not done

// Function Declarations
void loadDataFromFile();
void saveDataToFile();
void addNewHabit();
void markTodayHabits();
void showWeeklyReport();
void clearInputBuffer();

int main()
{
    int userChoice;
    loadDataFromFile(); // Load previous data if available

    do
    {
        printf("\n===== Simple Habit Tracker =====\n");
        printf("1. Add a New Habit\n");
        printf("2. Log Today's Habits\n");
        printf("3. Show Weekly Report\n");
        printf("4. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);
        clearInputBuffer();

        switch (userChoice)
        {
        case 1:
            addNewHabit();
            break;
        case 2:
            markTodayHabits();
            break;
        case 3:
            showWeeklyReport();
            break;
        case 4:
            saveDataToFile();
            printf("Goodbye! Your data is saved.\n");
            break;
        default:
            printf("Invalid option. Please choose 1–4.\n");
        }

    } while (userChoice != 4);

    return 0;
}

// Function to add new habits
void addNewHabit()
{
    if (totalHabits >= MAX_HABIT)
    {
        printf("Habit limit reached!\n");
        return;
    }
    printf("Enter the name of your new habit: ");
    fgets(habitNames[totalHabits], sizeof(habitNames[totalHabits]), stdin);
    habitNames[totalHabits][strcspn(habitNames[totalHabits], "\n")] = '\0';

    // Initialize habit tracker for this habit to 0 (not done)
    for (int day = 0; day < TOTAL_DAYS; day++)
    {
        habitStatus[totalHabits][day] = 0;
    }

    totalHabits++;
    printf("Habit added successfully!\n");
}
// Function to mark today's habit completion
void markTodayHabits()
{
    int today;
    printf("Which day is today? (1=Mon,...,7=Sun): ");
    scanf("%d", &today);
    clearInputBuffer();

    if (today < 1 || today > 7)
    {
        printf("Invalid day number. Use 1 to 7.\n");
        return;
    }

    for (int i = 0; i < totalHabits; i++)
    {
        char done;
        printf("Did you do '%s'? (y/n): ", habitNames[i]);
        scanf(" %c", &done);

        if (done == 'y' || done == 'Y')
        {
            habitStatus[i][today - 1] = 1;
        }
        else
        {
            habitStatus[i][today - 1] = 0;
        }
    }
    printf("Today's habits logged!\n");
}

// Function to show weekly habit report
void showWeeklyReport()
{
    printf("\n Weekly Habit Report:\n");

    for (int i = 0; i < totalHabits; i++)
    {
        int completedDays = 0;
        printf("\nHabit: %s\n", habitNames[i]);
        printf("Progress: ");

        for (int day = 0; day < TOTAL_DAYS; day++)
        {
            printf("%d ", habitStatus[i][day]);
            completedDays += habitStatus[i][day];
        }
        printf("\n Done %d out of 7 days\n", completedDays);
    }
}

// Function to save data into file
void saveDataToFile()
{
    FILE *file = fopen("habit.txt", "w");
    if (file == NULL)
    {
        printf("Failed to save data.\n");
        return;
    }
    fprintf(file, "%d\n", totalHabits);

    for (int i = 0; i < totalHabits; i++)
    {
        fprintf(file, "%s\n", habitNames[i]);
        for (int day = 0; day < TOTAL_DAYS; day++)
        {
            fprintf(file, "%d ", habitStatus[i][day]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Function to load data from file
void loadDataFromFile()
{
    FILE *file = fopen("habits.txt", "r");
    if (file == NULL)
        return;

    fscanf(file, "%d\n", &totalHabits);

    for (int i = 0; i < totalHabits; i++)
    {
        fgets(habitNames[i], sizeof(habitNames[i]), file);
        habitNames[i][strcspn(habitNames[i], "\n")] = '\0';

        for (int day = 0; day < TOTAL_DAYS; day++)
        {
            fscanf(file, "%d", &habitStatus[i][day]);
        }
    }
    fclose(file);
}

// Function to clear leftover input (to avoid scanf issues)
void clearInputBuffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
        
}