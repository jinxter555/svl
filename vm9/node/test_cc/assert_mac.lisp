module Kernel 
  def main (x y) 
      (var a)
      print "Macros!\n"
      assert [1==1]
      loop
        print (eval (read)) "\n"
      end.loop
  end.def

  defmacro assert (assertion)
    quote
      if (unquote assertion) 
      :else
        print "assert failed!"
      end.if
    end.quote

  end.defmacro

end.module
