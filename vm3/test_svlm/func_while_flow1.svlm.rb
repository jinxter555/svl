module mhello
$a = 10
print "a is: "
print $a
print "\n";
pf()
break

def pf() do
  while $a >= 1 do
    # print $a
    print "\n";
    case $a do
    is 3 -> 
      print "I got 3\n"
      break
    is 4 -> 
      print "I got 4\n"
    else ->
      print "d == I got "
      print $a
      print " \n"
    end
    $a = $a - 1
  end
  print "end of while\n"
  555
end