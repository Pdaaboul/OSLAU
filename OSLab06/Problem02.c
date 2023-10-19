#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 20
#define NUM_STRINGS 4

void analyzeAndTransform(char* str, int k) {
    int len = strlen(str);
    int letters = 0, uppercase = 0, lowercase = 0, integers = 0, specialChars = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(str[i])) {
            letters++;
            if (isupper(str[i])) {
                uppercase++;
            } else {
                lowercase++;
            }
        } else if (isdigit(str[i])) {
            integers++;
        } else {
            specialChars++;
        }
    }

    printf("*** String %d ***\n%s\n", k, str);
    printf("Length = %d\n", len);
    printf("The number of letters is: %d\n", letters);
    printf("The number of uppercase letters is: %d\n", uppercase);
    printf("The number of lowercase letters is: %d\n", lowercase);
    printf("The number of integers is: %d\n", integers);
    printf("The number of special characters is: %d\n", specialChars);

  
    for (int i = 0; i < len; i++) {
        str[i] = toupper(str[i]);
    }

    printf("Transformed to uppercase:\n%s\n", str);
}

int main() {
    char* sharedArray[NUM_STRINGS];
    char tempStr[MAX_STR_LEN];


    for (int i = 0; i < NUM_STRINGS; i++) {
        sharedArray[i] = mmap(NULL, MAX_STR_LEN, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (sharedArray[i] == MAP_FAILED) {
            printf("mmap failed");
            return 1;
        }
    }

    pid_t childPid = fork();

    if (childPid < 0) {
        printf("Fork failed");
        return 1;
    }

    if (childPid == 0) { 
        printf("From child:\n");
        for (int i = 0; i < NUM_STRINGS; i++) {
            printf("Please enter a string %d: ", i + 1);
            scanf("%s", tempStr);
            strcpy(sharedArray[i], tempStr);
        }
    } else {
        wait(NULL);

        printf("From Parent:\n");

        for (int i = 0; i < NUM_STRINGS; i++) {
            analyzeAndTransform(sharedArray[i], i);
        }

     
        for (int i = 0; i < NUM_STRINGS; i++) {
            munmap(sharedArray[i], MAX_STR_LEN);
        }
    }

    return 0;
}
