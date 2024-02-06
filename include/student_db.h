//
// Created by Cristian Soare on 2/6/2024.
//

#ifndef STUDENT_DB_H
#define STUDENT_DB_H

// Structure definition for student
typedef struct student {
    int student_id;
    char forename[20];
    char surname[20];
    struct enrolled_courses {
        char module_code[10];
        char module_name[50];
        float module_grade;
    } sub[3];
    float semester_average;
    float semester_percentage;
} student;

// Function prototypes
void editRecords(int option);
void displayRecords(int option);
void totalRecords();
void updateRecords();
void checkDB(FILE *file);
void deleteRecords();
void sortRecords();

#endif /* STUDENT_DB_H */
