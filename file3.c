#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "hasanur.txt" // Changed filename to hasanur.txt
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 200

typedef struct {
    char name[MAX_NAME_LENGTH];
    int roll;
    char address[MAX_ADDRESS_LENGTH];
} Student;

void insertData();
void searchData();
void displayData();
void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    while (1) {
        printf("Menu:\n");
        printf("1. Insert data to file\n");
        printf("2. Search data by name\n");
        printf("3. Display the data\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from buffer

        switch (choice) {
            case 1:
                insertData();
                break;
            case 2:
                searchData();
                break;
            case 3:
                displayData();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void insertData() {
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Student student;
    printf("Enter Name: ");
    fgets(student.name, MAX_NAME_LENGTH, stdin);
    student.name[strcspn(student.name, "\n")] = 0; // Remove newline character

    printf("Enter Roll: ");
    scanf("%d", &student.roll);
    getchar(); // Clear newline character from buffer

    printf("Enter Address: ");
    fgets(student.address, MAX_ADDRESS_LENGTH, stdin);
    student.address[strcspn(student.address, "\n")] = 0; // Remove newline character

    fwrite(&student, sizeof(Student), 1, file);
    fclose(file);

    printf("Data inserted successfully.\n");
}

void searchData() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char searchName[MAX_NAME_LENGTH];
    printf("Enter the name to search: ");
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = 0; // Remove newline character

    Student student;
    int found = 0;
    while (fread(&student, sizeof(Student), 1, file)) {
        if (strcmp(student.name, searchName) == 0) {
            printf("Name: %s\n", student.name);
            printf("Roll: %d\n", student.roll);
            printf("Address: %s\n", student.address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No data found for name: %s\n", searchName);
    }

    fclose(file);
}

void displayData() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Student student;
    while (fread(&student, sizeof(Student), 1, file)) {
        printf("Name: %s\n", student.name);
        printf("Roll: %d\n", student.roll);
        printf("Address: %s\n", student.address);
        printf("---------------------------\n");
    }

    fclose(file);
}
