#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void LowerToUpper(char str[]);
void UpperToLower(char str[]);

int main(){
    char str [100];
    printf("Please enter a String S \n");
    fgets(str,sizeof(str),stdin);


    printf("Transform to Upper Case : \n");
    LowerToUpper(str);
    printf("%s \n", str);
    printf("Transform to Lower Case : \n");
    UpperToLower(str);
    printf("%s \n",str);
    return 0;
}

void LowerToUpper(char str[]){
     for(int i = 0; str[i]; ++i) {
        if(str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}

void UpperToLower(char Str[]){
    for (int i = 0; Str[i] ;i++){
            if (Str[i] >= 'A' && Str[i] <= 'Z'){
                Str[i] = Str[i] + 'a' - 'A';
            }
    }
}