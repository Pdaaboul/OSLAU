#include <stdio.h>
float computeBMI(float weight, int height) {
    return (weight * 10000) / ((float) height * height);
}
int main(){
float w;
int h;
float BMI;

    printf("Enter the weight in kg:\n");
    scanf("%f", &w);

    printf("Enter the height in cm:\n");
    scanf("%d", &h);

    
    if (w <= 0 || h <= 0) {
        printf("Error: The weight and height should not be negative or equal to 0.\n");
        return 1;
    }


    BMI = computeBMI(w, h);
      if (BMI < 18.5) {
        printf("BMI=%.1f ==> Underweight\n", BMI);
    } else if (BMI >= 18.5 && BMI <= 24.9) {
        printf("BMI=%.1f ==> Normal Weight\n", BMI);
    } else {
        printf("BMI=%.1f ==> Overweight\n", BMI);
    }
    return 0;
}