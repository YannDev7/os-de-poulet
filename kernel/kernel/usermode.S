.globl jump_usermode
jump_usermode:
	mov %esp, %eax
	push $0x23
	push %eax
	pushf
	push $0x1B
	push $test_user_function
    iret
