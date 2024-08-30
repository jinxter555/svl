%%module mc1
%mvar gold 1.878
%call init_ds
# %call mc1:fun2 r7 mc1:e
%call mc1:fun2 r7 @pi
ret 
exit
%%function init_ds
%mvar pi 3.14
%mvar e 2.8
ret
%%function fun2
%%larg xyz
%load_l r0, xyz
fprint r0
ret
