%%module mc1
push_c 888888
%call mc1:main
exit
%%function main
%lvar i1 1000000
mov r2, 3.45
%call mc1:fun2 r7, i1
ret 
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
