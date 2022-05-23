
.globl Voronoid

@ unsigned short* screen - r0
@ const TPoint* points - r1
@ int npoints - r2
@ const unsigned short* palette - r3


Voronoid:
  stmdb   sp!,{r4,r5,r6,r7,r8,r9,r10,r11}     @ prolog

  mov r4,r0                                   @r4 = r0
  mov r5,r1                                   @r5 = rº
  mov r6,r2                                   @r6 = r2
  mov r7,r3                                   @r7 = r3

  mov r8,#0                                   @y = 0
for_y_loop:
  cmp r8,#160
  beq end_for_y

  mov r9,#0                                   @x = 0
for_x_loop:
  cmp r9,#240
  beq end_for_x

  mov r0,r5                                   @r0 = points
  mov r1,r6                                   @r1 = npoints
  mov r2,r9                                   @r2 = x
  mov r3,r8                                   @r3 = y

  bl Closest

  add r0,r0,r0
  ldrh r11,[r7,r0]
  strh r11,[r4],#2                            @*screen = palette [c]

  add r9,r9,#1                                @x++
  b for_x_loop

end_for_x:

  add r8,r8,#1                                @y++
  b for_y_loop

end_for_y:

  ldmia   sp!,{r4,r5,r6,r7,r8,r9,r10,r11}     @ epilog
  bx      lr
