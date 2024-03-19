%%module mod2
%mvar a [1 2 3]
%mvar b 3 [30]
%mvar c [4 5 6]
%mvar v1 1111
%mvar v2 2222
%mvar v3 3333
%mvar hello 8888
%mov_mv_adr r2, @hello
load_g r0, r2, 0
exit
