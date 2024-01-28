%module mod1
mov r0, 123
pushc 0
call fun1
call fun2
pushc 70
load r1, r2, 3
vmexit
%function fun1
pushc 11
pushc 22
pushc 33
ret
%function fun2
pushc 44
pushc 55
pushc 66
ret
