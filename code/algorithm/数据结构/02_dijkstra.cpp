// dijkstra算法: 求解非负权图的单源最短路径问题
// 场景: 给出一个图的结点数n和所有的边信息(u,v,w), u,v代表边的两个结点，w代表边的权重，求出结点i到其余所有结点的最短路径
// 使用小根堆+邻接矩阵实现

#include <vector>
#include <queue>

std::vector<int> dijkstra(int n, std::vector<std::vector<int>> edges, int i)
{
    // 构建图邻接矩阵
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (const auto& edge : edges)
    {
        adj[edge[0]].emplace_back(edge[1], edge[2]);
        adj[edge[1]].emplace_back(edge[0], edge[2]);
    }

    // 使用小根堆存储已遍历的结点及其最短距离
    std::priority_queue<std::pair<int , int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.emplace(0, i);

    std::vector<int> dist(n, -1);
    dist[i] = 0;

    while (!pq.empty())
    {
        // 从小根堆中取出具有最小距离的结点
        auto [d, u] = pq.top();
        pq.pop();

        // 如果图存在重复边，取最小的距离
        if (d != dist[u])
            continue;

        // 松弛操作
        for (const auto& [v, w] : adj[u])
        {
            if (dist[v] == -1 || (d + w < dist[v]))
            {
                dist[v] = d + w;
                pq.emplace(dist[v], v);
            }
        }
    }

    return dist;
}