%%module mod2
%call mod2:f1
exit
%%function f1
mov r1, 12345
mov r2, 3.45
push_c 11
push_c 22
push_c 33
ret
