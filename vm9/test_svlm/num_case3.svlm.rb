module Main do 
  def main() do
    print "in main\n"
    print "\n"
    #
    a = {1,3}
    case {1,3} do
    is {$x,3} when $x == 1 ->
      print a 
      print "\n"
      print $x
      print "did match x == 1 !\n";
    else ->
      print a
      print "didn't match anything!\n";
    end

    #print "the end\n"

  end

end
