#include <stdio.h>
#include <math.h> 
void MySuperFunc(int *x,int *y, int *z);

int main (){
 int x,y,z;
    
    printf("please enter three integers z, x and y : \n");
    scanf("%d %d %d", &x ,&y ,&z);
    printf("From main, before ==> x= %d, y=%d and z= %d\n", x, y, z);
    MySuperFunc(&x,&y,&z);
    printf("From main, after ==> x= %d, y=%d and z= %d\n", x, y, z);

    return 0;
}

void MySuperFunc(int *x,int *y, int *z){
    int placeholderX = *x;
    int placeHolderY = *y;
    int placeHolderZ = *z;

    *x = placeholderX + placeHolderY + placeHolderZ;
    *y = pow(placeHolderY, placeholderX);
    *z = (placeholderX) * (placeHolderY) * (placeHolderZ);
}