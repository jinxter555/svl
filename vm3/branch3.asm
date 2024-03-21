%%module mod2
%call main
exit
%%function main
%call  init_ds
%mov_mv_adr r2, @str1
iprint r2
# %call mod2:print_string r7 @str1  # @str1 will return the value that is array size
%call mod2:print_mstring r2 r2
ret
%%function init_ds
%mvar v1 3.145
%mvar v2 123
%mvar str1 "this is Delphia represented that it used artificial intelligence and machine learning to analyze its retail clients' spending and social media data to inform its investment advice when, in fact, no such data was being used in its investment process, the SEC said in a settlement order. Despite being warned about suspected misleading practices in 2021 and agreeing to amend them, Delphia only partially complied, according to the SEC. The company continued to market itself as using client data as AI inputs but never did anything of the sort, the regulator said.123"
ret
#%%call print_string r7, @str1
#ret 0
%%function print_mstring 
%%larg mstring 
mov r7, 1

%load_l r0,  mstring  ## r0 has the address
load_g r1, r0, 0     ## r1 has the array size
load_g r2, r0, 1     ## r2 has the string buffer size
iadd_c r0, r0, 2     ## r0, set r0 to the begining of stirng buffer

%%label loop1 # this is it
#iprint r7

load_g r3, r0, 0
cprint r3


iadd_c r0, r0, 1
iadd_c r7, r7, 1
cmpi r1, r7
%branch bge loop1

%%label  endprint
ret
