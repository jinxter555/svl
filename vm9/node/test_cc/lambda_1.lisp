(module Kernel 
  (defun main (x y) my_func_des
    (
     (assign f1 (lambda (z) (print "hello")) )
     (assign f2 123)
     (assign f3 (defun abc (x y) (print "what is abc") ))
     (print "\n\nf3:\n" f3)
     (p55())
     (print "\n")
     (p55())
     (print "\n")
    )
  )
  (defun p55 () 
    (
     (print "p55\n")
     (assign f4 (defun abc (x y) (print "what is abc") ))
;     (print "\n\nf4:\n" f4)
    )
  )
)
