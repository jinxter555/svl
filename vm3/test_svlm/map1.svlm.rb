module mhello
#$a = %{hello: 2}
$a = %{"hello": 2}
$b = %{"world": 2333.33}
print $a["what"]
return
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

