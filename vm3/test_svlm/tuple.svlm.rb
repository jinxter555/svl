module mhello
$a = {1,2}
$b = {3,4}
$c = {$a, $b}
print $c
#if {$x, $y} = $c then
if $a == $b then
  print "hello"
else
  print "world"
end
return
print "\n"
print $b
print "\n"
print $c
return 

