// kruskal算法: 求解图的最小生成树算法
// 最小生成树: 图内边权和最小的生成树
// 使用并查集结合排序实现

#include <vector>
#include <algorithm>

struct DSU{
    std::vector<int> parents;
    
    DSU(int n):parents(n){
        for (int i = 0; i < n; ++i)
        {
            parents[i] = i;
        }
    }
    ~DSU() = default;
    // 查找父元素
    int find_parent(int x)
    {
        if (x != parents[x])
        {
            parents[x] = find_parent(parents[x]);
        }
        return parents[x];
    }

    void union_set(int x, int y)
    {
        parents[find_parent(y)] = find_parent(x);
    }
};

int kruskal(int n, std::vector<std::vector<int>> edges)
{
    DSU dsu(n);
    std::sort(edges.begin(), edges.end(), [](const std::vector<int>& lhs, const std::vector<int>& rhs)->bool{
        return lhs[2] < rhs[2];
    });

    int res{0};
    for (const auto& edge : edges)
    {
        int u = edge[0], v = edge[1], w = edge[2];
        if (dsu.find_parent(u) != dsu.find_parent(v))
        {
            res += w;
            dsu.union_set(u, v);
        }
    }

    return res;
}