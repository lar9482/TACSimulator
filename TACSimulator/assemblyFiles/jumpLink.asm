function1:
    movI r10, 1000
    movI r11, 2000
    movI r12, 3000
    movI r13, 4000
    jmpReg rRET

function2:
    movI r10, 10
    movI r11, 20
    movI r12, 30
    jmpReg rRET

main:
    jmpL function1
    movI rRET, 0

    movI r4, 20
    jmpL_Reg r4
    movI rRET, 0