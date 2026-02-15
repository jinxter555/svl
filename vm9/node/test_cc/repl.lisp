module Kernel 
  def repl ()
    ;var (i 0)
    ;print "hello\n"
    while (true)
    ;while [ true ]
      print "hello2\n"
    end.while
  end.def

  def repl2 ()
    var (i 0)
    while [i < 10]
      print "i " i "\n";
      [i = i+1]
    end.while
  end.def

  def main (x y)
 ;   repl()
;    repl2()

    while (true)
    ;while [ true ]
      print "hello2\n"
    end.while


  end.def

  def f1 ()
    print "here in f1\n"
    return :ok
  end.def

end.module
