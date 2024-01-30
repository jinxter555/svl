#pragma once
#define VM_vmexit        0      // prevent buffer overlow 
#define VM_noop        1      // no op
#define VM_mov        10

#define VM_pushc      11      // push constant
#define VM_pushr      12      // push register
#define VM_popr       13      // push register

#define VM_load        14
#define VM_store        15

#define VM_addi       21
#define VM_subi       22
#define VM_muli       23
#define VM_divi       24
#define VM_call       33      // push register
#define VM_ret        34      // push register

#define VM_cmpi       35
#define VM_cmpf       36
#define VM_beq        37
#define VM_bgt        38
#define VM_blt        39