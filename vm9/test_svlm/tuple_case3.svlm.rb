module mhello
$a = {3, 4};
case $a do
is $b when $b == {3,4} ->
  print $a
  print "world\n"
else ->
  print "else world\n"
end
return
