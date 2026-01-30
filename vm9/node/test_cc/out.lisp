line print "hello, world from main()\n\n" no paren!line result:
module Kernel
def main (x y)
(print "hello, world from main()\n\n")
end.def
defun p55 (x y) "my func p55"
end.defun
defun p56 (x y) "my func p56"
end.defun
def p57 (x y)
end.def
end.module

input paren: module Kernel
def main (x y)
(print "hello, world from main()\n\n")
end.def
defun p55 (x y) "my func p55"
end.defun
defun p56 (x y) "my func p56"
end.defun
def p57 (x y)
end.def
end.module

eval vector!
In Module.Function: Kernel.Main
[Error: SymbolNotFound] print