.text
.globl loadPageDirectory
loadPageDirectory:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax
    mov %eax, %cr3
    mov %ebp, %esp
    pop %ebp
    ret

.globl enablePaging
enablePaging:
    push %ebp
    mov %esp, %ebp

    mov %cr0, %eax
    or $0x80000000, %eax
    mov %eax, %cr0
    mov %ebp, %esp

    pop %ebp
    ret


// fonction de test
.global _getValue
getValue:
    push %ebp
    mov %esp, %ebp

    mov %cs, %eax

    mov %ebp, %esp
    pop %ebp
    ret
