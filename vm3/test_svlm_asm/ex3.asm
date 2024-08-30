%module example2
%function myfunc1
pushc 1
pushc 2
pushc 3
%function myfunc2
mov r1, 3
mov r2, 6
muli r0, r1, r2
%function myfunc3
muli r0, r1, r2
call myfunc2
