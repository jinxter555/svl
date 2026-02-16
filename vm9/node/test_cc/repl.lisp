module Kernel 

  def repl ()
    var input

    ;while [true]

     [input = \(car (read))]
      print "input: " input "\n"

      if [ input == "exit"]
      (
        print "equal\n"
        return :ok
      )
      end.if

      print "continue!\n"


  end.def


  def main (x y)
    print "hello main\n"
    repl()
  end.def

  def f1 ()
    print "here in f1\n"
    return :ok
  end.def

end.module
