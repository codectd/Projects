.data

william: .asciiz "William\n"
enterstr: .asciiz "Please enter a string"
newline: .asciiz "\n"
star: .asciiz "*"
starnewline: .asciiz "*\n"
str: .space 100

.text
main:
li $v0, 4
la $a0, william
syscall

li $v0, 4
la $a0, enterstr
syscall

li $v0, 8 
la $a0, str
li $a1, 100
syscall

move $t0, $zero
while1:#str[index] break; index++;
la $t1, str
add $t1, $t1, $t0
lb $t1, 0($t1)
beq $t1, $zero, afterwhile1
nop

addi $t0, $t0, 1

j while1
nop

afterwhile1:
#str, $t0, -1
la $t6, str
add $t6, $t0, $t6
addi $t6, $t6, -1
sb $zero, 0($t6)

#for(int i = 0; i < inStringLen + 2; i++)
#  {
#    printf("*");
#  }
li $t2, 0

while2:
if1:
addi $t3, $t0, 1
bge $t2, $t3, afterwhile2
nop

li $v0, 4
la $a0, star
syscall

add $t2, $t2, 1

j while2
nop

li $v0, 4
la $a0, star
syscall


afterwhile2:

li $v0, 4
la $a0, newline
syscall

li $v0, 4
la $a0, star
syscall

li $v0, 4
la $a0, str
syscall

li $v0, 4
la $a0, star
syscall

li $v0, 4
la $a0, newline
syscall

li $t2, 0


while3:
if3:
addi $t3, $t0, 0
bge $t2, $t3, afterwhile3
nop

li $v0, 4
la $a0, star
syscall

add $t2, $t2, 1

j while3
nop

afterwhile3:

li $v0, 4
la $a0, star
syscall


