#include <stdio.h>
#include <stdbool.h>

int main (){
    int arr [100];
    int input;
    int counter = 0;
    bool isEqual = true;


    printf("Please enter integers and -1 to exit:\n");

    while (true){
        scanf("%d", &input);
        if(input == -1) {
            break;
        }
        else {
            arr[counter] = input;
            counter ++;
        }
    }

    for (int i = 0; i < counter -1; i ++){
        if (arr[i] != arr[i+1]){
            isEqual = false;
            break;
        }
    }

   if (isEqual) {
        printf("All the integers are equal? YES\n");
    } else {
        printf("All the integers are equal? NO\n");
    }

    return 0;
}