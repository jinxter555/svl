module Kernel 
  defun main (x y) 
    (print (p55 (11111 22222)) "\n")
    (print (p56 ()) "\n\n")
    assign 
      (x 5)
      (y [2+x])
    end.assign

    case(x)
      (7 do (print "is 7") end)
    when 7 (print 7) end.when
    end.case

    print 
      "x " x
      (p55 (11111 22222)) "\n" 
    end.print

    if [ a > 1 ] then 
    else 
    end.if

  end.defun

  defun p55 (x y)  
    for range(1..10)  
      do (i) 
        (print i)
      end
    end.for
  end.defun

  class myclass

  end.class
end.module
