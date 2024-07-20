main:

    movI r2, 200
    movI r3, 300
    movI r4, 400

    movI r1, -1000
    sw r1, 0[r2]
    sw r1, -10[r3]
    sw r1, 10[r4]
    
    lw r5, 0[r2]
    lw r6, -10[r3]
    lw r7, 10[r4]

    movI r8, 800
    movI r9, 900
    movI r10, 1000

    movI r11, 255
    sb r11, 0[r8]
    sb r11, -10[r9]
    sb r11, 10[r10]

    lb r12, 0[r8]
    lb r13, -10[r9]
    lb r14, 10[r10]