module Kernel 

  class Dict
    (var size (length 123) )
    def Dict(x)  
      (print "\n\nhello class constructor Dict()\n\n")
      ; (print this "\n\n");
      (print "x is: " x "\n")
    end.def

    def area(a)  
      (print "hello class Dict::area ()\n")
      (print "area is: " a "\n")
;      (print this "\n")
    end.def

  end.class

  def main (x y)
    (print "hello, world\n")
    (assign m1 (new Dict))
    (assign x1 999)
    (assign method1 (:Dict))
;      (p55 (55 2))
;      (print "\n\n")
;    (print m1 "\n\n")
    ;(send m1 (:Map 555 666 777 888 x1))
;    (send m1 (:Dict 555))
    (send m1 (:area 999))

    ;(send m1 ((method1) 555))
  end.def
end.module
