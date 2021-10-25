#include <stdio.h>
#include <stdlib.h>
#include "registers.c"
#include "opcode_table.c"
#include "decoder.c"

int convertHexToInt(char c);

int main(int argc, char *argv[]) {
    FILE *fptr;

    fptr = fopen(argv[1], "r");
    int *instructions = malloc(1000 * sizeof(int));
    int len = 0;
    char c;

    if (fptr == NULL)
    {
        printf("The file does not exist. Exit Program.");
        exit(1);
    }

    while ((c = fgetc(fptr)) != EOF)
    {
        if (c == ' ')
        {
            continue;
        }
        instructions[len++] = convertHexToInt(c);
    }
    instructions[len] = '\0';
    fclose(fptr);

    init_one_byte_opcode_map();
    init_two_byte_opcode_map();

    /** Decode **/

    int byte_size = len / 2;
    decode(instructions, byte_size);
    

    /** End Decode  **/

    free(instructions);

    return 0;
}

int convertHexToInt(char c)
{
    switch(c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
        case 'A':
            return 10;
        case 'b':
        case 'B':
            return 11;
        case 'c':
        case 'C':
            return 12;
        case 'd':
        case 'D':
            return 13;
        case 'e':
        case 'E':
            return 14;
        case 'f':
        case 'F':
            return 15;
        default:
            printf("Invalid input. Exit Program.");
            exit(1);
    }
}