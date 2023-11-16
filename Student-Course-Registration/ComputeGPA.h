

#ifndef COMPUTEGPA_H_
#define COMPUTEGPA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



extern void add_new_student();
extern void addCourse(int Std_id);
extern float calculateGPA(int STD_id);
extern void print_student(int i);
extern void ShowAllStudents();
extern void delete_student(int id);
extern void show_all_courses(int STD_id);
int has_repeated_course(int STD_id);

#endif /* COMPUTEGPA_H_ */
