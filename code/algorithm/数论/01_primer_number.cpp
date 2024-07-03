#include <cmath>

// 1.1 素数判断
bool isPrimerNumber(int N)
{
    // 边界值判断
    if (N <= 1)
        return false;
    if (N == 2) 
        return true;
    
    // 遍历[2~sqrt(N)]，搜索N的因子
    int max_x = std::sqrt(N) + 1;
    for (int x = 2; x <= max_x; ++x)
    {
        // 存在因子，N是合数
        if (N % x == 0)
        {
            return false;
        }
    }

    // N不存在因子，N是素数
    return true;
}

// 1.2 埃氏筛
