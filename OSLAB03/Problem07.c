#include <stdio.h>
#include <string.h>


void encodeMessage(char *msg, int *codeKeys, int msgLength, int keysLength);


int main() {


    char userInput[50];
    int keyArray[20];
    int arraySize;


    printf("Type the message: ");
    scanf("%s", userInput);
    printf("How many elements in the key array? ");
    scanf("%d", &arraySize);

    for (int i = 0; i < arraySize; ++i) {
        printf("Provide key value %d: ", i + 1);
        scanf("%d", &keyArray[i]);
    }


    int strLen = strlen(userInput);


    encodeMessage(userInput, keyArray, strLen, arraySize);

    return 0;
}


void encodeMessage(char *msg, int *codeKeys, int msgLength, int keysLength) {
    char encodedMsg[msgLength + 1];

    for (int i = 0; i < msgLength; ++i) {
        int shiftValue = codeKeys[i % keysLength];
        char letter = msg[i];
        int newCharVal = letter - 'a' + shiftValue;


        if (newCharVal > 25) {
            newCharVal = newCharVal - 26;
        }

        encodedMsg[i] = newCharVal + 'a';
    }


    encodedMsg[msgLength] = '\0';


    printf("Encoded Message: %s\n", encodedMsg);
}
