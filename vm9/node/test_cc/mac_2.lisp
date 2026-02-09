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

    quote
      print ((unquote mx) " " my " ")
      print 1 2 3
    end.quote

    quote
      print 4 5 10
      print ((unquote mx) " " my " ")
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
