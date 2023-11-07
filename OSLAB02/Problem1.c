#include <stdio.h>
#include <math.h>
#include <stdbool.h>

float Mdist(float xO, float yO, float xA, float yA) {
    return fabs(xO - xA) + fabs(yO - yA);
}
bool Check(float xO, float yO, float xA, float yA, float D) {
    float distance = Mdist(xO, yO, xA, yA);
    return distance >= D;
}
int main (){
  float xO, yO, xA, yA, D;

    
    printf("Please enter the coordinates of O:\n");
    scanf("%f %f", &xO, &yO);

    printf("Please enter the coordinates of A:\n");
    scanf("%f %f", &xA, &yA);

    printf("Please enter the target distance D:\n");
    scanf("%f", &D);

   
    float manhattanDistance = Mdist(xO, yO, xA, yA);
    printf("The Manhattan distance between O and A = %.2f\n", manhattanDistance);

   
    bool result = Check(xO, yO, xA, yA, D);
    if (result) {
        printf("The Manhattan distance between O and A is >= to D = %.2f\n", D);
    } else {
        printf("The Manhattan distance between O and A is less than D = %.2f\n", D);
    }

    return 0;


   
}