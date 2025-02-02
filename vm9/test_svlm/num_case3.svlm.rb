module Main do 
  def main() do
    print "in main\n"
    print "\n"
    #
    a = {1,{3,4}}

    case a  do
    is {$x,{3,4}} when $x == 1 ->
      print a 
      print "did match x == 1 !\n";
    else ->
      print a
      print "didn't match anything!\n";
    end

    #print "the end\n"

  end

end
