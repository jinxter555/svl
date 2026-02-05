module Kernel 
  class Dict
    (var size (length 123) )

    def Dict(w1 w2 w3)  
      ; print "\n\nhello class constructor Dict()\n"
      print "w1: " w1 "\n"
      ;loop
      ;  print ( eval (read)) "\n"
      ;end.loop
    end.def

    def area(a pi)  
      print "\nhello class Dict::area ()\n"
      print "area is: " a "\n"
      print "pi: " pi "\n"
    end.def
  end.class

  def main (x y)


    (assign x1 999)
    assign m1 (new Dict "ship building" "world1" "trade")


    ;assign m1 (new Dict "ship building" "world1" "trade")
    ;assign m2 (new Dict "ship building" "world1" (* 5 6) ))

;    assign m2 (new Dict "ship building" "world1" "trade")

;    send m1 :Dict "my word" 1 (+ 3 5)
  ;  send m1 (:Dict ("my dictionary" 1 2))
;    send m1 :area 999 3.14

;    print "hello, world1\n"
;    print "x1: " x1 "\n"  

  ;  print "v1: " v1 "\n\n"
      loop
        print ( eval (read)) "\n"
      end.loop

  end.def

end.module
