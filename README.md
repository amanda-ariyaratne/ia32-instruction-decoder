# x86 Processor Instruction Emulator

## Team
1. K. H. A. A. Ariyaratne - 170043A
2. M. P. M. Gayathri - 170182X

## Functions available
1. Addition
2. AND
3. Load effective address
4. Move
5. Compare
6. Increment
7. Decrement
8. Subtraction
9. Push
10. Pop

## Compile the Program
To compile the program execute the following on the command line at the root folder.
```
gcc -o main main.c
```

## Run the program
To compile the program after compilation execute the following on the command line at the root folder. You need to specify an input file as a command line argument. The input file must contain the instructions in hex format similar to the input file given with the project description.
```
./main <sample.txt>
```

Five sample input files are provided with the repository named 

`sample1.txt` 

`sample2.txt`

`sample3.txt`

`sample4.txt`

`sample5.txt`

Example inputs are provided below.

### Add 0+1 and move the value to eax
1. B0 00 # mov 0 to eax
2. B1 01 # mov 1 to ecx
3. 22 C1 # get eax <- eax AND ecx (11 000 001)

AND, MOV, reg<br>
B0 00 B1 01 22 C1

### Add two numbers and store them in the mem(val of CL)
1. C6 00 01 # store 1 in effective address of 00 000 001 (00 + ECX -> CL)
2. B0 01 # mov 1 to eax
3. 00 01 # mem <- mem+reg (00 000 001 -> 000(AL) 00 001 addrof(value of CL))

ADD, MOV, Mem load<br>
C6 00 01 B0 01 00 01

### Sub two numbers and store in the addr in the displacement
1. C6 45 00 01 (mod RM-> 01 000 101)
2. B0 01 # mov 1 to eax
3. 28 45

SUB, MOV, Mem load using displacement<br>
C6 45 00 01 B0 01 28 45

### Load effective addr and store it in EAX and check greater than 0
1. 8D 04 21 # modrm 00 002 100 sib 00 100 001 (store addr val in ECX in EAX)
2. 3D 00 00 00 00

LEA, CMP<br>
8D 04 21 3D 00 00 00 00

### Increment eax value by 1 and Decrement it again then push to the stack
1. FE C0 (11 000 000)
2. 0F FF F0 (11 110 000)
3. FE C8 (11 001 000)
4. 0F FF F0 (11 110 000)

INC, DEC, PUSH<br>
FE C0 0F FF F0 FE C8 0F FF F0
