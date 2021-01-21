	.text
    .set noreorder
    .set noat

	.macro MCOUNT_SAVE_REGS
	    dsubu $sp, 304
	    sd $ra, 248($sp)
	    sd $at, 8($sp)
	    sd $a0, 32($sp)
	   	sd $a1, 40($sp)
	    sd $a2, 48($sp)
	    sd $a3, 56($sp)
	    sd $a4, 64($sp)
	    sd $a5, 72($sp)
	    sd $a6, 80($sp)
	    sd $a7, 88($sp)
	    sd $gp, 96($sp)
    .endm

    .macro MCOUNT_RESTORE_REGS
	    ld $ra, 248($sp)
	    ld $at, 8($sp)
	    ld $a0, 32($sp)
	    ld $a1, 40($sp)
	    ld $a2, 48($sp)
	    ld $a3, 56($sp)
	    ld $a4, 64($sp)
	    ld $a5, 72($sp)
	    ld $a6, 80($sp)
	    ld $a7, 88($sp)
	    sd $gp, 96($sp)
	    daddiu $sp, 304
    .endm

	.globl ftrace_caller
	.type ftrace_caller, @function
ftrace_caller:

	#开栈，保护寄存器
	MCOUNT_SAVE_REGS

	#ra 存储 pc(jal ftrace_caller)+8
	#a0 = pc(jal ftrace_caller)
	#参数1
	dsubu $a0, $ra, 8
	
	#参数2
	move $a1, $at

	#参数3
	and $a2, 0 

	#参数4
	daddiu $v0, $sp, 104
	move $a3, $v0

	jal ftrace_call
	nop

ftrace_call:
	jal ftrace_call_change
	nop

	#获取跳转地址到v0
	daddiu $v0, $sp, 104
	daddiu $v0, $v0, 0*8
	lw $t1, 0($v0)
	lw $t2, 4($v0)

	#恢复寄存器
	MCOUNT_RESTORE_REGS

	#需要恢复sp在上一层入口时的初始值
	#daddiu $sp, $sp, 32

	#计算偏移量，并恢复sp
	daddiu $v0, $at, -8
	lw $t0, ($v0)
	and $t0, 0xffff
	srl $t0, 15
	and $t0, 0x1
	bnez $t0, X
	nop
	beqz $t0, Y

X:	
	lw $v1, ($v0)
	and $v1, 0xffff
	sll $v1, 2
	li $t0, 0x3ffff
	xor $v1, $t0
	daddiu $v1, $v1, 1 
	daddiu $v0, $at, -4
	dsubu $v0, $v0, $v1
	j Z
Y:
	lw $v1, ($v0)
	and $v1, 0xffff
	sll $v1, 2
	li $t0, 0x1ffff
	xor $v1, $t0
	daddiu $v1, $v1, 1 
	daddiu $v0, $at, -4
	dsubu $v0, $v0, $v1
	j Z

Z:
	lw $v1, ($v0)
	and $v1, 0xffff
	xor $v1, 0xffff
	daddiu $v1, $v1, 1
	
	daddu $sp, $sp, $v1

	#将跳转地址存入t9
	and $t9, 0
	or $t9, $t2
	dsll $t9, $t9, 32
	or $t9, $t1

	#执行新并直接返回
	move $ra, $at
	move $s8, $sp
	jr $t9
