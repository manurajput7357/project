#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// Structure for student
struct Student {
    int roll;
    char name[50];
    char status[10]; // Present / Absent
};

struct Student students[MAX_STUDENTS];
int count = 0;

// Function to add student
void addStudent() {
    printf("\nEnter Roll Number: ");
    scanf("%d", &students[count].roll);

    printf("Enter Name: ");
    scanf("%s", students[count].name);

    strcpy(students[count].status, "Absent"); // default

    count++;
    printf("\nStudent Added Successfully!\n");
}

// Mark attendance
void markAttendance() {
    int roll, found = 0;
    printf("\nEnter Roll Number to Mark Attendance: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("Mark (1) Present or (2) Absent: ");
            int choice;
            scanf("%d", &choice);

            if (choice == 1)
                strcpy(students[i].status, "Present");
            else
                strcpy(students[i].status, "Absent");

            printf("Attendance Updated!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Not Found!\n");
}

// Display attendance
void displayAttendance() {
    printf("\n--- Daily Attendance ---\n");
    printf("Roll\tName\t\tStatus\n");

    for (int i = 0; i < count; i++) {
        printf("%d\t%-10s\t%s\n", students[i].roll, students[i].name, students[i].status);
    }
}

// Save to file
void saveToFile() {
    FILE *fp = fopen("attendance.txt", "w");

    if (fp == NULL) {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %s\n", students[i].roll, students[i].name, students[i].status);
    }

    fclose(fp);
    printf("\nAttendance Saved to 'attendance.txt' Successfully!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n====== Attendance Management System ======\n");
        printf("1. Add Student\n");
        printf("2. Mark Attendance\n");
        printf("3. Display Attendance\n");
        printf("4. Save to File\n");
        printf("5. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: markAttendance(); break;
            case 3: displayAttendance(); break;
            case 4: saveToFile(); break;
            case 5: 
                printf("Exiting... Thank you!\n");
                exit(0);
            default: 
                printf("Invalid Choice! Try Again.\n");
        }
    }

    return 0;
}
