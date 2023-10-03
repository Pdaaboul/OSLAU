#include <stdio.h>
#include <stdbool.h>

int main() {
    int num, firstNum;
    bool isEqual = true;
    bool firstInput = true;

    printf("Please enter integers and -1 to exit:\n");

  while (true) {
        scanf("%d", &num);

        if (firstInput) {
            firstNum = num;
            firstInput = false;
        }

        if (num == -1) break;

        if (num != firstNum) {
            isEqual = false;
        }
    }

    if (isEqual) {
        printf("All the integers are equal? YES\n");
    } else {
        printf("All the integers are equal? NO\n");
    }

    return 0;
}
