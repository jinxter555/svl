(module Kernel 
  (defun main (x y) my_func_des
    (
      (print "hello, world1\n")
      (Main.main 1 2)
      loop
        print (eval (read)) "\n"
      end.loop
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
   ;Main.main 1 2
  end.def
end.module
