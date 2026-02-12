module Kernel 
  class Range
    (var begin fin step state)

    def Range(start fin step)  
      ; assign needs to return a value
      assign @begin start
      assign @state start
      assign @fin fin
      assign @step  step

    end.def

    def init()  
      assign @state @begin
      (:ok @state)
    end.def

    def next ()
      assign @state (+ @state @step)
      if 
        (> @state @fin)
        (:error nil)
        (:ok @state)
      end.if

      if 
        (== @state @fin)
        (:end @fin)
      end.if


      ;print "i am in next(v): \n"
    end.def
    def end ()
      assign @state @begin
    end.def

  end.class

  def main (x y)

    (assign x1 999)
    assign r1 (new Range 1 5 1)
    ;send r1 :next 

      loop
        print (eval (read)) "\n"
      end.loop


  end.def

end.module
