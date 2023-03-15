    .globl Reset

Reset:
    ldr r0, =(stack_top)
    mov sp, r0
    bl start_kernel
    b .
    