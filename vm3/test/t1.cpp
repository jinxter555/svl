#include <iostream>
// uncomment to disable assert()
//#define NDEBUG
#include <cassert>
using namespace std;
int main()
{
    int age=15;
    assert(2+2==3+1);
    cout << "Expression valid...Execution continues.\n";
    //assert(2+2==1+1);
    //cout << "Asset disabled...execution continuous with invalid expression\n";


    assert((age >= 18) && "You must be 18 or older to vote");

}
