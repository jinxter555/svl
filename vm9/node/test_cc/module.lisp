(module Kernel 
  (def main (x y) 
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
  (def main (x y) 
    (
    (print "hello, world2\n")
    Hello.p ()
    )
  )
)

module Hello
  def p ()
   print "Hola, world\n"
  end.def
end.module
