(module Kernel 
  (defun main (x y) "my func des" 
    (
      (print "hello, world\n")
      (print "using call (...) \n")
      (call (Kernel p55) (5555 2))
      (print "\nusing identifier (...) \n")
      (p55 (55 2))
      (print "\n\n")
    )
  )
  (defun p55 (x y) "my func p55" 
    (
      (print "hello, p55, 55\n")
      (print (x))
      (print "\n")
      (print "-" x "-")
      (print "-" z "-")
      (print "\n")
      (p56 (66 2))
    )
  )
  (defun p56 (x y) "my func p56" 
    (
      (print "hello, p56, 56\n")
      (print (x))
      (print "\n")
      (print "-" x "-")
      (print "\n")
    )
  )

)
