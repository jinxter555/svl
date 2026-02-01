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

    case x
    when (> x 5) 
      print "x is > 5"
    end.when
    when (< x 3) 
      print "x is < 3"
    end.when
    end.case

    case x
    (> x 5) ( print ) 
    (< x 3) ( print ) 
    end.case

    case x
    [x > 5] do print end.do
    [x < 3] do print end.do
    end.case

    case x
    [x > 5] (print )
    [x < 3] (print )
    end.ase

    case x
    (:ok, v) (print )
    [x < 3] (print )
    end.ase

    case x
    (1) (print)
    [> 5] (print )
    [< 3] (print )
    end.case

  end.def


end.module


end.defun
