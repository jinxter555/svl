%%module mc1
%mvar pi 3.14
%call mc1:fun2 r7 mc1:pi
exit
%%function init_ds
%mvar e 2.8
ret
%%function fun2
%%larg xyz
%load_l r0, xyz
fprint r0
mov r1, 10
mov r7, 0
%%label loop1
#fprint r0
iprint r1
isub_c r1, r1, 1
cmpi r1, r7
%branch bgt loop1
iprint r1
ret
