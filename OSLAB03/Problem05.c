#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap (int* a, int *b);
int main (){
 int a,b;
 a = 5;
 b = 10;

 int* ptr1;
 int* ptr2;
 ptr1 = &a;
 ptr2 = &b;
    
    printf("Before Swap : \n a = %d \n b = %d \n", a,b); 
    swap(&a,&b);
   printf("After Swap : \n a = %d \n b = %d", a,b); 
    return 0;

}

void swap (int* a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}