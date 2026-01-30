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
  ;  (print "hello, world\n")
(    assign m1 (new Dict))
    assign x1 999
;    (assign method1 (:Dict))
   (send m1 :area 999 3.14)
  ;  send m1 :area x1 3.1415
  ;  send m1 :area x1 

  end.def
end.module
