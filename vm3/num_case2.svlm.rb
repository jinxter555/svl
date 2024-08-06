module mhello
$a = 123;
print $a
case $a do
is true -> 
  print "hello\n"
is $b when $b == 123 ->
  print "world\n"
end
return
