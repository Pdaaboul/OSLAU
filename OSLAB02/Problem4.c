#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c;
    printf("Enter a, b and c:\n");
    scanf("%d %d %d", &a, &b, &c);

   
    if (a < 0 || b < 0 || c < 0) {
        printf("Error: The integers should not be negative\n");
        return 1;
    }

    if (a > 9 || b > 9 || c > 9) {
        printf("Error: The integers should be single-digit numbers\n");
        return 1;
    }

    int sum = pow(a, 3) + pow(b, 3) + pow(c, 3);
    int num = a * 100 + b * 10 + c;

 
    if (sum == num) {
        printf("%d is an Armstrong number since %d^3 + %d^3 + %d^3 = %d\n", num, a, b, c, sum);
    } else {
        printf("%d is not an Armstrong number since %d^3 + %d^3 + %d^3 is not equal to %d\n", num, a, b, c, num);
    }

    return 0;
}
