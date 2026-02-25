module Kernel 
  class Car
    var car_type
    def initialize()
      = @car_type  123

      print  "car init\n"
    end.def

    def finalize(x)
      print  "car fin\n"
    end.def

  end.class



  class Dict
    (var size (length 123) w c1)

    def initialize(w1 w2 w3)  
      print "Dict w1: " w1 "\n"
      = @w w1

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


  class Dict2
    var 

    def initialize(w1 w2 w3)  
      print "Dict2 w1: " w1 "\n"
    end.def

    def area(a pi)  
      print "\nhello class Dict2::area ()\n"
      print "area is: " a "\n"
      print "pi: " pi "\n"
    end.def

    def finalize()
      print  "Dict2 finalize destructor!\n\n"
    end.def

  end.class



  def main (x y)

    (var m1)

    = m1 (new Dict "ship building" "world1" "trade")
    = m2 (new Dict2 "construction" "fishery" "saliing")

    f1()

    loop
       print ( eval (read)) "\n"
    end.loop

  end.def

  def f1 ()
    var m1 m2 i1
    = i1 111111
    = m1 (new Dict "webster1  " "global" "affairs")
    = imm1(new Dict "webster2 " "global" "affairs")
    = m2 (new Dict2 "webster h222 using dict2  " "global" "affairs")
    f2()


  end.def

  def f2 ()
    var m2 i1
    = i2 211111
    = m2 (new Dict "webster11  " "global" "affairs")
    = imm1(new Dict "webster22 " "global" "affairs")
  end.def

end.module
