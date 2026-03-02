(module Kernel 
  (def main (x y)
    (
     (var m1)
      (assign m1 
      (hash  \
            (k1 123) \
            (k2 456) \
            (k3 456) \
            (k4 (hash(l1 456))) \
      ))

      = l1 (ihash (:abcd "hello") (:a2 "world"))
      print "l1: " l1 "\n"

      loop
        print "Map:m1 "  m1 "\n\n"
        print (eval (read)) "\n"
      end.loop


    )
  )
)
