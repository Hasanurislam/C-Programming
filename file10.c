#include <stdio.h>
#include <stdlib.h>

#define FILENAME "data.txt"

struct Student {
    char name[50];
    int roll;
    char address[100];
};

void insertData() {
    struct Student s;
    FILE *file = fopen(FILENAME, "a+b");  // Open for appending in binary mode

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
    FILE *file = fopen(FILENAME, "rb");  // Open for reading in binary mode

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

int main() {
    int choice;

    while (1) {
        printf("\n1. Insert Data\n");
        printf("2. Display Data\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear the newline character left by scanf

        switch (choice) {
            case 1:
                insertData();
                break;
            case 2:
                displayData();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
