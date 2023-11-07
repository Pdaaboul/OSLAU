
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct {
    int id;
    char name[100];
    char date[20];
    float rating;
} Movie;

int main() {
    Movie *shared_movies;

    
    shared_movies = mmap(NULL, 5 * sizeof(Movie), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    
    if (fork() == 0) {
        printf("Enter details for 5 movies:\n");
        for (int i = 0; i < 5; i++) {
            printf("Movie %d\n", i+1);
            printf("ID: ");
            scanf("%d", &shared_movies[i].id);
            printf("Name: ");
            scanf("%s", shared_movies[i].name);
            printf("Date: ");
            scanf("%s", shared_movies[i].date);
            printf("Rating: ");
            scanf("%f", &shared_movies[i].rating);
        }
        exit(0);
    }

    
    wait(NULL);

    
    if (fork() == 0) {
        Movie best_movie = shared_movies[0];
        for (int i = 1; i < 5; i++) {
            if (shared_movies[i].rating > best_movie.rating) {
                best_movie = shared_movies[i];
            }
        }
        printf("Movie with highest rating:\n");
        printf("ID: %d\n", best_movie.id);
        printf("Name: %s\n", best_movie.name);
        printf("Date: %s\n", best_movie.date);
        printf("Rating: %.1f\n", best_movie.rating);
        exit(0);
    }


    wait(NULL);


    munmap(shared_movies, 5 * sizeof(Movie));

    return 0;
}
