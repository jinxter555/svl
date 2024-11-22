#include <iostream>
#include <utility> // for std::as_const
                   //
using namespace std;

class IntList
{
private:
    int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // give this class some initial state for this example

public:
    int& operator[] (int index)
    {
        // use std::as_const to get a const version of `this` (as a reference)
        // so we can call the const version of operator[]
        // then const_cast to discard the const on the returned reference
        return const_cast<int&>(as_const(*this)[index]);
    }

    const int& operator[] (int index) const
    {
        return m_list[index];
    }
};

int main()
{
    IntList list{};
    list[2] = 3; // okay: calls non-const version of operator[]
    std::cout << list[2] << '\n';

    const IntList clist{};
    // clist[2] = 3; // compile error: clist[2] returns const refrence, which we can't assign to
    std::cout << clist[2] << '\n';

    return 0;
}
