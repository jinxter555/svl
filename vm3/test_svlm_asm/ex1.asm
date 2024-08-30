%%module mod1
%call  fun2
exit
push_c 123
push_c 456
push_c 789
%call fun1
exit
%%function fun1
%lvar myint1 5
%lvar myfloat1 6.78
%lvar myint3 7
mov r1, 12345
mov r2, 3.45
push_c 11
push_c 22
push_c 33
push_c 44.44
ret
%%function fun2
%lvar myint1 12345
%lvar myint2 33
%lvar myfloat2 3.14159
%load_l r0, myint1
%load_l r1, myint2
%load_l r2, myfloat2
iadd_c r3, r1, 1
%store_l r0, myint1
push_c 111
push_c 222
push_c 333
push_c 444.44
ret
exit
