%%module mod2
#%call  init_ds
#%call mod2:fun1 
exit
%%function init_ds
# %mvar str1 "this is Delphia represented that it used artificial intelligence and machine learning to analyze its retail clients' spending and social media data to inform its investment advice when, in fact, no such data was being used in its investment process, the SEC said in a settlement order. Despite being warned about suspected misleading practices in 2021 and agreeing to amend them, Delphia only partially complied, according to the SEC. The company continued to market itself as using client data as AI inputs but never did anything of the sort, the regulator said."
ret
%%function fun1
%%call print_string r7, @str1
ret 0
%%function print_string 
%%larg mstring 
%load_l r0, r5, mstring
iprint r0
ret
