module Kernel 
  (defun main (x y) "my func des" 
    (

      print "Macros!\n"
      mymac 1 2
      assign mvalue 55555
      mymac mvalue 33

      loop
        print (eval (read)) "\n"
      end.loop
    )
  )

  defmacro mymac (mx my)

    print "my mac1\n"
    quote
      assign y 2
      ;print "mx: " mx ", my: " my "\n"
      print ((unquote mx) " " my "\n")
    end.quote

  end.defmacro

  def l1 ()
    5
    8
  end.def

  def l2 ()
    7 9
  end.def

  def l3 ()
    1 2 3
    4 5 6 7 
    8 9
  end.def

  def l4 ()
    print 
    print 
    print 
  end.def

end.module
