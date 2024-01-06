# EQ_EDIT - A C++ Equation Evaluator

EQ_EDIT is a simple C++ code that evaluate a mathematical expression with variables and some standard mathematical functions given as a string. The variables and functions used in the equation are defined and their values are passed to the function that evaluates the equation. The code is presented in a single header file `EQ_EDIT.hpp` which contains the `EQ_EDIT` class.

The code allows the following mathematical operators to be used in the equation:
- `+` - Addition
- `-` - Subtraction
- `*` - Multiplication
- `/` - Division
- `^` - Power
- `()` - Parentheses

the following mathematical functions to be used in the equation:
- `abs` - Absolute value
- `int` - Integer part
- `frac` - Fractional part
- `rond` - Round
- `log` - Logarithm (base 10)
- `ln` - Natural logarithm
- `exp` - Exponential
- `sin` - Sine
- `cos` - Cosine
- `tan` - Tangent
- `sh` - Hyperbolic sine
- `ch` - Hyperbolic cosine
- `th` - Hyperbolic tangent
- `asin` - Arcsine
- `acos` - Arccosine
- `atan` - Arctangent
- `ash` - Hyperbolic arcsine
- `ach` - Hyperbolic arccosine
- `ath` - Hyperbolic arctangent

and the following mathematical constants to be used in the equation:
- `pi` - &pi; number
- `e` - Euler's number

It is possible to add new functions and constants to the code by modifying the `EQ_EDIT.hpp` file.

## How it Works
The application uses the `EQ_EDIT` class to evaluate mathematical equations. The variables used in the equation are defined and their values are passed to the `Value` method of the `func_eq` object. This method evaluates the equation and returns the calculated value.
Another way to use the code is to define the variables and the equation using the `setVar` and `setEquation` methods of the `EQ_EDIT` class. The `getValue` method of the `func_eq` object, without any arguments, is then called to evaluate the equation.

## How to Use the Code
To use the code, you need to include the `EQ_EDIT.hpp` header file in your code. You can then create an instance of the `EQ_EDIT` class and use it to evaluate mathematical equations. See the code examples below for more details.

## Code example
### Example 1
A first example is presented in the `example1.cpp` file. 
```cpp
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
```

Here is a description of each line of code:
```cpp
#include "EQ_EDIT.hpp"
```
Includes the `EQ_EDIT.hpp` header file which contains the `EQ_EDIT` class.

```cpp
EQ_EDIT func_eq;
```
Creates an instance of the `EQ_EDIT` class which is used to evaluate mathematical equations.

```cpp
double x = 10;
double beta = 1.5;
string equation = "-(x^2/2)+20+2*beta+alpha";
```
Defines the variables `x`, `beta`, and `alpha` and the equation to evaluate.

```cpp
double value = func_eq.Value(true,equation,{{"x",x},{"beta",beta},{"alpha",0.5}});
```
Calls the `Value` method of the `func_eq` object to evaluate the equation. The values of the variables are passed as key-value pairs.

```cpp
cout << "Equation: " << func_eq.getEquation() << endl;
cout << "Number of variables: " << func_eq.getNVar() << endl;
cout << "Value: " << value << endl;
```
Displays the equation, the number of variables in the equation, and its calculated value.

### Example 2
Another example is presented in the `example2.cpp` file. 
```cpp
#include <iostream>
#include "EQ_EDIT.hpp"
using namespace std;
int main()
{
    EQ_EDIT func_eq;
    double x = 10;
    double beta = 1.5;
    string equation = "-(x^2/2)+20+2*beta+alpha";
    func_eq.setVar({{"x",x},{"beta",beta},{"alpha",0.5}});
    func_eq.setEquation(equation);
    double value    = func_eq.getValue();
    cout<<"----------------------------------"<<endl;
    cout<<"          EXAMPLE 2              "<<endl;
    cout<<"----------------------------------"<<endl;
    cout << "Equation exp.: " << func_eq.getEquation() << endl;
    cout << "Number of variables: " << func_eq.getNVar() << endl;
    cout << "Value: " << value << endl;
    return 0;
}
```
In this example the variables are defined and the equation is set using the `setVar` and `setEquation` methods of the `EQ_EDIT` class. Here is a description the alternative method used in this example:

```cpp
func_eq.setVar({{"x",x},{"beta",beta},{"alpha",0.5}});
func_eq.setEquation(equation);
double value    = func_eq.getValue();
```
Sets the values of the variables and the equation to evaluate. The `getValue` method of the `func_eq` object is then called to evaluate the equation.

```cpp
cout << "Equation: " << func_eq.getEquation() << endl;
cout << "Number of variables: " << func_eq.getNVar() << endl;
cout << "Value: " << value << endl;
```
Displays the equation, the number of variables in the equation, and its calculated value.


## License

This project is licensed under the GPL-3 license.

Unless you explicitly state otherwise, any contribution intentionally submitted by you for inclusion in this project shall be licensed as above, without any additional terms or conditions.