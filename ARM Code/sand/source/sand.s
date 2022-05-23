
	.globl UpdateParticles

@ Particle* particles r0
@ int nparticles r1
@ unsigned short* screen r2

UpdateParticles:
  stmdb   sp!,{r4,r5,r6,r7,r8,r9,r10,r11,r12,r14}     @ prolog

loop_do:

if_particles_alive:

	ldrb r4,[r0,#2]    				@particles->alive
	cmp r4,#0           			@if particles->alive
	beq end_if_not_alive

	ldrb r5,[r0]
	ldrb r12,[r0,#1]

	mov r10,#240
	mul r6,r12,r10          		@SCREEN_W * y
	add r6,r6,r5         			@[x + SCREEN_W * y]
    add r6,r2,r6,lsl #1  			@&screen [x + SCREEN_W * y]

	add r7,r6,#480       			@current + SCREEN_W
	mov r8,#66           			@int new_x = 66

	ldrh r9,[r7]          			@down[0] == BLACK
	cmp r9,#0						@if down[0] == BLACK
	moveq r8,#0
	beq if_new_x


	ldrh r9,[r7,#-2]
	cmp r9,#0            			@down[-1] == BLACK
	moveq r8,#-1
	beq if_new_x

	ldrh r9,[r7,#2]
	cmp r9,#0            			@down[1] == BLACK
	moveq r8,#1

if_new_x:


	cmp r8,#66						@new_x != 66
	movne r9,#0
	strneh r9,[r6]  				@*current = BLACK
	movne r9,#-1
	addne r11,r8,r8
	strneh r9,[r7,r11]				@down[new_x] = WHITE

	addne r11,r8,r5
	strneb r11,[r0]					@particles->x = x + new_x
	addne r11,r12,#1
	strneb r11,[r0,#1]				@particles->y = y + new_y

	moveq r11,#0
	streqb r11,[r0,#2]				@particles->alive = 0

end_if_not_alive:

  add r0,r0,#4         				@particles ++
  subs r1,r1,#1         			@nparticles --
  bne loop_do



  ldmia   sp!,{r4,r5,r6,r7,r8,r9,r10,r11,r12,r14}     @ epilog
  bx      lr
