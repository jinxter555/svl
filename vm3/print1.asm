%%module mod2
push_c 888889
#
%call  init_ds
%call mod2:fun1
exit
%%function init_ds
%mvar a [1 2 3]
%%mvar str1 "this is a test\n water is wet\t you don't want to walk on slipery side walk1"
%mvar b 3 [30]
%mvar c [4 5 6]
%mvar v1 1111
%mvar v2 2222
%mvar v3 3333
%mvar hello 8888
ret
%%function fun1
%load_g r0, r5, str1
iprint r0
iadd_c r5, r5, 1
%load_g r0, r5, str1
cprint r0
ret 
