module Kernel 

  class Dict
    (var size (length 123) )
    def Dict(x)  
      (print "\n\nhello class constructor Dict()\n\n")
      ; (print this "\n\n");
      (print "x is: " x "\n")
    end.def

    def area(a pi)  
      (print "\nhello class Dict::area ()\n")
      (print "area is: " a "\n")
      (print "pi: " pi "\n")
;      (print this "\n")
    end.def

  end.class

  def main (x y)

    (assign x1 999)
    (assign m1 (new Dict))
    (send m1 :area 999 3.14)
    (print "hello, world1\n")
    print "x1: " x1 "\n"

    loop
      print (eval (read)) "\n"
    end.loop

  end.def

end.module
