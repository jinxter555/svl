module Kernel 
  (defun main (x y) "my func des" 
    (

      ;var my
      print "Macros2!\n"
      assign my 55555
      mymac 22222 mvalue

      loop
        print (eval (read)) "\n"
      end.loop
    )
  )

  defmacro mymac (mx my)
    quote
      print (unquote mx) " " my " " "\n"
      print 1 2 3 "\n"
    end.quote

    quote
      print 4 5 10 "\n"
      print (unquote mx) " " my " " "\n"
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
