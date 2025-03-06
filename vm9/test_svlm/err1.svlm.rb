# what is up

module Main do
  def main() do
    a = 1 + 1
    print "hello2\n"
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

end

module Helper do
  def me(me_arg1) do
    return me_arg1
    print "in helper::me() "
    print me_arg1
    print "\n\n"
  end
end


module Helper2 do
  def out() do
    print "out\n"
  end
end
