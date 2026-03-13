(module Kernel 
  (def main (x y)
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
