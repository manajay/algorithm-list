/**
 * 
给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

示例 1:

输入:
11110
11010
11000
00000

输出: 1
示例 2:

输入:
11000
11000
00100
00011

输出: 3

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-islands
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 
 * 心理路程: 一看题有点蒙, 虽然看过提示说是 采用 沉岛 的方式去处理
 * 但是不太会 如何在二维数组去做 dfs 或者 bfs
 * 看过题解后发现不论是bfs 还是 dfs 解法都非常像

1. 遍历所有元素, 对于数组,二维数组或者多维数组的方法基本一样, 都是 多层  for 循环处理
2. 在遍历到一个 '1' 岛屿后, 采用不同的 搜索方式都可以将附近所有的 '1' 修改为 '0' 也就是说 沉岛处理
3. 重要的步骤有 二维数组的 四个方向 dfs/bfs , 注意边界

 * 
*/

#include <iostream>
#include <vector>
using namespace std;

// dfs 查找
class SolutionDFS
{
public:
    int r_c;
    int c_c;
    int numIslands(vector<vector<char>> &grid)
    {
        r_c = grid.size();
        if (r_c == 0)
            return 0;
        // 变量、函数、结构、类……等等，在相同的一个作用域中，只能有一个唯一的名称
        c_c = grid[0].size();
        if (c_c == 0)
            return 0;
        int count = 0;
        for (int r = 0; r < r_c; r++)
        {
            for (int c = 0; c < c_c; c++)
            {
                if (grid[r][c] == '1')
                {
                    dfs(grid, r, c);
                    count++;
                }
            }
        }
        return count;
    }

    void dfs(vector<vector<char>> &grid, int row, int col)
    {
        grid[row][col] = '0';
        // 左
        if (col - 1 >= 0 && grid[row][col - 1] == '1')
        {
            dfs(grid, row, col - 1);
        }
        // 右
        if (col + 1 < c_c && grid[row][col + 1] == '1')
        {
            dfs(grid, row, col + 1);
        }
        // 上
        if (row - 1 >= 0 && grid[row - 1][col] == '1')
        {
            dfs(grid, row - 1, col);
        }
        // 下
        if (row + 1 < r_c && grid[row + 1][col] == '1')
        {
            dfs(grid, row + 1, col);
        }
    }
};

// c++的头文件规定 没有 .h 的后缀名, 只是为了区分 c 语言, 而 <> 与 "" 区别是查找头文件的路径不同, <> 查找 include 路径, 而 "" 查找的是 项目的相对路径
#include <queue>

class SolutionBFS
{
public:
    int r_c;
    int c_c;
    int numIslands(vector<vector<char>> &grid)
    {
        r_c = grid.size();
        if (r_c == 0)
            return 0;
        // 变量、函数、结构、类……等等，在相同的一个作用域中，只能有一个唯一的名称
        c_c = grid[0].size();
        if (c_c == 0)
            return 0;
        int count = 0;
        for (int r = 0; r < r_c; r++)
        {
            for (int c = 0; c < c_c; c++)
            {
                if (grid[r][c] == '1')
                {
                    count++;
                    bfs(grid, r, c);
                }
            }
        }
        return count;
    }

    void bfs(vector<vector<char>> &grid, int row_i, int col_i)
    {
        queue<pair<int, int>> q;

        // 统一处理模式, 添加之后 立即更新为 '0', 或者添加之前更新也可以, 避免频繁的添加问题
        q.push(make_pair(row_i, col_i));
        grid[row_i][col_i] = '0';

        pair<int, int> node;
        while (!q.empty())
        {
            for (int i = 0; i < q.size(); i++)
            {
                node = q.front();
                q.pop();
                // 出问题的原因是 row和col 没有更新
                int row = node.first, col = node.second;
                // 左
                if (col - 1 >= 0 && grid[row][col - 1] == '1')
                {
                    q.push(make_pair(row, col - 1));
                    grid[row][col - 1] = '0';
                }
                // 右
                if (col + 1 < c_c && grid[row][col + 1] == '1')
                {
                    q.push(make_pair(row, col + 1));
                    grid[row][col + 1] = '0';
                }
                // 上
                if (row - 1 >= 0 && grid[row - 1][col] == '1')
                {
                    q.push(make_pair(row - 1, col));
                    grid[row - 1][col] = '0';
                }
                // 下
                if (row + 1 < r_c && grid[row + 1][col] == '1')
                {
                    q.push(make_pair(row + 1, col));
                    grid[row + 1][col] = '0';
                }
            }
        }
    }
};

/**
 * 并查集解法

链接：https://leetcode-cn.com/problems/number-of-islands/solution/dao-yu-shu-liang-by-leetcode/
 * 
*/

class UnionFind
{
public:
    UnionFind(vector<vector<char>> &grid)
    {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();

        // 下面是并查集的初始化, 如果元素为 '1' 则其公共祖先为自身的索引, 如果元素是 '0' 则公共祖先为 -1 也就是没有公共祖先

        // i 为行号
        for (int i = 0; i < m; ++i)
        {
            // j 为 列号, n是 一行有几列的值
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '1')
                {
                    // 当前节点的公共祖先是  行号 乘以 每行的个数 再加上 当前的列索引, 这里是为了将二维数组变为一维处理
                    parent.push_back(i * n + j);
                    ++count;
                }
                else
                    // 当前节点的公共祖先是自身
                    parent.push_back(-1);
                // 集合的层数
                rank.push_back(0);
            }
        }
    }

    /**
     * 并查集的查找
    */
    int find(int i)
    { // path compression
        if (parent[i] != i)
            // 并查集优化, 祖先更新为最上层的公共祖先
            parent[i] = find(parent[i]);
        return parent[i];
    }

    /**
     * 并查集的合并
     * 比较公共祖先, 不在一个集合则合并, 合并时要选取 秩小的 合并到 秩大的集合, 如果秩相等, 合并集合后 增加秩
    */
    void Union(int x, int y)
    { // union with rank
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty)
        {
            if (rank[rootx] > rank[rooty])
                parent[rooty] = rootx;
            else if (rank[rootx] < rank[rooty])
                parent[rootx] = rooty;
            else
            {
                parent[rooty] = rootx;
                rank[rootx] += 1;
            }
            --count;
        }
    }

    int getCount() const
    {
        return count;
    }

private:
    vector<int> parent;
    vector<int> rank;
    int count; // # of connected components
};

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int nr = grid.size();
        if (!nr)
            return 0;
        int nc = grid[0].size();
        // 初始化并查集
        UnionFind uf(grid);
        int num_islands = 0;
        // 遍历所有的元素
        for (int r = 0; r < nr; ++r)
        {
            for (int c = 0; c < nc; ++c)
            {
                // 如果元素是 岛屿
                if (grid[r][c] == '1')
                {
                    // 更新元素为 水, 防止重复检查
                    grid[r][c] = '0';
                    // 四个方向检查
                    // 合并周边元素(这里注意并查集初始化时 所有的 '1' 元素的 公共祖先都不一样,而所有的'0' 元素, 其公共祖先都为 -1 ,所以不需要合并) 注意这里传参是 二维数组转化为一维数组后的索引
                    // 合并过程中, 合并一次会 cout--, 一直到每个岛屿仅仅只剩下 一个公共祖先, 也就时只剩一个 count, 多个岛屿 合并后 只剩下岛屿数量的 公共祖先数
                    if (r - 1 >= 0 && grid[r - 1][c] == '1')
                        uf.Union(r * nc + c, (r - 1) * nc + c);
                    if (r + 1 < nr && grid[r + 1][c] == '1')
                        uf.Union(r * nc + c, (r + 1) * nc + c);
                    if (c - 1 >= 0 && grid[r][c - 1] == '1')
                        uf.Union(r * nc + c, r * nc + c - 1);
                    if (c + 1 < nc && grid[r][c + 1] == '1')
                        uf.Union(r * nc + c, r * nc + c + 1);
                }
            }
        }

        return uf.getCount();
    }
};