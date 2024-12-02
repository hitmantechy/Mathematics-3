// Writing program for curve fitting by method of group averages
// version topic.method.bugfix (larger number means all version before it already present)
// version 1.3.0 (fitting of straight line according to given points)
// There are certain problems in fitting of curve using quadratic using method of group averages
// Different methods gives slightly different results so consider checking the answers
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
    else if (type == 4)
    {
        float a, b, X1{}, X2{}, Y1{}, Y2{};
        float newX[n], newY[n];
        for (int i = 0; i < n; i++)
        {
            newX[i] = log10(x[i]);
            newY[i] = log10(y[i]);
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

        vector<float> ans = linearEqn2Var(1, X1, Y1, 1, X2, Y2);

        cout << "The fitted curve is Y = " << pow(10, ans[0]) << "X^" << ans[1];
    }
    else if (type == 3)
    {
        float a, b, X1{}, X2{}, Y1{}, Y2{};
        float newY[n];
        for (int i = 0; i < n; i++)
        {
            newY[i] = log10(y[i]);
        }
        for (int i = 0; i < n / 2; i++)
        {
            X1 += x[i];
            Y1 += newY[i];
        }
        X1 /= (n / 2);
        Y1 /= (n / 2);
        for (int i = n / 2; i < n; i++)
        {
            X2 += x[i];
            Y2 += newY[i];
        }
        X2 /= (n / 2);
        Y2 /= (n / 2);

        vector<float> ans = linearEqn2Var(1, X1, Y1, 1, X2, Y2);

        cout << "The fitted curve is Y = (" << pow(10, ans[0]) << ")(" << pow(10, ans[1]) << ")^X";
    }
    else
    {
        cout << "No valid operation choosen";
    }
}

void leastSquare(float *x, float *y, int n, int type)
{
    if (type == 1)
    {
        float X{}, Y{}, sqX{}, XY{};
        for (int i = 0; i < n; i++)
        {
            X += x[i];
            Y += y[i];
            sqX += x[i] * x[i];
            XY += x[i] * y[i];
        }
        vector<float> ans = linearEqn2Var(X, n, Y, sqX, X, XY);
        cout << "The fitted curve is Y = " << ans[0] << "X + (" << ans[1] << ")";
    }
    else if (type == 2)
    {
        float X{}, Y{}, sqX{}, XY{}, cbX{}, sqX_Y{}, qdX{};
        for (int i = 0; i < n; i++)
        {
            X += x[i];
            Y += y[i];
            sqX += x[i] * x[i];
            XY += x[i] * y[i];
            cbX += x[i] * x[i] * x[i];
            sqX_Y += x[i] * x[i] * y[i];
            qdX += x[i] * x[i] * x[i] * x[i];
        }
        vector<float> ans = linearEqn3Var(sqX, X, n, Y, cbX, sqX, X, XY, qdX, cbX, sqX, sqX_Y);
        cout << "The fitted curve is Y = " << ans[0] << "X^2 + (" << ans[1] << ")X + (" << ans[2] << ")";
    }
    else
    {
        cout << "No valid operation choosen";
    }
}

void methodOfMoments(float *x, float *y, int n, int type)
{
    if (type == 1)
    {
        float a, b, h{x[1] - x[0]}, Y{}, XY{};
        a = x[0] - (h / 2);
        b = x[n - 1] + (h / 2);
        for (int i = 0; i < n; i++)
        {
            Y += y[i];
            XY += x[i] * y[i];
        }

        vector<float> ans = linearEqn2Var((b * b - a * a) / 2, (b - a), h * Y, (b * b * b - a * a * a) / 3, (b * b - a * a) / 2, h * XY);

        cout << "Y = " << ans[0] << " + (" << ans[1] << ")";
    }
    else if (type == 2)
    {
        float a, b, h{x[1] - x[0]}, Y{}, XY{}, sqX_Y{};
        a = x[0] - (h / 2);
        b = x[n - 1] + (h / 2);
        for (int i = 0; i < n; i++)
        {
            Y += y[i];
            XY += x[i] * y[i];
            sqX_Y += x[i] * x[i] * y[i];
        }

        vector<float> ans = linearEqn3Var((b * b * b - a * a * a) / 3, (b * b - a * a) / 2, (b - a), h * Y, (pow(b, 4) - pow(a, 4)) / 4, (b * b * b - a * a * a) / 3, (b * b - a * a) / 2, h * XY, (pow(b, 5) - pow(a, 5)) / 5, (pow(b, 4) - pow(a, 4)) / 4, (pow(b, 3) - pow(a, 3)) / 3, h * sqX_Y);

        cout << "The fitted curve is Y = " << ans[0] << "X^2 + (" << ans[1] << ")X + (" << ans[2] << ")";
    }
    else
    {
        cout << "No valid operation choosen";
    }
}

int main()
{
    int n, type, methodType;
    cout << "Enter the number of entries. \n";
    cin >> n;
    cout << "\nEnter the type of curve fitting \n 1 - Straight line \n 2 - Quadratic polynomial \n 3 - Exponential \n 4 - Polynomial" << endl;
    cin >> type;
    cout << "\nEnter the method by you want to use \n 1 - groupAverages \n 2 - leastSquare \n 3 - methodOfMoments \n";
    cin >> methodType;
    cout << "\nEnter data for x \n";
    float x[n], y[n];
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }
    cout << "\nEnter data for y \n";
    for (int i = 0; i < n; i++)
    {
        cin >> y[i];
    }
    if (methodType == 1)
    {
        groupAverages(x, y, n, type);
    }
    else if (methodType == 2)
    {
        leastSquare(x, y, n, type);
    }
    else if (methodType == 3)
    {
        methodOfMoments(x, y, n, type);
    }
    else
    {
        cout << "No valid method is selected ";
    }
}