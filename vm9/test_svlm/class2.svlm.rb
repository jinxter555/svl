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

  def main() do
    print "\n\nin main()\n"
    obj = new MyClass
    obj.init()
    print "obj: " 
    print obj
    print "\n"
    obj.run(123)
    print "obj: " 
    print obj
    print "\n"

  end



end

