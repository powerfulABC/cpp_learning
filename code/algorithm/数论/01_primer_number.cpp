#include <cmath>

// 暴力求解
bool isPrimerNumber(int N)
{
    if (N <= 1)
        return false;
    if (N == 2) 
        return true;
    
    int max_x = std::sqrt(N) + 1;
    for (int x = 2; x <= max_x; ++x)
    {
        if (N % x == 0)
        {
            return false;
        }
    }
    return true;
}