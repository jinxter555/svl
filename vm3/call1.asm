%%module mc1
%mvar pi 1234
%call mc1:fun2 r7, mc1:pi
ret 
%%function fun2
%%larg xyz
%load_l r0, xyz
iprint r0
ret
