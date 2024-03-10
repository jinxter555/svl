%%module mc1
%mvar pi 3.14
%call mc1:fun2 r7 mc1:pi
ret 
exit
%%function init_ds
%mvar e 2.8
ret
%%function fun2
%%larg xyz
%load_l r0, xyz
fprint r0
ret
