fim 0p $08
fim 1p $0d
ldm $0
xch r4
xch r5

clc
ld r1
add r3
xch r5

jms car

clc
ld r0
add r2
clc
add r4
xch r4

jun jmp
car,
jcn c0 crr

ldm $1
xch r4

crr,
bbl 0
jmp,