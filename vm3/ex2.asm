%%module mod2
push_c 888888
%call mod2:fun2 
exit
%%function fun1
%%larg xyz
%lvar i1 9999999
%lvar i1 10
%lvar i2 20
%lvar i3 30
%load_l r4, xyz
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
%load_l r0, xyz
%load_l r2, i1
push_c 2222
ret_np 1
