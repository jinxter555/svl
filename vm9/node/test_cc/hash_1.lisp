(module Kernel 
  (defun main (x y) my_func_des
    (
      (var m1)
;      (print "hello, world1\n")
      (assign m1 
      (hash 
            (k1 123)
            (k2 456)
            (k3 456)
            ))
      loop
        (print(eval (read)) "\n")
      end.loop
    )
  )
)
