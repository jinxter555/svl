#include <any>
#include <iostream>

using namespace std;
 
int main()
{
    cout << boolalpha;
    cout << "\n";

    any a = 1;
    cout << a.type().name() << ": " << any_cast<int>(a) << "\n";
    a = 3.14;
    cout << a.type().name() << ": " << any_cast<double>(a) << "\n";
    a = true;
    cout << a.type().name() << ": " << any_cast<bool>(a) << "\n";
    cout << "\n";

    try {
      a = 1;
      cout << std::any_cast<float>(a) << '\n';
    } catch(const bad_any_cast &e) {
      cout << e.what() << "\n";
    }
    a =2 ;
    if(a.has_value()) {
      cout << a.type().name() << ": " << any_cast<int>(a) << "\n";
    }

    a.reset();
    if (!a.has_value()) {
        std::cout << "no value\n";
    }

    a = 3;
    int *i = any_cast<int>(&a);
    cout << *i << "\n";
    cout << "\n";

}
