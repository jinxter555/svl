(module Kernel 
  (defun main (x y) my_func_des
    (
      (assign l1 
        (lambda  (x y)
          (
            (print "x " x "\n")
            (print "y " y "\n")
            (print "hello world123\n")
          )
        )
      )
      (funcall l1 1 "holy shit")
    )
  )
)
