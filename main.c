#include <stdio.h>
#include <stdlib.h>
#include "registers.c"

int main() {

    FILE *fptr;

    fptr = fopen("sample.txt", "r");
    char *instructions = malloc(1000 * sizeof(char));
    int len = 0;
    int c;

    if (fptr == NULL)
    {
        printf("The file does not exist.");
        exit(1);
    }

    while ((c = fgetc(fptr)) != EOF)
    {
        instructions[len++] = (char) c;
    }
    instructions[len] = '\0';
    fclose(fptr);

    /** Decode **/

    int byte_size = len / 2;
    decode(instructions, byte_size);
    

    /** End Decode  **/

    free(instructions);

    return 0;
}