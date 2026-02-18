module Kernel 
  def main (x y) 
    var forever (t true)
    assign t1  "t1 robot"
    assign forever false

    iif(t) 
      (print "forever: " forever "\n" )
      (print "sometimes, forever " forever "\n" )
    end.iif

    My.Mod1.p1()
    = f1 (new System.Io.File)
    System.Io.p1()
    

  end.def

end.module

module My.Mod1
  def p1 ()
      print "p1\n"
  end.def
end.module

module System.Io
  class File
    var file_name

    def File()
      print "file init!\n"
    end.def
  
    def open()
      print "opening a file!\n"
    end.def
  end.class

  def p1()
    print "system io p1\n"
  end.def


end.module
