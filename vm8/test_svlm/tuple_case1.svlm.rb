module mhello
$a = {5, 1055};
case $a do
is {1, 4}  -> 
  print $a
  print "exact!\n"
is {$x, $y} when $x >= 3 -> 
  print $x
  print $y
  print "\n"
  print "got it 4\n"
else ->
  print "else world\n"
end
return
