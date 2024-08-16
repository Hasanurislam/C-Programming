#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "pp.txt"

struct Student {
    char name[50];
    int roll;
    char address[100];
};

void insertData() {
    struct Student s;
    FILE *file = fopen(FILENAME, "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]%*c", s.name);  // Read the name with spaces

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    getchar();  // Clear the newline character left by scanf

    printf("Enter Address: ");
    scanf(" %[^\n]%*c", s.address);  // Read the address with spaces

    fwrite(&s, sizeof(struct Student), 1, file);
    fclose(file);

    printf("Data inserted successfully.\n");
}

void displayData() {
    struct Student s;
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        printf("No data found.\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, file)) {
        printf("Name: %s\n", s.name);
        printf("Roll Number: %d\n", s.roll);
        printf("Address: %s\n\n", s.address);
    }

    fclose(file);
}

void searchDataByName(char *name) {
    struct Student s;
    FILE *file = fopen(FILENAME, "r");
    int found = 0;

    if (file == NULL) {
        printf("No data found.\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, file)) {
        if (strcmp(s.name, name) == 0) {
            printf("Data found:\n");
            printf("Name: %s\n", s.name);
            printf("Roll Number: %d\n", s.roll);
            printf("Address: %s\n\n", s.address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No data found with Name: %s\n", name);
    }

    fclose(file);
}

void searchDataByRoll(int roll) {
    struct Student s;
    FILE *file = fopen(FILENAME, "r");
    int found = 0;

    if (file == NULL) {
        printf("No data found.\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, file)) {
        if (s.roll == roll) {
            printf("Data found:\n");
            printf("Name: %s\n", s.name);
            printf("Roll Number: %d\n", s.roll);
            printf("Address: %s\n\n", s.address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No data found with Roll Number: %d\n", roll);
    }

    fclose(file);
}

void deleteDataByName(char *name) {
    struct Student s;
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    int found = 0;

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, file)) {
        if (strcmp(s.name, name) != 0) {
            fwrite(&s, sizeof(struct Student), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("Data with Name: %s deleted successfully.\n", name);
    } else {
        printf("No data found with Name: %s\n", name);
    }
}

void deleteDataByRoll(int roll) {
    struct Student s;
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    int found = 0;

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, file)) {
        if (s.roll != roll) {
            fwrite(&s, sizeof(struct Student), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("Data with Roll Number: %d deleted successfully.\n", roll);
    } else {
        printf("No data found with Roll Number: %d\n", roll);
    }
}

int main() {
    int choice, roll;
    char name[50];

    while (1) {
        printf("\n1. Insert Data\n");
        printf("2. Display Data\n");
        printf("3. Search Data by Name\n");
        printf("4. Search Data by Roll Number\n");
        printf("5. Delete Data by Name\n");
        printf("6. Delete Data by Roll Number\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertData();
                break;
            case 2:
                displayData();
                break;
            case 3:
                printf("Enter Name to search: ");
                scanf(" %[^\n]%*c", name);  // Read the name with spaces
                searchDataByName(name);
                break;
            case 4:
                printf("Enter Roll Number to search: ");
                scanf("%d", &roll);
                searchDataByRoll(roll);
                break;
            case 5:
                printf("Enter Name to delete: ");
                scanf(" %[^\n]%*c", name);  // Read the name with spaces
                deleteDataByName(name);
                break;
            case 6:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &roll);
                deleteDataByRoll(roll);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
