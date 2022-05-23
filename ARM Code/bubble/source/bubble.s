
.globl SortArray

@ static void SortArray (int *array, int len)
@ int *array - r0
@ int len - r1

SortArray:
  stmdb   sp!,{r4,r5,r6,r7,r8}     @ prolog


while:
 cmp r1,#1
 ble end_while

 mov r3,#1						          @int ordered = 1
 mov r4,#0						          @int i = 0 del for
 sub r8,r1,#1                   @len - 1

for:

 cmp r4,r8                      @array[i] > array[i+1]
 bge end_for

 ldr r5,[r0,r4, lsl #2]					@array[i] -> *(array + i) -> t
 add r6,r4,#1					    		  @(i + 1)
 ldr r7,[r0,r6, lsl #2]					@array[i+1] -> *(array + (i + 1))

 cmp r5,r7                      @array[i] > array[i+1]
 ble end_if

 str r7,[r0,r4, lsl #2]					@escribiendo en la dirección de memoria r6 el valor r9
 str r5,[r0,r6, lsl #2]
 mov r3,#0

end_if:

 add r4,r4,#1
 b for

end_for:

 sub r1,#1                      @len--

 cmp r3,#0
 beq end_if2
 mov r1,#0                      @len = 0

end_if2:
  b while
end_while:

  ldmia   sp!,{r4,r5,r6,r7,r8}    @ epilog
  bx      lr
