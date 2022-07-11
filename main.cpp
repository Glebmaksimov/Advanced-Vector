#include "Declarations.h"
using namespace std;

struct D {
    int a = 4;
    int b = 6;
};
int main(){

    Vector<D> v;
    D a;
    D b;
    D c;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    for (int i = 0; i < v.size(); ++i) {
        cout<<v[i].a<<"\t"<<v[i].b<<endl;
    }
    return 0;
}
