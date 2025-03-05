module Main  do

def main() do
    #print "in main\n"
    print "in main"
    func2()
    func3(456)
end

def func2() do
    print "in func2\n"
    $var1 = 123
    print "var1: "
    print $var1
    #print "\n\n"
    func3(888)
end

def func3(f_arg1) do
    print "in func3, f_arg1:"
    print f_arg1
    print "\n\n"
end

module Helper.App.Main do
  def me() do
    print "helper me\n"
  end
end

end

