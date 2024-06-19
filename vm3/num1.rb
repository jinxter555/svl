module mhello1
#print "hello\n"
#print f1(11,22)
print f1(num1(), num1())
#print "\n"
#f1(num1(), num2(), num3())
print f1(1,2+3, num3())
return 
print "-\n"
print  num1()
print "-\n"
print  num2()
return 

def num1() do
  return 10+1
end
def num2() do
  # return 20+1
  return 21
end
def num3() do
  # return 20+1
  return 31
end
def f1(v1, v2, v3) do
  print "in f1\n"
  #r = v1 # + v2
  #r =  v2
  print v2
  print "\n"
end

