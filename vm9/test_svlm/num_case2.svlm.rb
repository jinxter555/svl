module Main do 
  def main() do
    print "in main\n"
    print "\n"
    #
    a = {1,3}
    case a do
    is 123 ->
      print "i am 123\n";
      $a = 1+2 
      print $a
      print "\n"
    
    is 222 -> 
      print "hello b: "
      $b = 2+25
      print $b
    is {1,4}  ->
      print "match {1,3}\n"
      print a 
    is {$x,3} when $x == 1 ->
      print a 
      print "did match x == 1 !\n";
    else ->
      print a
      print "didn't match anything!\n";
    end

    #print "the end\n"

  end

end
