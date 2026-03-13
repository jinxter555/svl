module Kernel 
  def main (x y)
    print "call l1()\n"

    loop
        print (eval (read)) "\n"
    end.loop
  end.def 


  def l1()
      (
        lambda  (x)
          print "x is : " x "\n"
          (print "hello world123\n")
        end.lambda 
        5
      )
  end.def
end.module


