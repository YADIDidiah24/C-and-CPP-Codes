#include "ComputeGPA.h"

typedef struct {
    char course_name[40];
    char course_id[6];
    int course_credit;
    char course_mark[2];
} courses_t;

typedef struct {
    int id;
    char name[40];
    float GPA;
    int NumberOfCourse;
    courses_t* courses;
} student_t;

student_t student[3];

int Totalstudent = 0;

// Function prototype declaration for addCourse
void addCourse(int Std_id, int numberOfCourses);

// Function to add a new student
void add_new_student() {
    // Prompt the user to enter the student's ID
    printf("Enter the student ID: ");
    scanf("%d", &student[Totalstudent].id);

    // Prompt the user to enter the student's name
    printf("Enter the student name: ");
    scanf("%s", student[Totalstudent].name);

    // Prompt the user to enter the student's GPA
    printf("Enter the student's GPA: ");
    scanf("%f", &student[Totalstudent].GPA);

    while (student[Totalstudent].GPA > 4.0) {
        printf("GPA should not be greater than 4.\n");
        printf("Enter the student's GPA (PROPER LESS THAN 4): ");
        scanf("%f", &student[Totalstudent].GPA);
    }

    // Prompt the user to enter the number of courses the student has taken
    printf("Enter the number of courses: ");
    scanf("%d", &student[Totalstudent].NumberOfCourse);

    // Allocate memory for the courses array
    student[Totalstudent].courses = (courses_t*)malloc(student[Totalstudent].NumberOfCourse * sizeof(courses_t));
    if (student[Totalstudent].courses == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    addCourse(student[Totalstudent].id, student[Totalstudent].NumberOfCourse);

    Totalstudent++;
}

void addCourse(int Std_id, int numberOfCourses) {
    int number = -1;
    for (int i = 0; i < Totalstudent; i++) {
        if (student[i].id == Std_id) {
            number = i;
            break;
        }
    }
    if (number == -1) {
        printf("Student with ID %d not found.\n", Std_id);
        return;
    }

    courses_t* new_courses = realloc(student[number].courses,
        (student[number].NumberOfCourse + numberOfCourses) * sizeof(courses_t));
    if (new_courses == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    student[number].courses = new_courses;
    for (int i = 0; i < numberOfCourses; i++) {
        printf("Enter course %d name: ", student[number].NumberOfCourse + i + 1);
        scanf("%39s", student[number].courses[student[number].NumberOfCourse + i].course_name);

        printf("Enter course %d ID: ", student[number].NumberOfCourse + i + 1);
        scanf("%5s", student[number].courses[student[number].NumberOfCourse + i].course_id);

        printf("Enter course %d credit hours: ", student[number].NumberOfCourse + i + 1);
        scanf("%d", &student[number].courses[student[number].NumberOfCourse + i].course_credit);

        printf("Enter course %d mark: ", student[number].NumberOfCourse + i + 1);
        scanf("%2s", student[number].courses[student[number].NumberOfCourse + i].course_mark);
    }

    student[number].NumberOfCourse += numberOfCourses;
}


float calculateGPA(int STD_id){
    int number = -1;
    float TotalGPA =0;
    float calculate=0;
    float currentGPA;
    for (int i = 0; i < Totalstudent; i++) {
        if (student[i].id == STD_id) {
            number = i;
            break;
        }
    }
    if (number == -1) {
        printf("Student with ID %d not found.\n", STD_id);
        return -1;
    }
    currentGPA = student[number].GPA;
    for (int k=0;k<student[number].NumberOfCourse;k++){
        char mark[3] = { student[number].courses[k].course_mark[0], student[number].courses[k].course_mark[1], '\0' };


        if (strcmp(mark, "A+") == 0) {
            calculate = 4.0;
        } else if (strcmp(mark, "A") == 0) {
            calculate = 3.8;
        } else if (strcmp(mark, "B+") == 0) {
            calculate = 3.5;
        } else if (strcmp(mark, "B") == 0) {
            calculate = 3.0;
        } else if (strcmp(mark, "C+") == 0) {
            calculate = 2.5;
        } else if (strcmp(mark, "C") == 0) {
            calculate = 2.0;
        } else if (strcmp(mark, "D+") == 0) {
            calculate = 1.5;
        } else if (strcmp(mark, "D") == 0) {
            calculate = 1.0;
        } else if (strcmp(mark, "F") == 0) {
            calculate = 0.0;
        } else {
            printf("ERROR!!!");
        }

        TotalGPA+=calculate;
        return TotalGPA;
    }

    TotalGPA=TotalGPA/student[number].NumberOfCourse;
    currentGPA= (currentGPA+TotalGPA)/2;
    student[number].GPA=currentGPA;
}
void print_student(int i){
    printf("\t=======================\n");
    printf("\tName: %s \n\tID: %d \n\tGPA: %f \n\tNO OF COURSES: %d\n",student[i].name,student[i].id,
    student[i].GPA,student[i].NumberOfCourse);
    printf("\t=======================\n");

    for(int k=0 ;k<student[i].NumberOfCourse;k++){
    printf("\tCOURSE %d\n",k+1);
    printf("\t#=======================\n");
    printf("\n\t #Course Name: %s \n\t #Course ID: %s \n\t #Course CREDITS: %d \n\t #Course Grade: %s\n",
    student[i].courses[k].course_name,student[i].courses[k].course_id,
    student[i].courses[k].course_credit,student[i].courses[k].course_mark);
    printf("\t=======================\n");
    }

}

void ShowAllStudents()
{
    printf("|==========|====================|====================|=============|\n");
    printf("|    ID    |        Name        |        GPA         |  NO.Course  |\n");
    printf("|==========|====================|====================|=============|\n");

    for(int i=0; i<Totalstudent; i++)
    {
        int k;
        printf("|");
        printf("%s",student[i].id);
        for(k=0; k < 19; k++)
        {
            printf(" ");
        }
        printf("|");
        printf("%s",student[i].name);
        for(k=0; k < (20-strlen(student[i].name)); k++)
        {
            printf(" ");
        }
        printf("|");
        printf("%s",student[i].GPA);
        for(k=0; k < 19; k++)
        {
            printf(" ");
        }
        printf("|");
        printf("%d",student[i].NumberOfCourse);
        for(k=0; k < 12; k++)
        {
            printf(" ");
        }
        printf("|\n");
        printf("|----------|--------------------|--------------------|-------------|\n");

    }
    printf("\n");
}
void delete_student(int id) {
    int index = -1;
    for (int i = 0; i < Totalstudent; i++) {
        if (student[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }
   
    for (int i = index; i < Totalstudent - 1; i++) {
        student[i] = student[i + 1];
    }
    Totalstudent--;
    printf("Student with ID %d deleted.\n", id);
}
void show_all_courses(int STD_id) {
    int number = -1;
    for (int i = 0; i < Totalstudent; i++) {
        if (student[i].id == STD_id) {
            number = i;
            break;
        }
    }
    if (number == -1) {
        printf("Student with ID %d not found.\n", STD_id);
        return;
    }

    printf("Courses for %s (ID: %d):\n", student[number].name, STD_id);
    printf("---------------------------------------------------------\n");
    printf("%-40s %-10s %-10s %-10s\n", "Course Name", "Course ID", "Credits", "Grade");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < student[number].NumberOfCourse; i++) {
        printf("%-40s %-10s %-10d %-10s\n", student[number].courses[i].course_name, student[number].courses[i].course_id, student[number].courses[i].course_credit, student[number].courses[i].course_mark);
    }
    has_repeated_course(STD_id);
}
int has_repeated_course(int STD_id) {
    int number = -1;
    for (int i = 0; i < Totalstudent; i++) {
        if (student[i].id == STD_id) {
            number = i;
            break;
        }
    }
    if (number == -1) {
        printf("Student with ID %d not found.\n", STD_id);
        return -1;
    }

    for (int i = 0; i < student[number].NumberOfCourse; i++) {
        for (int k = i + 1; k < student[number].NumberOfCourse; k++) {
            if (strcmp(student[number].courses[i].course_id, student[number].courses[k].course_id) == 0) {
                printf("Student with ID %d has a repeated course: %s\n", STD_id, student[number].courses[i].course_id);
                return 1;
            }
        }
    }
    free(courses);
    return 0;
}
