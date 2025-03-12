# what is up

module Main do
  class MyClass do
    def init() do
      print "MyClass init()\n"
      @a=1+2*3
      @a=@a+1
      print @a
      print "hello\n"
    end

    def run(arg1) do
      print "run()!!!\n"
      print "arg1: "
      print arg1

      print "\n@a: " 
      @a = @a + arg1
      print @a

      print "\n\n"
    end
  end

  def MyBabe() do 
    print "my babe!\n"
  end

  def main() do
    #Helper.me(999)
    obj = new MyClass
    obj.run(123)
    obj.init()
    #
    #obj.init()
    print "in main()\n"
    func2()
    func3(456)

    #Helper.me(999)
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
    #print me_arg1
    print "\n\n"
  end
end



module Main do
  def out() do
    print "out\n"
  end
end
