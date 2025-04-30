.text

// Fonctions de la GDT

.globl loadGDT
loadGDT:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax
    lgdt (%eax)
    mov %ebp, %esp
    pop %ebp
    ret

.globl setSegmentRegisters
setSegmentRegisters:
    mov $0x10, %eax
    mov %eax, %ds
    mov %eax, %ss
    mov %eax, %es
    jmp $0x08,$.flush_cs
.flush_cs:
    ret

.globl getGDTaddr
getGDTaddr:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax
    sgdt (%eax)
    mov %ebp, %esp
    pop %ebp
    ret

// Fonctions de l'IDT

.globl loadIDT
loadIDT:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax
    lidt (%eax)
    mov %ebp, %esp
    pop %ebp
    ret

.globl getIDTaddr
getIDTaddr:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax
    lidt (%eax)
    mov %ebp, %esp
    pop %ebp
    ret
