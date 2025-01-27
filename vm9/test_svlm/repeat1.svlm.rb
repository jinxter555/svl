module Main do
  def main() do
    $a = 2

    print "a is: "
    print $a
    print "\n";

    repeat 
      print $a
      print "\n";
      $a = $a + 1
    until $a > 10 done
    #
    print $a
  end
end
