# what is up

module Main do
  def main() do
    print "in main\n"
    func2()
    func3(456)

    Helper.me(999)
    # Helper.me()
  end

  def func2() do
    print "in func2\n"
    $var1 = 123
    print "var1: "
    print $var1
    print "\n\n"
    func3(888)
  end

  def func3(arg1) do
    print "in func3, arg1:"
    print arg1
    print "\n\n"
  end

end

module Helper do
  def me(arg1) do
    print "helper::me "
    print arg1
    print "\n\n"
  end
end
