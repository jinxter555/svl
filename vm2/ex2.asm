%module example2
pushc 1
pushc 2
call myfunc
pushc 3
mov r1, 3
call myfunc
mov r2, 6
muli r0, r1, r2
## function name and so
%function myfunc
muli r0, r1, r2
