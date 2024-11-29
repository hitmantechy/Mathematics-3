#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<float> linearEqn2Var(float a1, float b1, float c1, float a2, float b2, float c2)
{
    vector<float> solution;
    if ((a1 / a2) != (b1 / b2))
    {

        float D = a1 * b2 - a2 * b1;
        float Dx = c1 * b2 - b1 * c2;
        float Dy = a1 * c2 - a2 * c1;

        solution.push_back(Dx / D);
        solution.push_back(Dy / D);

        return solution;
    }
    else if ((a1 / a2) == (b1 / b2) && (b1 / b2) != (c1 / c2))
    {
        solution.push_back(0);
        return solution;
    }
    else if ((a1 / a2) == (b1 / b2) && (b1 / b2) == (c1 / c2))
    {
        solution.push_back(1);
        return solution;
    }
}

vector<float> linearEqn3Var(float a1, float b1, float c1, float d1, float a2, float b2, float c2, float d2, float a3, float b3, float c3, float d3)
{
    vector<float> solution;
    float D = a1 * (b2 * c3 - b3 * c2) - b1 * (a2 * c3 - a3 * c2) + c1 * (a2 * b3 - a3 * b2);
    float Dx = d1 * (b2 * c3 - b3 * c2) - b1 * (d2 * c3 - d3 * c2) + c1 * (d2 * b3 - d3 * b2);
    float Dy = a1 * (d2 * c3 - d3 * c2) - d1 * (a2 * c3 - a3 * c2) + c1 * (a2 * d3 - a3 * d2);
    float Dz = a1 * (b2 * d3 - b3 * d2) - b1 * (a2 * d3 - a3 * d2) + d1 * (a2 * b3 - a3 * b2);
    solution.push_back(Dx / D);
    solution.push_back(Dy / D);
    solution.push_back(Dz / D);

    return solution;
}
