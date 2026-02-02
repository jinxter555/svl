module Kernel 

  class Dict
    (var size (length 124) )
    def Dict(x)  
      (var (that 555))
      print "hello class constructor Dict()\n"
      ;(print "arg x: " x "\n")
      ;print this
      ;(assign this.length 55555)
      ;print this


      loop 
        print (eval (read)) "\n" 
      end.loop
    end.def

    def area(a pi)  
      print "\nhello class Dict::area ()\n"
      print "area is: " a "\n"
      print "pi: " pi "\n"
      assign name "area"


;      (print this "\n")
    end.def

  end.class

  def main (x y)

    (assign x1 999)
    assign m1 (new Dict "hello dictionary")
    ; (send m1 :Dict "my dictionary")
    ;(send m1 :area 999 3.14)
    ;(print "hello, world1\n")
    ;print "x1: " x1 "\n"

    ; loop print (eval (read)) "\n" end.loop

  end.def

end.module
