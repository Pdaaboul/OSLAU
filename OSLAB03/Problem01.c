#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char str[100];
    char c;
    int totalChars = 0, letters = 0, integers = 0, specialChars = 0, spaces = 0;
    int charCount[256] = {0};

    printf("Please enter a String S\n");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    printf("Please enter a character C\n");
    scanf(" %c", &c);

    for(int i = 0; str[i]; i++) {
        unsigned char ch = str[i];
        totalChars++;
        charCount[ch]++;
        
        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            letters++;
        } else if(ch >= '0' && ch <= '9') {
            integers++;
        } else if(ch == ' ') {
            spaces++;
        } else {
            specialChars++;
        }
    }

    printf("The total number of characters is: %d\n", totalChars);
    printf("The number of letters is: %d\n", letters);
    printf("The number of integers is: %d\n", integers);
    printf("The number of special characters is: %d\n", specialChars);
    printf("The number of spaces is: %d\n", spaces);
    printf("The character %c --> Occurrence: %d\n", c, charCount[(unsigned char)c]);

    for(int i = 0; i < 256; i++) {
        if(charCount[i] > 0) {
            printf("Character = %c --> Occurrence: %d\n", i, charCount[i]);
        }
    }
    
    return 0;
}
