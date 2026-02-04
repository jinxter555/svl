module Kernel 
  def main (x y) 
    (var forever)
    (assign t1  "t1 robot")
    (assign forever true)

    while (forever) 
      print "forever: " forever "\n"
      print (eval (read)) "\n"
    end.loop
  end.def
end.module
