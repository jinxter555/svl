module Kernel 
  def main (x y)
    #load "fib_5.lisp"
    #load "use_build_1.lisp"

    var v list1
    = list1 ( 11 22 33 44 55)

      (p1 list1 (+ 3 4 5))
      # p2(list1)

      loop
        print (eval (read)) "\n"
      end.loop
  end.def

  def p1(myl x)
    print "p1(myl) " myl "\n"
    index 0 myl :set 5555
    print "p1(myl) " myl "\n"
    print "x second: "  x "\n"

      loop
        print (eval (read)) "\n"
      end.loop

  end.def

end.module
