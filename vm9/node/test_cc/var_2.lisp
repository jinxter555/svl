(module Kernel 
  (defun main (x y) my_func_des
    (
;    (print "hello, world1\n")    (print "hello, world2\n")
    (var v1 (v2 (vector 12345 3457)) (v3 3.14159) (s1 "hello") (s2 "world"))
    (assign v1 "what is up")
    (assign v5 "hello v5")
    (assign v5 "hello v555")
    (print v5 "\n")
    (print v2)
    (print v3 "\n")
    (print "hello literal!! (v2 v3): " (literal v2 v3 (1 2 3))  "\n")
    ; (p55 (11111 22222))
    (p55 (11111 v2))
    )
  )


  (defun p55 (x y) "my func p55" 
    (
      (print "hello, p55, 55\n")
      (print x; print out x 
             "\n" ; print new
             y "\n"; new line
            )
    )
  )

)
