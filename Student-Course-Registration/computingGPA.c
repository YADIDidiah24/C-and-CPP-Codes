#include "ComputeGPA.h"


int main() {

        int choice, student_id;

    do {
        printf("\nChoose an option:\n");
        printf("1. Add a new student\n");
        printf("2. Add courses for an existing student\n");
        printf("3. Calculate GPA for a student\n");
        printf("4. Print a student's information\n");
        printf("5. Show all students\n");
        printf("6. Delete a student\n");
        printf("7. Show all courses for a student\n");
        printf("8. Exit\n");
        printf("Enter your choice (1-8): ");
        scanf("%d", &choice);

        
        switch (choice) {
            case 1:
                add_new_student();
                break;
            case 2:
                printf("Enter the student ID: ");
                scanf("%d", &student_id);
                addCourse(student_id);
                break;
            case 3:
                printf("Enter the student ID: ");
                scanf("%d", &student_id);
                calculateGPA(student_id);
                break;
            case 4:
                printf("Enter the student ID: ");
                scanf("%d", &student_id);
                print_student(student_id);
                break;
            case 5:
                ShowAllStudents();
                break;
            case 6:
                printf("Enter student ID to delete: ");
                scanf("%d", &student_id);
                delete_student(student_id);
                break;
            case 7:
                printf("Enter student ID to show course information: ");
                scanf("%d", &student_id);
                show_all_courses(student_id);
                break;
            case 8:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please choose again.\n");
                break;
        }
        char continue_choice;
        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &continue_choice);
        if (continue_choice == 'n') {
            break;
        }
    } while (1);
    return 0;
}
