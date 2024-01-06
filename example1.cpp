#include <iostream>
#include "EQ_EDIT.hpp"

using namespace std;

int main()
{

    EQ_EDIT func_eq;

    double x = 10;
    double beta = 1.5;
    string equation = "-(x^2/2)+20+2*beta+alpha";
    double value    = func_eq.getValue(true,equation,{{"x",x},{"beta",beta},{"alpha",0.5}});
    cout<<"----------------------------------"<<endl;
    cout<<"          EXAMPLE 1              "<<endl;
    cout<<"----------------------------------"<<endl;
    cout << "Equation exp.: " << func_eq.getEquation() << endl;
    cout << "Number of variables: " << func_eq.getNVar() << endl;
    cout << "Value: " << value << endl;

    return 0;
}
