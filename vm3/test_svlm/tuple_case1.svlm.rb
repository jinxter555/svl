module mhello
$a = {2, 4};
case $a do
is true -> 
  print "hello\n"
is $b when $b > 123 ->
  print $a
  print "world\n"
is {$x, 4} -> 
  print $x
  print "\n"
  print "got it 3\n"
else ->
  print "else world\n"
end
return
