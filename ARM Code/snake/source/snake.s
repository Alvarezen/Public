
.globl UpdateSnake

@ static int UpdateSnake (int keypad, Snake* snake, unsigned short* screen)
@ int keypad r0
@ Snake* snake r1
@ unsigned short* screen r2


UpdateSnake:
  stmdb   sp!,{r4,r5,r6,r7,r8,r9,r10,r11,r12,r14}     @ prolog

  mov r3,#0                            @int crash = 0
  ldr r4,[r1]                          @Slab* slabs = snake->slabs
  ldrh r5,[r1,#6]                      @int head_slab = snake->head_slab
  add r6,r5,#1                         @int tail = snake->head_slab + 1

  ldrh r7,[r1,#4]                      @snake->len
  cmp r6,r7                            @tail >= snake->len
  movge r6,#0                          @tail == a 0

  add r8,r4,r6,lsl #3                  @slabs[tail]
  ldr r9,[r8]                          @slabs[tail].x
  ldr r10,[r8,#4]                      @slabs[tail].y
  mov r11,#240                         @r11  = 240
  mul r11,r11,r10                      @slabs[tail].y * 240
  add r11,r11,r9                       @slabs[tail].x + slabs[tail].y * 240
  add r11,r11,r11
  mov r12,#0                           @r12 = 0
  strh r12,[r2,r11]                    @screen[slabs[tail].x + slabs[tail].y * 240] = 0

  add r8,r4,r5,lsl #3                  @slabs[snake->head_slab].x
  ldr r9,[r8]                          @new_x = slabs[snake->head_slab].x
  ldr r8,[r8,#4]                       @new_y = slabs[snake->head_slab].y

  add r5,r5,#1                         @head_slab++;

  cmp r5,r7                            @head_slab >= snake->len
  movge r5,#0                          @head_slab = 0
  strh  r5,[r1,#6]                     @snake->head_slab = head_slab;

  ldr r10,[r1,#8]                      @int speed_x = snake->speed_x;
  ldr r11,[r1,#12]                     @int speed_y = snake->speed_y;


  cmp r0,#0                            @keypad != 0
  beq if_keypad
  mov r10,#0                           @speed_x = 0
  mov r11,#0                           @speed_y = 0
  ands r14,r0,#1                       @keypad & 1
  movne r10,#1                         @speed_x = 1
  ands r14,r0,#2                       @keypad & 2
  movne r10,#-1                        @speed_x = -1
  ands r14,r0,#4                       @keypad & 4
  movne r11,#-1                        @speed_y = -1
  ands r14,r0,#8                       @keypad & 8
  movne r11,#1                         @speed_y = 1

  str r10,[r1,#8]                      @speed_x
  str r11,[r1,#12]                     @speed_y

if_keypad:

  add r9,r9,r10                        @new_x += speed_x;
  add r8,r8,r11                        @new_y += speed_y;

  mov r11,#240                         @240
  mul r11,r8,r11                       @new_y * 240
  add r11,r11,r9                       @(new_x + new_y * 240)
  add r11,r11,r11                      @r9 x 2 para el puntero screen
  add r11,r11,r2                       @head_pix = screen + (new_x + new_y * 240)

  ldrh r12,[r11]                       @*head_pix
  cmp r12,#0                           @*head_pix == 0
  moveq r10,#-1                        @white
  streqh r10,[r11]                     @if (*head_pix == 0)

  addeq r12,r4,r5,lsl #3               @slabs[head_slab].x
  streq r9,[r12]                       @slabs[head_slab].x = new_x
  streq r8,[r12,#4]                    @slabs[head_slab].y = new_y
  movne r3,#1                          @crash = 1
  mov r0,r3                            @return crash

  ldmia   sp!,{r4,r5,r6,r7,r8,r9,r10,r11,r12,r14}     @ epilog
  bx      lr
