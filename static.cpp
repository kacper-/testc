#include <iostream>
using namespace std;
 
class GfG {
public:
    static int i;
 
    GfG(){
        // Do nothing
    };
};
 
    int GfG::i = 1;

 
int main()
{
    GfG obj;
    // prints value of i
    obj.i=2;
    cout << obj.i;
}