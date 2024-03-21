%%module mod2
push_c 888889
#
%call  init_ds
%call mod2:fun1 
%call mod2:fun2 
exit
#
#
#
%%function init_ds
%mvar a 3 [1 2 3]
%mvar b 2 []
%mvar c 2 [4 5 6]
%mvar d 5 [7 1]
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
fprint r2
push_c 11
push_c 22
push_c 33
ret 0
%%function fun2
%%larg xyz
%lvar return_value1 11
%lvar return_value2 12
%lvar i1 1
%lvar i2 5 []
%lvar i3 3
%load_l r0, i1
iprint r0
%load_l r0, i3
iprint r0
push_c 2222
ret
