(module Kernel 
  (defun main (x y) "my func des" 
    (
      (print "hello, world")
      (call (Kernel p55) (1 2))
    )
  )
  (defun p55 (x y) "my func p55" 
    (
      (print "hello, p55, 55\n")
      (call (Kernel p56) (1 2))
    )
  )
  (defun p56 (x y) "my func p56" 
    (print "hello, p56, 56\n")
  )
)
