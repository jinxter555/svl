# what is up

module Main do
  def main() do
    # $m = %{"hello": "world"}
    $m1 = %{ "www1": "server1", "www2": [1,2,3]}
    $m2 = %{ "www1": "server1", "www2": "server2" }
    print $m1["what"]

    $l = [1,2,3]
    print $l
    print $m1
    print "\n"
  end
end
