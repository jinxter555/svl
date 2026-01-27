%%module  kernel

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

    for (1 10) 
      do (i) 
        print i
      end
    end.for

    for (1..3) (i)
      print i
    end.for

    for (map) (k v) 
    end.for

    for (map)
      do (k v) 
      end
    end.for

    while [infix] do
    end.while

    repeat
      print i
    until [infix] 
    end.repeat

  end.def

end.module
