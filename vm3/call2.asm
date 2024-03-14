%%module mc2
%call mc2:main
exit
%%function main
#
#
#
%lvar i1 101
%lvar i2 102
%lvar i3 103
%call mc2:fun2 r7 i1 i2 i3
ret 
%%function fun2
%%larg i3
%%larg i2
%%larg i1
%load_l r0, i1
%load_l r1, i2
%load_l r2, i3
iprint r0
iprint r1
iprint r2
ret
