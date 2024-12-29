# what is up

module Main do
  def main() do
    print "In Main!\n\n"
    $a = [1,2,3]
    $b = $a
    $b[1] = 555
    print "a: "
    print $a
    print "\n"
    print "b: "
    print $b
    print "\n"
   # $b = $a
   # $a[1] = 5555
   # $b[1] = 6666
   # print $a
    print "\n"
   # print $b
    print "\n"
    print "\n"
  end
end
