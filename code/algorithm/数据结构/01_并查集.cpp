#include <vector>

// 由于外部经常需要访问parents，因此使用struct实现并查集
struct DSU{
    std::vector<int> parents;

    // 初始化并查集，将各自结点的根节点都初始化为自己
    DSU(int n):parents(n)
    {
        for (int i = 0; i < n; ++i)
        {
            parents[i] = i;
        }
    };
};

typedef struct DSU DSU;

// 找元素x的根节点
// 根节点的特点 x = parents[x];
int FindParentDSU(DSU& dsu, int x)
{
    // 没有找到根节点
    // 继续找，并更新沿途所有元素的根节点，使树的高度降低
    if (x != dsu.parents[x])
    {
        dsu.parents[x] = FindParentDSU(dsu, dsu.parents[x]);
    }

    // 找到根节点， 返回根结点
    return dsu.parents[x];
}

// 合并两个集合
// 将y所在集合合并入x所在集合 y -> x
void UnoinDSU(DSU& dsu, int x, int y)
{
    dsu.parents[FindParentDSU(dsu, y)] = FindParentDSU(dsu, x);
}