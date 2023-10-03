#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    double x;
    double y;
    double width;
    double length;
}Rectangle ;
void ScaleRectangle(Rectangle *rect, int scale_factor);
double ComputeArea(Rectangle rectangle);
double ComputePerimeter(Rectangle rectangle) ;
bool isSquare(Rectangle rectangle);
bool withinRectangle(Rectangle rectangle, double a, double b);
void MoveRectangle(Rectangle *rectangle, double a, double b);
int main (){


    Rectangle rect1 = {1.00, 1.00, 5.50, 5.50};
    printf("Rectangle 1: w=%.2f, l=%.2f, A(%.2f, %.2f)\n", rect1.width, rect1.length, rect1.x, rect1.y);


    ScaleRectangle(&rect1, 2);
    printf("Rectangle R1 scaled: w=%.2f, l=%.2f\n", rect1.width, rect1.length);

   
    printf("Rectangle R1 area= %.2f\n", ComputeArea(rect1));
    printf("Rectangle R1 perimeter= %.2f\n", ComputePerimeter(rect1));

   
    if (isSquare(rect1)) {
        printf("Square\n");
    } else {
        printf("Not a Square\n");
    }

   
    double pointX, pointY;
    printf("Please enter the coordinates of the point P:\n");
    scanf("%lf", &pointX);
    scanf("%lf", &pointY);

    if (withinRectangle(rect1, pointX, pointY)) {
        printf("P(x=%.2f, y= %.2f) is located inside the rectangle\n", pointX, pointY);
    } else {
        printf("P(x=%.2f, y= %.2f) is not located inside the rectangle\n", pointX, pointY);
    }

   
    MoveRectangle(&rect1, 3.3, 10.1);
    printf("Move the rectangle by (3.3, 10.10):\n");
    printf("Rectangle R1 Updated: w=%.2f, l= %.2f, A(%.2f, %.2f)\n", rect1.width, rect1.length, rect1.x, rect1.y);

    return 0;

}
void ScaleRectangle(Rectangle *rectangle, int a){
    rectangle->width  *= a;
    rectangle->length  *= a;
}

double ComputeArea(Rectangle rectangle){
    return (rectangle.length * rectangle.width);
}
double ComputePerimeter(Rectangle rectangle) {
    return (rectangle.length + rectangle.width) * 2;
}


bool isSquare(Rectangle rectangle){
    return rectangle.width == rectangle.length;
}
bool withinRectangle(Rectangle rectangle, double a, double b){
return (a >= rectangle.x && a<=(rectangle.x + rectangle.width)) && (b<=rectangle.y && b>=(rectangle.y -rectangle.length));
}

void MoveRectangle(Rectangle *rectangle, double a, double b){
    rectangle->x += a;
    rectangle->y += b;
}