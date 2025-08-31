# simple program that exists itself if successful

# section operators break 
# program into a sections
.section .data 
.section .text

# globl means that the assembler
# shouldnt discard the symbol after
# assembly proccess. 
# without globl section computer wont know
# from where to start the program
.globl _start

_start:
# %eax holds the system call number
movl $1, %eax   # linux number for exiting
                # apparently the same as the return 1 in c  
# %ebx holds the return status
movl $20, %ebx   # status number for the os

# int stands for interrupt
int $0x80       #wakes up kernel to run the exit command
