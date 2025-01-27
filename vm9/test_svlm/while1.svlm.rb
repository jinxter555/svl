module Main do
  def main() do
    $a = 10

    print "a is: "
    print $a
    print "\n";

    while $a > 0 do
      print $a
      print "\n";
      $a = $a - 1
    end
    #
    print $a
  end
end
