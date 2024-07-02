module mhello
$abc = 2
print $abc
print "\n"
#
#
# if (3==0) || (4==2) then
if $abc > 10 then
  print "gt 10 \n"
else 
  print "n gt 10\n"
end

$n = 222;

flow $n do
is 123 ->
  $a = 777
  print $a
  print "\n"
is 223 -> 
  print "hello b: "
  $b = 2+25
  print $b
is 1 ->
  2 + 3
else ->
  $c = 555
  print $c
end


return

