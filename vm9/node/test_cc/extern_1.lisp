(module Kernel 
  (defun main (x y) my_func_des
    (
      (var m1 s1)
      (assign s1 "hello, world1\n")
      (assign m1 
        (map 
            (k1 123)
            (k2 456)
            (k3 456)
            (k4 (map(l1 456)))
        )
      )
      (print m1 "\n\n")
      (print "keys m1: " (call_extern (Map map_get_keys) m1 ()))
;      (call_extern (Map map_set_keys) m1 (pi 3.1415))
      (print "\n\n")
    )
  )
)
