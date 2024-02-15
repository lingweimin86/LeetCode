#include <vector>

using namespace std;


struct Node;

struct Edge {
    int weight;
    Node from;
    Node to;
};

struct Node {
    int value;
    int in;
    int out;
    vector<Node> nextNodes;
    vector<Edge> edges;
};


// 宽度优先，利用队列实现

// 深度优先， 利用栈实现

// 拓扑排序, 按依赖关系进行排序



// kruskal 算法 - 生成最小生成树， 要求无向图

// prim 算法， 要求无向图