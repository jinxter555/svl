module mhello
$a = {3, 4};
case $a do
is true -> 
  print "hello\n"
is $b when $b > 123 ->
  print $a
  print "world\n"
is {2, 4}  -> 
  print $a
  print "exact!\n"
is {$x, 4} when $x >= 3 -> 
  print $x
  print "\n"
  print "got it 4\n"
else ->
  print "else world\n"
end
return
