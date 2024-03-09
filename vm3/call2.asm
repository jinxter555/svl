%%module mc2
%call mc1:main
exit
%%function main
%lvar i1 101
%lvar i2 102
%lvar i3 104
%call mc1:fun2 r7, i1, i2
ret 
%%function fun2
%%larg x
%%larg y
%lvar return_value1 11
%lvar return_value2 12
%lvar i1 1
%lvar i3 3
%load_l r1, x
%load_l r2, y
push_c 2222
ret_np 1
