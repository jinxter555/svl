module Kernel 

  class Car
    var car_type
    def initialize()
      = @car_type  123

      print  "car init\n"
    end.def

    def finalize()
      print  "car fin\n"
    end.def

  end.class

  class Dict
    (var size (length 123) w c1)

    def initialize(w1 w2 w3)  
      print "Dict init:  " w1 "\n"
      = @w w1
      = @c1 (new Car  )

    end.def

    def area(a pi)  
      print "\nhello class Dict::area ()\n"
      print "area is: " a "\n"
      print "pi: " pi "\n"
    end.def

    def finalize()
      print @w " Dict finalize destructor!\n\n"
    end.def

  end.class


  def main (x y)

    (assign x1 999)

    f1()

    loop
       print ( eval (read)) "\n"
    end.loop

  end.def

  def f1 ()
    var m1 
    print "f1\n"
    = m1 (new Dict "webster11  " "global" "affairs")
  end.def

end.module
