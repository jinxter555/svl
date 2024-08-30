module mhello
$abc = 22
print $abc
print "\n"

while $abc >= 5 do
  print "hello: "
  print $abc
  print "\n"
  $abc = $abc - 1

  case $abc do
  is 10 ->
    print "I have 10 break out\n"
    break
  is 30 ->
    print "I have 30 break out\n"
    break
  end

end
return
