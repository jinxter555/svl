module Main do 
  def main() do
    print "in main\n"
    print "\n"
    #
    case 0 do
    is 123 ->
      print "i am 123\n";
      $a = 1+2 
      print $a
      print "\n"
    
    is 222 -> 
      print "hello b: "
      $b = 2+25
      print $b
    # is x when x == 125 ->
    is x when x > 1 ->
      print "did match x > 1 !\n";
    else ->
      print "didn't match anything!\n";
    end

    print "the end\n"

  end

end
