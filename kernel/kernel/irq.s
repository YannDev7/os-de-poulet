.macro ISR_ERR index
.globl _isr_\index
_isr_\index:
    pusha
    push 32(%esp)
    push $\index
    call exception_handler
    pop %eax
    pop %eax
    popa
    add $4, %esp
    iret
.endm

.macro ISR_NOERR index
.globl _isr_\index
_isr_\index:
    pusha
    push $0x0 // dummy error code
    push $\index
    call exception_handler
    pop %eax
    pop %eax
    popa
    iret
.endm

ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERR   8
ISR_NOERR 9
ISR_ERR   10
ISR_ERR   11
ISR_ERR   12
ISR_ERR   13


.globl _isr_14
_isr_14:
    pusha
    mov %cr2, %eax
    push %eax
    push 32(%esp)
    push $14
    call _interrupt_14
    pop %eax
    pop %eax
    pop %eax
    popa
    add $4, %esp
    iret



ISR_NOERR 15
ISR_NOERR 16
ISR_ERR   17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_ERR   30
ISR_NOERR 31

.globl _irq_0
_irq_0:
    pusha
    call irq_timer_handler
    popa
    iret

.globl _irq_1
_irq_1:
    pusha
    call irq_kbd_handler
    popa
    iret
