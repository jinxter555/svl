module Kernel 
  def main (x y)

      (assign l1 
        lambda  (x y)
            print "x " x "\n"
            print "y " y "\n"
            print "hello\n"
        end.lambda 
      )
      assign l2 "hello"

     (
        lambda  (x)
          (print "hello lambda \n")
          print x "\n"
          return  x
        end.lambda
        55555
      )

      # print "v1: " v1 "\n"

     # ((lambda (number) (* 7 number)) 3)

      # funcall l1 1 "holy shit"
  end.def 
end.module
