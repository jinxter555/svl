%%module mod1
%call  fun2
push_c 123
push_c 456
push_c 789
%call fun1
exit
%%function fun1
%%lvar myint1 5
%%lvar myfloat1 6.78
%%lvar myint3 7
mov r1, 12345
mov r2, 3.45
push_c 11
push_c 22
push_c 33
push_c 44.44
ret
%%function fun2
%%lvar myfloat1 1.2
%%lvar myfloat2 3.45
mov r1, 12345
mov r2, 3.45
push_c 111
push_c 222
push_c 333
push_c 444.44
ret
