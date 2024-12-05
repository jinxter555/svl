# what is up

module Main do
  def main() do
    print "In Main!\n\n"
    $a = [1,2,3]
    $b = $a
    $a[1] = 5555
    $b[1] = 6666
    # $m = %{"hello": "world"}
    $m = %{}
    print $a[1]
    print "\n"
    print $m
    print "\n"
  end
end
