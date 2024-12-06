// Numerical Solution of Algebraic and Transcedental equations
// Solution method involves two methods approximating using single value , approximation using intervals
// functions input should contain two values a,b , tolerance , maxIteration
//  version 0.1.0
#include <iostream>
#include <cmath>
#include <vector>
#include "mathFunctions.h"
#include <string>
#include <iomanip>

// currently working on taking f(x) as a input string
/*
float function(float x){
     string function;
     cout<<"Enter function \n";
     getline(cin, function);
    int i=0;
     while(i<function.size()-1){

        i++;
     }
}
*/

float f(float x)
{
    return 3 * x * x * x + 12 * x * x - 5 * x + 7;
}

float df(float x)
{
    return 9 * x * x + 24 * x - 5;
}

float bisectionMethod(float a, float b)
{
    float ans = (a + b) / 2;
    for (int i = 0; i < 20; i++)
    {
        if (f(ans) < 0)
        {
            a = ans;
        }
        else if (f(ans) > 0)
        {
            b = ans;
        }
        ans = (a + b) / 2;
    }
    return ans;
}

float regulaFalsiMethod(float a, float b)
{
    float ans = a * f(b) - b * f(a);
    ans /= (f(b) - f(a));

    for (int i = 0; i < 12; i++)
    {
        if (f(ans) < 0)
        {
            a = ans;
        }
        else if (f(ans) > 0)
        {
            b = ans;
        }
        ans = a * f(b) - b * f(a);
        ans /= (f(b) - f(a));
    }
    return ans;
}

float secantMethod(float a, float b)
{
    float ans = a * f(b) - b * f(a);
    ans /= (f(b) - f(a));
    for (int i = 0; i < 5; i++)
    {
        a = b;
        b = ans;
        ans = a * f(b) - b * f(a);
        ans /= (f(b) - f(a));
    }
    return ans;
}

float newtonRaphsonMethod(float a)
{
    float x = a - f(a) / df(a);
    for (int i = 0; i < 5; i++)
    {
        a = x;
        x = a - f(a) / df(a);
    }
    return x;
}

vector<float> gaussJacobi(float a1, float b1, float c1, float d1, float a2, float b2, float c2, float d2, float a3, float b3, float c3, float d3)
{
    vector<float> ans(3);
    float x{}, y{}, z{};
    for (int i = 0; i < 12; i++)
    {
        ans[0] = (d1 - b1 * y - c1 * z) / a1;
        ans[1] = (d2 - a2 * x - c2 * z) / b2;
        ans[2] = (d3 - a3 * x - b3 * y) / c3;
        x = ans[0];
        y = ans[1];
        z = ans[2];
    }
    return ans;
}

vector<float> gaussSeidal(float a1, float b1, float c1, float d1, float a2, float b2, float c2, float d2, float a3, float b3, float c3, float d3)
{
    vector<float> ans(3, 0);
    for (int i = 0; i < 10; i++)
    {
        ans[0] = (d1 - b1 * ans[1] - c1 * ans[2]) / a1;
        ans[1] = (d2 - a2 * ans[0] - c2 * ans[2]) / b2;
        ans[2] = (d3 - a3 * ans[0] - b3 * ans[1]) / c3;
    }
    return ans;
}

using namespace std;

int main()
{
    int a{-5}, b{-4};
    cout << setprecision(15) << bisectionMethod(a, b) << endl;
    cout << setprecision(15) << regulaFalsiMethod(a, b) << endl;
    cout << setprecision(15) << secantMethod(a, b) << endl;
    cout << setprecision(15) << newtonRaphsonMethod(a) << endl;

    float a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3;
    cout << "Enter the coefficients of a1X + b1Y + c1Z = d1 " << endl;
    cin >> a1 >> b1 >> c1 >> d1;
    cout << "Enter the coefficients of a2X + b2Y + c2Z = d2 " << endl;
    cin >> a2 >> b2 >> c2 >> d2;
    cout << "Enter the coefficients of a3X + b3Y + c3Z = d3 " << endl;
    cin >> a3 >> b3 >> c3 >> d3;

    vector<float> ans = gaussJacobi(a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3);
    // vector<float> ans1 = gaussSeidal(a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3);
    cout << "Solutions is ( " << ans[0] << " , " << ans[1] << " , " << ans[2] << " )" << endl;
    // cout << "Solutions is ( " << ans1[0] << " , " << ans1[1] << " , " << ans1[2] << " )" << endl;
}