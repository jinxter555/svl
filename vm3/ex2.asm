%%module mod2
%call mod2:fun2
exit
%%function fun1
%lvar i1 10
%lvar i2 20
%lvar i3 30
#%load_l r1, i3
mov r1, 12345
mov r2, 3.45
push_c 11
push_c 22
push_c 33
ret 0
%%function fun2
push_c 2222
ret 0
