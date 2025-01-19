module mhello
$a = 5
print $a
print "\n";
if {$a, 2} == {5, 1+1 }  then
  print "tuple equal \n"
else
  print "wrong\n"
end
break
