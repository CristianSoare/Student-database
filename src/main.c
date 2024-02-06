//
// Created by Cristian Soare on 2/4/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_FILE "studentdb.txt"

typedef struct student{
    int student_id;
    char forename[20];
    char surname[20];
    struct enrolled_courses{
        char module_code[10];
        char module_name[50];
        float module_grade;
    }sub[3];
    float semester_average;
    float semester_percentage;
}student;

void editRecords(int option);
void displayRecords(int option);
void totalRecords();
void updateRecords();
void checkDB(FILE *file);
void deleteRecords();
void sortRecords();

int main(){
    int choice;
    do{
        printf("\n1.CREATE");
        printf("\n2.DISPLAY");
        printf("\n3.APPEND");
        printf("\n4.NO RECORDS");
        printf("\n5.SEARCH");
        printf("\n6.UPDATE");
        printf("\n7.DELETE");
        printf("\n8.SORT");
        printf("\n0.EXIT");
        printf("\n>>");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                system("cls");
                editRecords(1);
                break;
            case 2:
                system("cls");
                displayRecords(1);
                break;
            case 3:
                system("cls");
                editRecords(2);
                break;
            case 4:
                system("cls");
                totalRecords();
                break;
            case 5:
                system("cls");
                displayRecords(2);
                break;
            case 6:
                system("cls");
                updateRecords();
                break;
            case 7:
                system("cls");
                deleteRecords();
                break;
            case 8:
                system("cls");
                sortRecords();
                break;
        }
    }while(choice!=0);

    return 0;
}


void editRecords(int option){
    FILE *file;
    char *editOption= option==1?"w":"a";
    file=fopen(DATABASE_FILE, editOption);
    student *s;
    int num_records, i, j;
    printf("Enter how many student records you would like to create?\n>>");
    scanf("%d",&num_records);
    s=(student*)calloc(num_records,sizeof(student));
    for (i = 0; i < num_records; ++i) {
        float total=0.0;
        printf("Enter student ID: ");
        scanf("%d",&s[i].student_id);
        printf("Enter student forename: ");
        scanf(" %19s",&s[i].forename);
        printf("Enter student surname: ");
        scanf(" %19s",&s[i].surname);
        for (j = 0; j < 3; ++j) {
            printf("Enter module code of subject %d: ",j+1);
            scanf(" %9s",&s[i].sub[j].module_code);
            printf("Enter module name of subject %d: ",j+1);
            scanf(" %[^\n]",&s[i].sub[j].module_name);
            printf("Enter module grade of subject %d: ",j+1);
            scanf("%f",&s[i].sub[j].module_grade);
            total += s[i].sub[j].module_grade;
        }
        s[i].semester_average=total/3;
        s[i].semester_percentage=s[i].semester_average/20.0*100.0;
        fwrite(&s[i],sizeof(student),1,file);
    }
    fclose(file);
}

void displayRecords(int option){
    student s;
    FILE *file;
    file=fopen(DATABASE_FILE,"r");
    checkDB(file);
    int id;
    int found=0;
    if(option==2){
        printf("\nEnter ID to search records: ");
        scanf("%d",&id);
    }
    while (fread(&s,sizeof(student),1,file)){
        if(option==1 || (option==2 && s.student_id==id)){
            found = 1;
            printf("\n[+]%d -- %s %s",s.student_id,s.forename,s.surname);
            for (int j = 0; j < 3; ++j) {
                printf("\n--%s",s.sub[j].module_code);
                printf("\n      MODULE NAME: %s",s.sub[j].module_name);
                printf("\n      GRADE: %.2f",s.sub[j].module_grade);
            }
            printf("\nSEMESTER GRADE : %.2f/20 %.2f\n",s.semester_average,s.semester_percentage);
        }
    }
    if(!found&&option==2){
        printf("\nRECORD NOT FOUND\n");
    }
    fclose(file);
}

void totalRecords(){
    FILE *file;
    file = fopen(DATABASE_FILE,"r");
    fseek(file,0,SEEK_END);
    int num = ftell(file)/sizeof(student);
    printf("\nNUMBER OF RECORDS : %d\n",num);
    fclose(file);
}

void checkDB(FILE *file) {
    if (file == NULL) {
        char choice;
        printf("ERROR: Database file not found, would you like to create one?(Y/n)\n>>");
        scanf(" %s", &choice);
        if (choice == 'y' || choice == 'Y' || choice == '\n') {
            file = fopen(DATABASE_FILE, "w");
            printf("OK");
        } else if (choice == 'n' || choice == 'N') {
            printf("OK");
            exit(0);
        } else {
            printf("Invalid choice");
            return;
        }
    }
}

void updateRecords() {
    student s;
    FILE *file, *tempFile;
    file = fopen(DATABASE_FILE, "r");
    tempFile = fopen("temp.txt","w");
    checkDB(file);
    int id;
    int found = 0;
    printf("\nEnter ID to update records: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(student), 1, file)) {
        if (s.student_id == id) {
            found = 1;
            float total=0;
            int choice;
            printf("What data would you like to update?\n");
            printf("\n1.ID");
            printf("\n2.FORENAME");
            printf("\n3.SURNAME");
            printf("\n4.MODULES AND GRADES");
            printf("\n5.ALL");
            printf("\n>>");
            scanf("%d",&choice);
            switch (choice) {
                case 1:
                    printf("Enter new student ID: ");
                    scanf("%d",&s.student_id);
                    fwrite(&s,sizeof(student),1,tempFile);
                    break;
                case 2:
                    printf("Enter new student forename: ");
                    scanf(" %19s",&s.forename);
                    fwrite(&s,sizeof(student),1,tempFile);
                    break;
                case 3:
                    printf("Enter student surname: ");
                    scanf(" %19s",&s.surname);
                    fwrite(&s,sizeof(student),1,tempFile);
                    break;
                case 4:
                    for (int j = 0; j < 3; ++j) {
                        printf("Enter new module code of subject %d: ",j+1);
                        scanf(" %9s",&s.sub[j].module_code);
                        printf("Enter new module name of subject %d: ",j+1);
                        scanf(" %[^\n]",&s.sub[j].module_name);
                        printf("Enter new module grade of subject %d: ",j+1);
                        scanf("%f",&s.sub[j].module_grade);
                        total += s.sub[j].module_grade;
                    }
                    s.semester_average=total/3;
                    s.semester_percentage=s.semester_average/20.0*100.0;
                    fwrite(&s,sizeof(student),1,tempFile);
                    break;
                case 5:
                    printf("Enter new student ID: ");
                    scanf("%d",&s.student_id);
                    printf("Enter new student forename: ");
                    scanf(" %19s",&s.forename);
                    printf("Enter new student surname: ");
                    scanf(" %19s",&s.surname);
                    for (int j = 0; j < 3; ++j) {
                        printf("Enter new module code of subject %d: ",j+1);
                        scanf(" %9s",&s.sub[j].module_code);
                        printf("Enter new module name of subject %d: ",j+1);
                        scanf(" %[^\n]",&s.sub[j].module_name);
                        printf("Enter new module grade of subject %d: ",j+1);
                        scanf("%f",&s.sub[j].module_grade);
                        total += s.sub[j].module_grade;
                    }
                    s.semester_average=total/3;
                    s.semester_percentage=s.semester_average/20.0*100.0;
                    fwrite(&s,sizeof(student),1,tempFile);
                    break;
                default:
                    printf("Invalid choice");
                    break;
            }
        } else {fwrite(&s,sizeof(student),1,tempFile);}
    }
    if (!found) {
        printf("\nRECORD NOT FOUND\n");
    } else {
        fclose(file);
        fclose(tempFile);
        tempFile=fopen("temp.txt","r");
        file= fopen(DATABASE_FILE,"w");
        while (fread(&s, sizeof(student),1,tempFile)){
            fwrite(&s, sizeof(student),1,file);
        }
        printf("\nOK\n");
    }
    fclose(file);
}

void deleteRecords(){
    student s;
    FILE *file;
    file = fopen(DATABASE_FILE, "r");
    FILE *tempFile;
    tempFile = fopen("temp.txt","w");
    checkDB(file);
    int id;
    int found = 0;
    printf("\nEnter ID to delete record: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(student), 1, file)) {
        if (s.student_id == id) {
            found=1;
        }else{
            fwrite(&s,sizeof(student),1,tempFile);
        }
    }
    if (!found) {
        printf("\nRECORD NOT FOUND\n");
    } else {
        fclose(file);
        fclose(tempFile);
        tempFile=fopen("temp.txt","r");
        file= fopen(DATABASE_FILE,"w");
        while (fread(&s, sizeof(student),1,tempFile)){
            fwrite(&s, sizeof(student),1,file);
        }
        printf("\nOK\n");
    }
    fclose(file);
}

void sortRecords() {
    student *s, s1;
    char sortOption1, sortOption2;
    printf("Sort by average grade or surname?(g/s)\n>>");
    scanf(" %c",&sortOption1);
    if(sortOption1=='g' || sortOption1=='G'){
        printf("Sort on display or save in file?(d/s)\n>>");
        scanf(" %c",&sortOption2);
        FILE *file = fopen(DATABASE_FILE,"r");
        fseek(file,0,SEEK_END);
        int num = ftell(file)/sizeof(student);
        s = (student*)calloc(num, sizeof(student));
        rewind(file);
        for (int i = 0; i < num; ++i) {
            fread(&s[i],sizeof(student),1,file);
        }
        fclose(file);
        for (int i = 0; i < num; ++i) {
            for (int j = i+1; j < num; ++j) {
                if(s[i].semester_average<s[j].semester_average){
                    s1=s[i];
                    s[i]=s[j];
                    s[j]=s1;
                }
            }
        }
        if (sortOption2 == 's' || sortOption2 == 'S') {
            file= fopen(DATABASE_FILE,"w");
        }
        for (int i = 0; i < num; ++i) {
            printf("\n[+]%d -- %s %s", s[i].student_id, s[i].forename, s[i].surname);
            for (int j = 0; j < 3; ++j) {
                printf("\n--%s", s[i].sub[j].module_code);
                printf("\n      MODULE NAME: %s", s[i].sub[j].module_name);
                printf("\n      GRADE: %.2f", s[i].sub[j].module_grade);
            }
            printf("\nSEMESTER GRADE : %.2f/20 %.2f\n", s[i].semester_average, s[i].semester_percentage);
            if (sortOption2 == 's' || sortOption2 == 'S') {
                fwrite(&s[i], sizeof(student), 1, file);
            }
        }
        if (sortOption2 == 's' || sortOption2 == 'S') {
            fclose(file);
        }
    }
    else if(sortOption1=='s' || sortOption1=='S'){
        printf("Sort on display or save in file?(d/s)\n>>");
        scanf(" %c",&sortOption2);
        FILE *file = fopen(DATABASE_FILE,"r");
        fseek(file,0,SEEK_END);
        int num = ftell(file)/sizeof(student);
        s = (student*)calloc(num, sizeof(student));
        rewind(file);
        for (int i = 0; i < num; ++i) {
            fread(&s[i],sizeof(student),1,file);
        }
        fclose(file);
        for (int i = 0; i < num; ++i) {
            for (int j = i+1; j < num; ++j) {
                if(strcmp(s[i].surname,s[j].surname)>0){
                    s1=s[i];
                    s[i]=s[j];
                    s[j]=s1;
                }
            }
        }
        if (sortOption2 == 's' || sortOption2 == 'S') {
            file= fopen(DATABASE_FILE,"w");
        }
        for (int i = 0; i < num; ++i) {
            printf("\n[+]%d -- %s %s", s[i].student_id, s[i].forename, s[i].surname);
            for (int j = 0; j < 3; ++j) {
                printf("\n--%s", s[i].sub[j].module_code);
                printf("\n      MODULE NAME: %s", s[i].sub[j].module_name);
                printf("\n      GRADE: %.2f", s[i].sub[j].module_grade);
            }
            printf("\nSEMESTER GRADE : %.2f/20 %.2f\n", s[i].semester_average, s[i].semester_percentage);
            if (sortOption2 == 's' || sortOption2 == 'S') {
                fwrite(&s[i], sizeof(student), 1, file);
            }
        }
        if (sortOption2 == 's' || sortOption2 == 'S') {
            fclose(file);
        }
    } else {
        printf("Invalid choice");
        return;
    }
}