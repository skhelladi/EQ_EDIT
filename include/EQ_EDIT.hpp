/* 
    * Project: EQ_EDIT
    * File:   EQ_EDIT.hpp
    * license: GNU/GPLv3
    * Author:  Sofiane KHELLADI <sofiane.khelladi@gmail.com>
    * This code allows to evaluate a mathematical expression with variables and functions.
 */

#ifndef EQ_EDIT_H
#define EQ_EDIT_H

#include <math.h>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <cstdarg>
#include <cstring>
#include <vector>
//////////////////////////
//////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//                              CONSTANTES                                    //
////////////////////////////////////////////////////////////////////////////////
#define CONSMAX 2
#define FUNMAX 19
#define F_STACKMAX 100
#define ERRORMAX 7

////////////////////////////////////////////////////////////////////////////////
//                                  ERRORS                                    //
////////////////////////////////////////////////////////////////////////////////

string errtb[ERRORMAX] =
    {
        "No function...",
        "Not an alpha-numeric character...",
        "Unknown function...",
        "Not defined variable: choose one among 'x,y,z,a,b,c,d,f,g,h'...",
        "Probably you've used a bad operator...",
        "Bad function expression...",
        "Number of variable unsupported..."};
////////////////////////////////////////////////////////////////////////////////
//                               FUNCTIONS                                    //
////////////////////////////////////////////////////////////////////////////////

string functb[FUNMAX] =
    {
        "abs",
        "int",
        "frac",
        "rond",
        "log",
        "ln",
        "exp",
        "sin",
        "cos",
        "tan",
        "sh",
        "ch",
        "th",
        "asin",
        "acos",
        "atan",
        "ash",
        "ach",
        "ath",
};

////////////////////////////////////////////////////////////////////////////////
//                              CONSTANTES ARRYS                              //
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    string name;
    double val;
} constyp;

constyp constb[CONSMAX] = {{"pi", M_PI}, {"e", M_E}};

////////////////////////////////////////////////////////////////////////////////
//                                 VARIABLES                                  //
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    string name;
    double val;
} vartyp;

////////////////////////////////////////////////////////////////////////////////
//                                  ERRORS                                    //
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    NO_FUNCTION,
    NOT_ALPANUM,
    UNKNOWN_FUNC,
    NOT_DEFINED_VAR,
    BAD_OPERATOR,
    BAD_FUNC,
    UNSUPPORTED_VAR_NUM
} error_id;

////////////////////////////////////////////////////////////////////////////////
//                               FUNCTIONS                                    //
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    F_ABS,
    F_INT,
    F_FRAC,
    F_ROND,
    F_LOG,
    F_LN,
    F_EXP,
    F_SIN,
    F_COS,
    F_TAN,
    F_SH,
    F_CH,
    F_TH,
    F_ASIN,
    F_ACOS,
    F_ATN,
    F_ASH,
    F_ACH,
    F_ATH
} funcname;

double F_FUNC(int k, double x)
{
    switch (k)
    {
    case F_ABS:
        return fabs(x);
    case F_INT:
        return floor(x);
    case F_FRAC:
        return x - floor(x);
    case F_ROND:
        return (x < 0.5 * (ceil(x) + floor(x))) ? floor(x) : ceil(x);
    case F_LOG:
        return log10(x);
    case F_LN:
        return log(x);
    case F_EXP:
        return exp(x);
    case F_SIN:
        return sin(x);
    case F_COS:
        return cos(x);
    case F_TAN:
        return tan(x);
    case F_SH:
        return sinh(x);
    case F_CH:
        return cosh(x);
    case F_TH:
        return tanh(x);
    case F_ASIN:
        return asin(x);
    case F_ACOS:
        return acos(x);
    case F_ATN:
        return atan(x);
    case F_ASH:
        return (x < 0.0) ? -log(sqrt(x * x + 1.0) - x) : log(x + sqrt(x * x + 1.0));
    case F_ACH:
        return log(x + sqrt(x * x - 1.0));
    case F_ATH:
        return 0.5 * log((1 + x) / (1 - x));
    }
    return 0.0;
}

////////////////////////////////////////////////////////////////////////////////
//                                   WEIGHT                                   //
////////////////////////////////////////////////////////////////////////////////
char weight(char op)
{
    return (
        (op == ')') ? 1 : (op == '+' || op == '-')            ? 2
                      : (op == '*' || op == '/' || op == 'm') ? 3
                      : (op == '^')                           ? 4
                      : (op == '(' || op == 'f')              ? 1
                                                              : 0);
}
//---------------------------------------------------------------------------

class EQ_EDIT
{
public:
    EQ_EDIT() {}
    virtual ~EQ_EDIT() {}
    void setNVar(int value)
    {
        NVar = value;
    }
    int getNVar()
    {
        return NVar;
    }
    
    void setVar(vector<vartyp> value)
    {
        NVar = value.size();
        vartb = value;
    }

    vector<vartyp> getVar()
    {
        return vartb;
    }

    void setEquation(string value)
    {
        Equation = value;
    }
    string getEquation()
    {
        return Equation;
    }
    // double  Value(bool go,vector<double> value);   //y=f(x)
    double getValue(bool compute, string equation, vector<vartyp> var = {{"x", 0.0}})
    {
        if (compute)
        {
            if (equation == "")
            {
                cerr << errtb[NO_FUNCTION];
                return -1;
            }

            NVar = var.size();

            vartb = var;
            Equation = equation;

            return F_VALUE(Equation.c_str(), true);
        }
        else
            return 0.0;
    }

    double getValue()
    {
        if (Equation == "")
        {
            cerr << errtb[NO_FUNCTION];
            return -1;
        }

        return F_VALUE(Equation.c_str(), true);
    }

private:
    double F_VALUE(string expr, bool cal)
    {
        double stack_x[F_STACKMAX];
        char stack_o[F_STACKMAX];
        int stack_f[F_STACKMAX];
        int kx = -1,
            ko = 0,
            kf = -1;
        int state = 0,
            end_pos = 0;
        char *ci = NULL;
        char cop;
        int sop,
            k;
        char *cx = (char *)"";

        int VARMAX = NVar;

        if (expr == "")
        {
            cerr << errtb[NO_FUNCTION];
            return -1;
        }

        cx = (char *)expr.c_str();

        for (int i = 0; i < F_STACKMAX; i++)
        {
            stack_x[i] = 0;
        }

        stack_o[0] = '(';
        while (end_pos < 2)
        {
            switch (state)
            {
            case 0:

            case 1:
                if (*cx == '(')
                {
                    stack_o[++ko] = '(';
                    cx++;
                    state = 0;
                    break;
                }

                if (*cx == '-' && state == 0)
                {
                    stack_o[++ko] = 'm';
                    cx++;
                    state = 1;
                    break;
                }

                if (!isalnum(*cx))
                {
                    cerr << errtb[NOT_ALPANUM];
                    return -1;
                }

                if (isdigit(*cx))
                {
                    stack_x[++kx] = strtod(cx, &ci);
                    cx = ci;
                    state = 2;
                    break;
                }

                k = 0;

                while (isalnum(cx[k]))
                    k++;
                ci = (char *)calloc(k + 1, sizeof(char *));
                strncpy(ci, cx, k);
                cx += k;
                if (*cx == '(')
                {
                    for (k = 0; k < FUNMAX; k++)
                        if (strcmp(ci, functb[k].c_str()) == 0)
                            break;
                    free(ci);
                    ci = NULL;
                    if (FUNMAX <= k)
                    {
                        cerr << errtb[UNKNOWN_FUNC];
                        return -1;
                    }

                    stack_f[++kf] = k;
                    stack_o[++ko] = 'f';
                    cx++;
                    state = 0;
                    break;
                }
                for (k = 0; k < CONSMAX; k++)
                    if (strcmp(ci, constb[k].name.c_str()) == 0)
                        break;
                if (CONSMAX <= k)
                {
                    for (k = 0; k < VARMAX; k++)
                        if (strcmp(ci, vartb[k].name.c_str()) == 0)
                            break;

                    if (VARMAX <= k)
                    {
                        // free(ci);
                        cerr << errtb[NOT_DEFINED_VAR];
                        return -1;
                    }
                    stack_x[++kx] = vartb[k].val;
                }
                else
                    stack_x[++kx] = constb[k].val;
                state = 2;
                free(ci);
                break;
            case 2:
                cop = (*cx == 0) ? ')' : *cx++;
                sop = weight(cop);
                if (sop == 0)
                {
                    // free(ci);
                    cerr << errtb[BAD_OPERATOR];
                    return -1;
                }

                state = 1;
                while (state < 2 && sop <= weight(stack_o[ko]))
                {
                    switch (stack_o[ko])
                    {
                    case '+':
                        stack_x[kx - 1] = cal ? stack_x[kx - 1] + stack_x[kx] : 0.0;
                        kx--;
                        break;
                    case '-':
                        stack_x[kx - 1] = cal ? stack_x[kx - 1] - stack_x[kx] : 0.0;
                        kx--;
                        break;
                    case '*':
                        stack_x[kx - 1] = cal ? stack_x[kx - 1] * stack_x[kx] : 0.0;
                        kx--;
                        break;
                    case '/':
                        stack_x[kx - 1] = cal ? stack_x[kx - 1] / stack_x[kx] : 0.0;
                        kx--;
                        break;
                    case '^':
                        stack_x[kx - 1] = cal ? pow(stack_x[kx - 1], stack_x[kx]) : 0.0;
                        kx--;
                        break;
                    case 'm':
                        stack_x[kx] = cal ? -stack_x[kx] : 0.0;
                        break;
                    case 'f':
                        stack_x[kx] = cal ? F_FUNC(stack_f[kf], stack_x[kx]) : 0.0;
                        kf--;
                    case '(':
                        state = 2;
                    }
                    stack_o[ko--] = ' ';
                }
                if (cop != ')')
                    stack_o[++ko] = cop;
                else if (*cx == 0)
                    end_pos++;
            }
        }

        if (ko != -1 || kx != 0 || kf != -1)
        {
            cerr << errtb[BAD_FUNC];
            return -1;
        }

        return stack_x[0];
    }

    string Equation;
    int NVar;
    vector<vartyp> vartb;
};

#endif // EQ_EDIT_H
