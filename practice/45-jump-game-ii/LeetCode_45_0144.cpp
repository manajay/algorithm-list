/**
给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。

示例:

输入: [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
说明:

假设你总是可以到达数组的最后一个位置。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/jump-game-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
*/

#include <iostream>
#include <vector>
using namespace std;

/**
贪心算法:
顺序遍历, 更新最大位置的点
遍历到该点的时候 更新步数
 https://leetcode-cn.com/problems/jump-game-ii/solution/45-by-ikaruga/
 * 
*/
class SolutionGreedy
{
public:
    int jump(vector<int> &nums)
    {
        // 前面能够跳跃的最远举例
        int maxPostion = 0, end = 0;
        int step = 0;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            // 每到一个点 比较其跳跃的地点与 以前能跳远的最远的位置 哪个更远, 更新其值
            maxPostion = max(i + nums[i], maxPostion);
            // 与上一个最远的距离 匹配的时候, 更新步数
            if (i == end)
            {
                end = maxPostion;
                step++;
            }
        }
        return step;
    }
};

// https://leetcode-cn.com/problems/jump-game-ii/solution/si-chong-can-kao-jie-fa-by-jason-2/

class SolutionDP
{
public:
    int jump(vector<int> &nums)
    {
        const int N = nums.size();
        if (N <= 1)
            return 0;
        vector<int> d(N, 0);
        for (int i = 1; i < N; ++i)
        {
            int &ans = d[i];
            ans = INT_MAX;
            for (int j = 0; j < i; ++j)
            {
                if (j + nums[j] >= i)
                {
                    ans = min(ans, d[j] + 1);
                }
            }
        }
        return d[N - 1];
    }
};

#include <queue>
/**
 * 
将每个位置当成节点，跳跃关系当成边，就构成了无向图。问题就转化为，无向图中，节点0到节点N-1的最短距离问题。
*/
class SolutionBFS
{
public:
    typedef pair<int, int> Pair;
    int jump(vector<int> &nums)
    {
        const int N = nums.size();
        if (N <= 1)
            return 0;
        vector<int> vis(N, 0);
        queue<Pair> Q;
        Q.push(make_pair(0, 0));
        vis[0] = 1;
        while (Q.size())
        {
            Pair cur = Q.front();
            Q.pop();
            if (cur.first == N - 1)
                return cur.second;
            for (int i = min(cur.first + nums[cur.first], N - 1); i >= cur.first + 1; --i)
            {
                if (!vis[i])
                {
                    if (i == N - 1)
                        return cur.second + 1;
                    vis[i] = 1;
                    Q.push(make_pair(i, cur.second + 1));
                }
            }
        }
        return -1;
    }
};
main()
{
}