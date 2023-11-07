#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {

int Id;
 char Name[50];
 float GPA;
}Student;

float avg( Student students[], int size);
 Student HighestGPA( Student students[], int size);

int main(){
    Student s[5]  = {
        {1, "Peter", 4.0},
        {2, "Nazih", 3.2},
        {3, "JeanPaul", 2.6},
        {4, "Kamil", 3.5},
        {5, "Cezario", 3.7}
 };
    float averageGPA = avg(s, 5);
    printf("Average GPA: %.2f\n", averageGPA);

    Student HighestStudent = HighestGPA(s, 5);
    printf("Student with the highest GPA: %s [ID: %d, GPA: %.2f]\n", HighestStudent.Name, HighestStudent.Id, HighestStudent.GPA);
        
 

    return 0;
}

float avg( Student students[], int size){
  float sum = 0;
  for (int i =0; i < size; i ++){
    sum += students[i].GPA;
  }
  return sum/size;
}

Student HighestGPA(Student students[], int size){
    Student current = students[0];
    for (int i = 0; i < size; i ++){
        if  (students[i].GPA > current.GPA){
            current = students[i];
        }
    }
    return current;
}