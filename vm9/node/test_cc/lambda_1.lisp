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
          (print "hello world123\n")
          print x
        end.lambda
        5 6 7
      )

     # ((lambda (number) (* 7 number)) 3)

      # funcall l1 1 "holy shit"
  end.def 
end.module
