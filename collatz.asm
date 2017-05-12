.data


William: .asciiz "William\n"
EnterInt: .asciiz "Please enter an integer\n"
newline: .asciiz "\n"
.text
main:
li $v0, 4
la $a0, William
syscall

li $v1, 4
la $a1, EnterInt
syscall

li $v0, 5 #get ready to read in integers
syscall



move $t0, $v0


while: 
move $a0, $t0
addi $v0, $zero, 1
syscall

la $a0, newline
addi $v0, $zero, 4
syscall

if1: 
li $t2, 2		#n is in $t0
div $t0, $t2	#if((n % 2) != 0)
mfhi $t1
beq $t1, $zero, else1
nop 


doif1:
li $t2, 3
mult $t0, $t2
mflo $t0
addi $t0, $t0, 1
j afterif1
nop

else1:
li $t2, 2
div $t0, $t2
mflo $t0
b afterif1
nop

afterif1:

addi $t3, $t0, -1
beq $t3, $zero, afterwhile
nop

afterIf:
j while
nop

afterwhile:
move $a0, $t0
addi $v0, $zero, 1
syscall

la $a0, newline
addi $v0, $zero, 4
syscall

li $v0, 10
syscall
