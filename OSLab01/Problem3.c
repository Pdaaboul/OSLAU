#include <stdio.h>
float MyAverage(int k, int l, int m);
int MySum(int k, int l, int m);
int MyMin(int k, int l, int m);
int MyMax(int k, int l, int m);
void Display(int k, int l, int m);

int main(){
int k = 20;
int l = 12;
int m = 35;



printf("the sum is:  %.d\n", MySum(k,l,m));
printf("The average is:  %.2f\n", MyAverage(k,l,m));
printf("The minimum is:  %d\n", MyMin(k,l,m));
printf("The maximum is:  %d\n", MyMax(k,l,m));
printf("The numbers sorted are : ");
Display(k,l,m);


return 0;
}


float MyAverage(int k, int l, int m) {
    return (k + l + m) / 3.0;
}

int MySum(int k, int l, int m) {
    return k + l + m;
}

int MyMin(int k, int l, int m) {
    int min = k;
    if (l < min) min = l;
    if (m < min) min = m;
    return min;
}

int MyMax(int k, int l, int m) {
    int max = k;
    if (l > max) max = l;
    if (m > max) max = m;
    return max;
}

void Display(int k, int l, int m){
      int temp;
    if (k > l) { 
        temp = k; k = l; l = temp; 
        }

    if (l > m) {
         temp = l; l = m; m = temp; 
         }

    if (k > l) {
         temp = k; k = l; l = temp; 
         }

    printf("%d, %d, %d\n", k, l, m);
}