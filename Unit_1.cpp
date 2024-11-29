// Writing program for curve fitting by method of group averages
// version topic.method.bugfix (larger number means all version before it already present)
// version 1.1.0 (fitting of straight line according to given points)
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "mathFunctions.h"

using namespace std;

void groupAverages(float *x, float *y, int n, int type)
{
    if (type == 1)
    {
        float x1{}, y1{}, x2{}, y2{}, a, b;
        for (int i = 0; i < n / 2; i++)
        {
            x1 += x[i];
            y1 += y[i];
        }
        x1 /= (n / 2);
        y1 /= (n / 2);

        for (int i = n / 2; i < n; i++)
        {
            x2 += x[i];
            y2 += y[i];
        }
        x2 /= (n / 2);
        y2 /= (n / 2);
        a = (y2 - y1);
        a /= (x2 - x1);

        b = y2 - x2 * a;
        cout << "The fitted curve is Y = " << a << "X + (" << b << ")" << endl;
    }
    else if (type == 2)
    {
        float X1{}, Y1{}, X2{}, Y2{}, a, b, c;
        float newX[n], newY[n];
        for (int i = 0; i < n; i++)
        {
            if (i != (n / 2))
            {
                newY[i] = (y[i] - y[n / 2]);
                newY[i] /= (x[i] - x[n / 2]);

                newX[i] = x[i] + x[n / 2];
            }
            else
            {
                newX[n / 2] = 0;
                newY[n / 2] = 0;
            }
        }
        for (int i = 0; i < n / 2; i++)
        {
            X1 += newX[i];
            Y1 += newY[i];
        }
        X1 /= (n / 2);
        Y1 /= (n / 2);
        for (int i = n / 2; i < n; i++)
        {
            X2 += newX[i];
            Y2 += newY[i];
        }
        X2 /= (n / 2);
        Y2 /= (n / 2);
        vector<float> ans = linearEqn2Var(X1, 1, Y1, X2, 1, Y2);
        a = ans[0];
        b = ans[1];

        c = y[n / 2] - a * x[n / 2] * x[n / 2] - b * x[n / 2];

        cout << "The fitted curve is Y = " << a << "X^2 + " << b << "X + " << c << endl;
    }
    else if (type == 3)
    {
    }
    else
    {
        cout << "No valid operation choosen";
    }
}

int main()
{
    int n, type;
    cout << "Enter the number of entries. \n";
    cin >> n;
    cout << "Enter the type of curve fitting \n 1 - Straight line \n 2 - Quadratic polynomial \n 3 - Exponential " << endl;
    cin >> type;
    cout << "Enter data for x \n";
    float x[n], y[n];
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }
    cout << "Enter data for y \n";
    for (int i = 0; i < n; i++)
    {
        cin >> y[i];
    }
    groupAverages(x, y, n, type);
}