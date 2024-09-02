loopBody:
    addI r3, r3, 1
    addI r1, r1, 1
    bLt r1, r2, loopBody
    jmp exit

main:
    movI r1, 0
    movI r2, 100

    jmp loopBody

exit: