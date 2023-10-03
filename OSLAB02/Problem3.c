#include <stdio.h>
#include <stdlib.h>
int Computemax(int a, int b, int c, int d);
float avg(int a, int b, int c, int d);
int Computemin(int a, int b, int c, int d);

int main (int argc, char **argv){
    int a,b,c,d;
    if( argc != 5){
        printf("ERROR!\n");
        return 1;
    }
    
     a = atoi(argv[1]);
     b = atoi(argv[2]);
     c = atoi(argv[3]);
     d = atoi(argv[4]);

    float average = avg(a, b, c, d);
    int max = Computemax(a, b, c, d);
    int min = Computemin(a, b, c, d);

    printf("The average of all the integers is: %.2f\n", average);
    printf("The minimum of all the integers is: %d\n", min);
    printf("The maximum of all the integers is: %d\n", max);

    return 0;
}

int Computemax(int a, int b, int c, int d){
     int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    if (d > max) max = d;
    return max;
}
float avg(int a, int b, int c, int d){
    return ((a+b+c+d)/4);
}

int Computemin(int a, int b, int c, int d){
    int min = a;
    if (b<min) min = b;
    if (c<min) min = c;
    if (d<min) min = d;
    return min;
}