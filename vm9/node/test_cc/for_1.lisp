module Kernel 
  class Range
    (var begin fin step state)

    def Range(start fin step)  
      ; assign needs to return a value
      = @begin start
      = @state start
      = @fin fin
      = @step  step

    end.def

    def init()  
      = @state @begin
      (:ok @state)
    end.def

    ; return statement needed
    def next ()
      = @state (+ @state @step)
      ; print "next: " @state "\n"

      if (>= @state @fin)
        return (:end @fin)
      end.if

      if(> @state @fin)
        return (:error nil)
        return (:ok @state)
      end.if

      ;print "i am in next(v): \n"
    end.def

    def end ()
      assign @state @begin
    end.def

  end.class

  defmacro forloop ( it cblock )
    quote
      var rv u (forever~ true)
      = rv (send (unquote it)  :init)
  
      ;faz (rv) (unquote cblock)
      while(forever~)
        ;= rv (send (unquote it)  :next)
        

        if (= (:end _) rv)
         ( print "end\n"
          = forever~ false
         )
        end.if

        if (= (:error _) rv)
        (
          print "error\n"
          = forever~ false
        )
        end.if


        faz (rv) (unquote cblock)
        = rv (send (unquote it)  :next)
        ;faz (rv2) (unquote cblock)
        ; faz (rv) (unquote cblock)

      

      end.while
      
      

    end.quote
    return :ok


  end.defmacro

  def main (x y)
    var i forever
    = r1 (new Range 1 5 3)

    ;send r1 :next 

    (forloop r1 
      do (:ok i)
        print i ": what is up\n"
      end.do
    )

   (loop (print (eval (read)) "\n"))
  

  end.def

end.module
