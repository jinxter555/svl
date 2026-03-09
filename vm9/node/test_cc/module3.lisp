module Kernel 
  var gvalue
  def main (x y) 
     use :global Kernel
  
     var (v1 "hola mundo") (v2 "halo welt")
     print "hello "
     print "world\n" 
     print v1 ", " v2 "\n"
     p55 88888888
     loop
        print (eval (read)) "\n"
      end.loop
  end.def

  def p55(value)
    print "p55 hello\n" 
    print "x value:" value "\n"
      loop
        print (eval (read)) "\n"
      end.loop
  end.def
end.module

module Another
  var my_var1 my_int2 my_map3
end.module
