module Kernel 
  class Range
    (var state fin step state)

    def Range(start fin step)  
      ; assign needs to return a value
      assign this.state start
      assign this.fin fin
      assign this.step  step

    end.def

    def init()  
    end.def

    def next ()
      assign this.state (+ this.state this.step)
      ;print "i am in next(v): \n"
      
    end.def

  end.class

  def main (x y)

    (assign x1 999)
    assign r1 (new Range 1 5 1)
    send r1 :next 

      loop
        print (eval (read)) "\n"
      end.loop


  end.def

end.module
