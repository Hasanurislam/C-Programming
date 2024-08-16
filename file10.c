#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.dat"
#define TEMP_FILENAME "temp.dat"  // Temporary file for deletion
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 200
#define PASSWORD "admin123"       // Define the password

typedef struct {
    char name[MAX_NAME_LENGTH];
    int roll;
    char address[MAX_ADDRESS_LENGTH];
} Student;

void insertData();
void searchDataByName();
void searchDataByRoll();
void deleteDataByRoll();
void deleteDataByName();
void displayData();
void menu();
int authenticate();  // Function to handle password authentication

int main() {
    if (authenticate()) {
        menu();
    } else {
        printf("Incorrect password. Exiting...\n");
        exit(0);
    }
    return 0;
}

int authenticate() {
    char inputPassword[50];
    printf("Enter password to access the system: ");
    fgets(inputPassword, 50, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = 0;  // Remove newline character

    // Check if the entered password matches the predefined password
    if (strcmp(inputPassword, PASSWORD) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void menu() {
    int choice;
    while (1) {
        printf("Menu:\n");
        printf("1. Insert data to file\n");
        printf("2. Search data by name\n");
        printf("3. Search data by roll number\n");
        printf("4. Delete data by roll number\n");
        printf("5. Delete data by name\n");
        printf("6. Display the data\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from buffer

        switch (choice) {
            case 1:
                insertData();
                break;
            case 2:
                searchDataByName();
                break;
            case 3:
                searchDataByRoll();
                break;
            case 4:
                deleteDataByRoll();
                break;
            case 5:
                deleteDataByName();
                break;
            case 6:
                displayData();
                break;
            case 7:
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

void searchDataByName() {
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

void searchDataByRoll() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int searchRoll;
    printf("Enter the roll number to search: ");
    scanf("%d", &searchRoll);
    getchar(); // Clear newline character from buffer

    Student student;
    int found = 0;
    while (fread(&student, sizeof(Student), 1, file)) {
        if (student.roll == searchRoll) {
            printf("Name: %s\n", student.name);
            printf("Roll: %d\n", student.roll);
            printf("Address: %s\n", student.address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No data found for roll number: %d\n", searchRoll);
    }

    fclose(file);
}

void deleteDataByRoll() {
    FILE *file = fopen(FILENAME, "rb");
    FILE *tempFile = fopen(TEMP_FILENAME, "wb");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int deleteRoll;
    printf("Enter the roll number to delete: ");
    scanf("%d", &deleteRoll);
    getchar(); // Clear newline character from buffer

    Student student;
    int found = 0;
    while (fread(&student, sizeof(Student), 1, file)) {
        if (student.roll == deleteRoll) {
            printf("Deleting record:\n");
            printf("Name: %s\n", student.name);
            printf("Roll: %d\n", student.roll);
            printf("Address: %s\n", student.address);
            found = 1;
        } else {
            fwrite(&student, sizeof(Student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILENAME);
        rename(TEMP_FILENAME, FILENAME);
        printf("Record deleted successfully.\n");
    } else {
        remove(TEMP_FILENAME);
        printf("No record found with roll number: %d\n", deleteRoll);
    }
}

void deleteDataByName() {
    FILE *file = fopen(FILENAME, "rb");
    FILE *tempFile = fopen(TEMP_FILENAME, "wb");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char deleteName[MAX_NAME_LENGTH];
    printf("Enter the name to delete: ");
    fgets(deleteName, MAX_NAME_LENGTH, stdin);
    deleteName[strcspn(deleteName, "\n")] = 0; // Remove newline character

    Student student;
    int found = 0;
    while (fread(&student, sizeof(Student), 1, file)) {
        if (strcmp(student.name, deleteName) == 0) {
            printf("Deleting record:\n");
            printf("Name: %s\n", student.name);
            printf("Roll: %d\n", student.roll);
            printf("Address: %s\n", student.address);
            found = 1;
        } else {
            fwrite(&student, sizeof(Student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILENAME);
        rename(TEMP_FILENAME, FILENAME);
        printf("Record deleted successfully.\n");
    } else {
        remove(TEMP_FILENAME);
        printf("No record found with name: %s\n", deleteName);
    }
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