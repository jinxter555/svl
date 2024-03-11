%%module mod2
%mvar a [1 2 3 4 5 6 7.8]
%mvar b 3 []
%mvar c 123
push_c 888889
#
%call  init_ds
%call mod2:fun2 
%call mod2:fun2 
exit
%%function init_ds
%mvar v1 1111
%mvar v2 2222
%mvar v3 3333
%mvar hello 8888
ret
%%function fun1
%%larg xyz
%lvar i1 9999999
%lvar i1 10
%lvar i2 20
%lvar i3 30
%load_l r4, xyz
iprint r4
mov r1, 12345
mov r2, 3.45
push_c 11
push_c 22
push_c 33
ret 0
%%function fun2
%%larg xyz
%lvar return_value1 11
%lvar return_value2 12
%lvar i1 1
%lvar i3 3
%load_g r0, r5, hello
iprint r0
iadd_c r0, r0, 1
%store_g r0, r5, hello
%load_l r0, xyz
%load_l r2, i1
push_c 2222
ret_np 1
