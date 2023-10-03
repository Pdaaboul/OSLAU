#include <stdio.h>

int isRectangular(int a);
void Rectangulars(int b);

int main(){
    int a,b;
        printf("Enter positive integers (negative to stop):\n");
    while (1) {
        scanf("%d", &a);
        if (a < 0) break;
        
        if (isRectangular(a)) {
            printf("%d is rectangular.\n", a);
        } else {
            printf("%d is not rectangular.\n", a);
        }
    }

    printf("Enter a positive integer to find rectangular numbers up to that value: ");
    scanf("%d", &b);
    Rectangulars(b);
    
    return 0;
}



int isRectangular(int a) {
    for (int i = 1; i <= a / 2; ++i) {
        if (i * (i + 1) == a) {
            return 1;
        }
    }
    return 0;
}

void Rectangulars(int b) {
    printf("Rectangular numbers in [0, %d]: ", b);
    for (int i = 1; i * (i + 1) <= b; ++i) {
        printf("%d ", i * (i + 1));
    }
    printf("\n");
}