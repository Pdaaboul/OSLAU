#include <stdio.h>

int isRightTriangle(int a, int b, int c) ;

int main() {
    int N;

    
    printf("Please enter an integer N:\n");
    scanf("%d", &N);

    
    printf("The right triangles having sides ranging between 1 and %d are:\n", N);

    for (int a = 1; a <= N-1; a++) {
        for (int b = a; b <= N-1; b++) {  
            for (int c = b; c <= N-1; c++) {  
                if (isRightTriangle(a, b, c)) {
                    printf("(%d, %d, %d)\n", a, b, c);
                }
            }
        }
    }

    return 0;
}
int isRightTriangle(int a, int b, int c) {
    return (a * a + b * b == c * c) || (a * a + c * c == b * b) || (c * c + b * b == a * a);
}
