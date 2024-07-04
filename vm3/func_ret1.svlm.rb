module mhello
$a = 5
$b = $a +  num1()
print $b
$c = $a +  f1(1,2)
print $c
print  "hello"
print "\n";
break
def num1() do
  return 10+20
end
def f1(n1, n2) do
  return n1 + n2
end
