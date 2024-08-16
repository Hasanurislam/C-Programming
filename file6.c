#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    char address[100];
    int roll_no;
};

void addData();
void searchByName();
void searchByRollNo();
void displayData();

int main() {
    int choice;

    do {
        printf("\n1. Add Data\n2. Search by Name\n3. Search by Roll Number\n4. Display All Data\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // to consume the newline character left in the buffer

        switch (choice) {
            case 1:
                addData();
                break;
            case 2:
                searchByName();
                break;
            case 3:
                searchByRollNo();
                break;
            case 4:
                displayData();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void addData() {
    FILE *fptr;
    struct Student student;

    // Open file in append mode to add data
    fptr = fopen("student_data.txt", "a");

    // Check if the file opened successfully
    if (fptr == NULL) {
        printf("Error opening file!");
        return;
    }

    // Get data from user
    printf("Enter name: ");
    fgets(student.name, sizeof(student.name), stdin);
    strtok(student.name, "\n"); // remove newline character from name

    printf("Enter address: ");
    fgets(student.address, sizeof(student.address), stdin);
    strtok(student.address, "\n"); // remove newline character from address

    printf("Enter roll number: ");
    scanf("%d", &student.roll_no);
    getchar(); // to consume the newline character left in the buffer

    // Write data to file
    fprintf(fptr, "Name: %s\nAddress: %s\nRoll Number: %d\n\n", student.name, student.address, student.roll_no);

    // Close the file
    fclose(fptr);

    printf("Data saved to student_data.txt\n");
}

void searchByName() {
    FILE *fptr;
    struct Student student;
    char search_name[50];
    int found = 0;

    // Open file in read mode to search data
    fptr = fopen("student_data.txt", "r");

    // Check if the file opened successfully
    if (fptr == NULL) {
        printf("Error opening file!");
        return;
    }

    printf("Enter name to search: ");
    fgets(search_name, sizeof(search_name), stdin);
    strtok(search_name, "\n"); // remove newline character from search_name

    // Read data from file and search by name
    while (fscanf(fptr, "Name: %49[^\n]\nAddress: %99[^\n]\nRoll Number: %d\n\n", student.name, student.address, &student.roll_no) != EOF) {
        if (strcmp(student.name, search_name) == 0) {
            printf("\nData Found:\n");
            printf("Name: %s\nAddress: %s\nRoll Number: %d\n", student.name, student.address, student.roll_no);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nNo data found for the name: %s\n", search_name);
    }

    // Close the file
    fclose(fptr);
}

void searchByRollNo() {
    FILE *fptr;
    struct Student student;
    int search_roll_no;
    int found = 0;

    // Open file in read mode to search data
    fptr = fopen("student_data.txt", "r");

    // Check if the file opened successfully
    if (fptr == NULL) {
        printf("Error opening file!");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &search_roll_no);
    getchar(); // to consume the newline character left in the buffer

    // Read data from file and search by roll number
    while (fscanf(fptr, "Name: %49[^\n]\nAddress: %99[^\n]\nRoll Number: %d\n\n", student.name, student.address, &student.roll_no) != EOF) {
        if (student.roll_no == search_roll_no) {
            printf("\nData Found:\n");
            printf("Name: %s\nAddress: %s\nRoll Number: %d\n", student.name, student.address, student.roll_no);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nNo data found for the roll number: %d\n", search_roll_no);
    }

    // Close the file
    fclose(fptr);
}

void displayData() {
    FILE *fptr;
    struct Student student;

    // Open file in read mode to display data
    fptr = fopen("student_data.txt", "r");

    // Check if the file opened successfully
    if (fptr == NULL) {
        printf("Error opening file!");
        return;
    }

    printf("\nDisplaying all student data:\n");

    // Read and display all data from the file
    while (fscanf(fptr, "Name: %49[^\n]\nAddress: %99[^\n]\nRoll Number: %d\n\n", student.name, student.address, &student.roll_no) != EOF) {
        printf("\nName: %s\nAddress: %s\nRoll Number: %d\n", student.name, student.address, student.roll_no);
    }

    // Close the file
    fclose(fptr);
}