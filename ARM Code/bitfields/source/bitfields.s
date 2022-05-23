
	.globl Paint

@ static void Point (nsigned short* dst, unsigned char* sprite, int stride_pixels, unsigned int color)
@ short* dst r0
@ unsigned char* sprite r1
@ int stride_pixels r2
@ unsigned int color r3

Paint:
  stmdb   sp!,{r4,r5,r6,r7,r8,r9,r10,r11,r12,r14}     @ prolog

  mov r4,#0x1F
  and r5,r3,r4														@int ball_r = color & 0x1f;
  and r6,r4,r3,lsr #5											@int ball_g = (color >> 5) & 0x1f
  and r7,r4,r3,lsr #10										@int ball_b = (color >> 10) & 0x1f

  mov r8,#0																@int side = BALL_SIDE

for_loop:

  cmp r8,#16															@y<side
  bge for_end

  mov r9,#0																@y=0

for_loop_2:

  cmp r9,#16															@x<side
  bge for_end_2

  ldrb r10,[r1]
  add r1,r1,#1

  cmp r10,#0
  beq end_if

  ldrh r10,[r0]

  and r11,r10,r4													@r = back_color & 0x1f;
  add r12,r11,r11,lsl #1								 	@r + (r << 1)
  add r12,r12,r5													@r + (r << 1) + ball_r
  mov r11,r12,asr #2											@r = ((r << 1) + r + ball_r) >> 2;

  and r12,r4,r10,lsr #5
  add r14,r12,r12,lsl #1 									@r + (r << 1)
  add r14,r14,r6													@r + (r << 1) + ball_r
  mov r12,r14,asr #2											@g = ((g << 1) + g + ball_g) >> 2;

  and r14,r4,r10,lsr #10
  add r10,r14,r14,lsl #1 									@r + (r << 1)
  add r10,r10,r7													@r + (r << 1) + ball_r
  mov r14,r10,asr #2											@b = ((b << 1) + b + ball_b) >> 2;

  orr r10,r11,r12,lsl #5									@(back_color >> 5)
  orr r10,r10,r14,lsl #10									@(back_color >> 10)
  strh r10,[r0]

end_if:

  add r0,r0,#2
  add r9,r9,#1

  b for_loop_2
for_end_2:

  sub r10,r2,#16													@stride_pixels - side
  mov r12,#2
  mul r10,r10,r12
  add r0,r0,r10

  add r8,r8,#1			

  b for_loop

for_end:


  ldmia   sp!,{r4,r5,r6,r7,r8,r9,r10,r11,r12,r14}    @ epilog
  bx      lr
