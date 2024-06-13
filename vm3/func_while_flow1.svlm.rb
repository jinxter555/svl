module mhello
$a = 5
print "a is: "
print $a
print "\n";

def pf() do
  while $a >= 1 do
    print $a
    print "\n";
    flow $a do
    == 3 -> 
      print "I got 3\n"
      break
    == 4 -> 
      print "I got 4\n"
      break
    end
    $a = $a - 1
  end
  print "end of while\n"
  555
end
