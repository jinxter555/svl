(module Kernel 
  (defun main (x y) "my func des" 
    (
      (var (x "xxx"))
      (print "hello, world\n")
      (call (Kernel p55) (5555 2))
      (print "\n")
      (p55 (55 2))
      (print "\n\n")
      loop
        print (eval (read)) "\n"
      end.loop
    )
  )
;        print (car (eval (read))) "\n"
  (defun p55 (x y) "my func p55" 
    (
      (var (z "zzz"))
      (print "hello, p55, 55\n")
      (print "x: " x "\n")
      (print "(x): " (x) "\n")
      (print "(y): " (y) "\n")
      (print "\n")
      (print "-" x "-")
      (print "-" z "-")
      (print "\n")
    ;  print (root) "\n"
    ;  (p56 (66 2))
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
  defmacro mymac ()
    assign x 1
    print "my mac1\n"
  end.defmacro
)
