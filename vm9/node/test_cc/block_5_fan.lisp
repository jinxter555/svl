module Kernel 

  class Map
    (var size (length 123) )
    def Map(x)  
     (print "hello class mp1()\n")
    end.def

  end.class

  def main (x y)
    print "hello, world\n"
    assign m1 (new Map)
    assign method1 (:Map)
;      (p55 (55 2))
;      (print "\n\n")
    print m1 "\n\n"
    send m1 (:Map 555)
    send m1 ((method1) 555)
  end.def
end.module
