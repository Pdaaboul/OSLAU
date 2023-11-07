
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe1[2];  
    int pipe2[2];  
    pipe(pipe1);
    pipe(pipe2);
    pid_t process_id = fork();

    if (process_id == 0) {
        close(pipe1[1]);
        close(pipe2[0]);

        int user_choice;  
        char capital_city[50];
        char *countries[] = {"Lebanon", "Egypt", "Tunis", "Morocco", "Jordan"};

        while (1) {
            printf("Please enter the number of the country you want to learn about:\n");
            printf("1. Lebanon\n2. Egypt\n3. Tunis\n4. Morocco\n5. Jordan\n");
            printf("Enter the corresponding number: ");
            scanf("%d", &user_choice);

            if (user_choice >= 1 && user_choice <= 5) {
                write(pipe2[1], &user_choice, sizeof(int));
                read(pipe1[0], capital_city, sizeof(capital_city));
                printf("Child: The capital of %s is %s\n", countries[user_choice - 1], capital_city);
                exit(0);
            } else {
                printf("Invalid choice. Please try again.\n");
            }
        }
    } else {  
        close(pipe1[0]);
        close(pipe2[1]);

        int selected_number; 
        char city_name[50];  

        read(pipe2[0], &selected_number, sizeof(int));

        switch (selected_number) {
            case 1: strcpy(city_name, "Beirut"); break;
            case 2: strcpy(city_name, "Cairo"); break;
            case 3: strcpy(city_name, "Tunis"); break;
            case 4: strcpy(city_name, "Rabat"); break;
            case 5: strcpy(city_name, "Amman"); break;
        }

        write(pipe1[1], city_name, sizeof(city_name));
        wait(NULL);
    }

    return 0;
}
