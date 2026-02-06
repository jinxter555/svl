(module Kernel 
  (defun main (x y) my_func_des
    (
      (print "hello, world1\n")
      (Main.main 1 2)
    )
  )
)
(module Main 
  (defun main (x y) my_func_des
    (
    (print "hello, world2\n")
    Hello.p ()
    )
  )
)

module Hello
  def p ()
   print "Hola, world\n"
   Main.main 1 2
  end.def
end.module
