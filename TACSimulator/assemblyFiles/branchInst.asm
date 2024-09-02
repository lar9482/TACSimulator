notEqual:
    movI r5, 432
    movI r6, 6746
    jmp branch2

isEqual:
    movI r7, 300
    movI r8, 400
    jmp exit

main:
    movI r1, 100
    movI r2, 200
    bNe r1, r2, notEqual

branch2:
    movI r3, 100
    movI r4, 100
    bEq r3, r4, isEqual

exit: