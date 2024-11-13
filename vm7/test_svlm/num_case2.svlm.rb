module mhello
$a = 123;
case $a do
is true -> 
  print "hello\n"
is $b when $b > 123 ->
  print $a
  print "world\n"
else ->
  print "else world\n"
end
return
