#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll_no;
    char name[50];
    float marks;
};

// Add student
void addStudent(struct Student s[], int *count) {
    printf("Enter Roll No: ");
    scanf("%d", &s[*count].roll_no);
    printf("Enter Name: ");
    scanf("%s", s[*count].name);
    printf("Enter Marks: ");
    scanf("%f", &s[*count].marks);
    (*count)++;
    printf("Student added successfully!\n");
}

// Display all students
void displayStudents(struct Student s[], int count) {
    printf("\n--- Student Records ---\n");
    for(int i=0; i<count; i++) {
        printf("Roll No: %d | Name: %s | Marks: %.2f\n", s[i].roll_no, s[i].name, s[i].marks);
    }
}

// Search student
void searchStudent(struct Student s[], int count, int roll) {
    for(int i=0; i<count; i++) {
        if(s[i].roll_no == roll) {
            printf("Found: Roll No: %d | Name: %s | Marks: %.2f\n", s[i].roll_no, s[i].name, s[i].marks);
            return;
        }
    }
    printf("Student not found!\n");
}

// Update student
void updateStudent(struct Student s[], int count, int roll) {
    for(int i=0; i<count; i++) {
        if(s[i].roll_no == roll) {
            printf("Enter new name: ");
            scanf("%s", s[i].name);
            printf("Enter new marks: ");
            scanf("%f", &s[i].marks);
            printf("Record updated!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

// Delete student
void deleteStudent(struct Student s[], int *count, int roll) {
    for(int i=0; i<*count; i++) {
        if(s[i].roll_no == roll) {
            for(int j=i; j<*count-1; j++) {
                s[j] = s[j+1];
            }
            (*count)--;
            printf("Record deleted!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

// Save records to file
void saveToFile(struct Student s[], int count) {
    FILE *fp = fopen("students.txt", "w");
    for(int i=0; i<count; i++) {
        fprintf(fp, "%d %s %.2f\n", s[i].roll_no, s[i].name, s[i].marks);
    }
    fclose(fp);
    printf("Records saved to file!\n");
}

// Load records from file
void loadFromFile(struct Student s[], int *count) {
    FILE *fp = fopen("students.txt", "r");
    if(fp == NULL) {
        printf("No file found, starting fresh.\n");
        return;
    }
    while(fscanf(fp, "%d %s %f", &s[*count].roll_no, s[*count].name, &s[*count].marks) != EOF) {
        (*count)++;
    }
    fclose(fp);
    printf("Records loaded from file!\n");
}

int main() {
    struct Student students[100];
    int count = 0, choice, roll;

    // Load records from file at startup
    loadFromFile(students, &count);

    while(1) {
        printf("\n--- Student Record System ---\n");
        printf("1. Add Student\n2. Display Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Save & Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(students, &count); break;
            case 2: displayStudents(students, count); break;
            case 3:
                printf("Enter Roll No to search: ");
                scanf("%d", &roll);
                searchStudent(students, count, roll);
                break;
            case 4:
                printf("Enter Roll No to update: ");
                scanf("%d", &roll);
                updateStudent(students, count, roll);
                break;
            case 5:
                printf("Enter Roll No to delete: ");
                scanf("%d", &roll);
                deleteStudent(students, &count, roll);
                break;
            case 6:
                saveToFile(students, count);
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
