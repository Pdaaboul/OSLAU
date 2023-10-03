#include <stdio.h>
#include <math.h>

int main(){
    int w = 13;
    int h = 7;
    int l = 2;
    float R = 5.5;
    int VolumeCuboid;
    float VolumeSphere;

    VolumeCuboid = w * h * l;
    VolumeSphere = (4.0 / 3) * M_PI * pow(R, 3);

    printf("The volume of the cuboid is %d\n",VolumeCuboid);
    printf("The volume of the sphere is %.2f\n",VolumeSphere);

    return 0 ;
}