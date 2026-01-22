(module Kernel 
  (defun main (x y) my_func_des
    (
      (assign l1 
        (lambda  (x y)
          (
            (print "x " x "\n")
            (print "y " y "\n")
            (print "hello world l1 123\n")
            (x)
          )
        )
      )
      (assign l2 "hello")
;      (print "lambda l1: " l1 "\n")

; this prints out returned map shoudl be evaluated in vector for loop lispeval
      ( (lambda  (x )
;          (print "x " x "\n")
          (print "hello world anonymous 123\n")
        )
       5
      )
      (print (funcall l1 222222 "holy shit") "\n")
    )
  )
)
