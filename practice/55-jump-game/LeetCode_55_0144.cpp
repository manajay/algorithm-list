/**
给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个位置。

示例 1:

输入: [2,3,1,1,4]
输出: true
解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。
示例 2:

输入: [3,2,1,0,4]
输出: false
解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/jump-game
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
*/

#include <iostream>
#include <vector>
using namespace std;

class SolutionBacktrace
{
public:
    // 回溯超时
    bool canJump(vector<int> &nums)
    {
        if (nums.size() == 0)
            return false;
        if (nums.size() == 1)
            return true;
        vector<bool> visited(nums.size(), false);
        bool can = false;
        visited[0] = true;
        backtrack(visited, 0, nums, can);
        return can;
    }
    void backtrack(vector<bool> &visited, int visiteIndex, vector<int> &nums, bool &can)
    {
        int i = nums[visiteIndex];
        while (i >= 1)
        {
            int newIndex = visiteIndex + i;
            if (newIndex >= nums.size() - 1)
            {
                can = true;
                break;
            }
            else if (visited[newIndex])
            {
                i--;
                continue;
            }
            else
            {
                visited[newIndex] = true;
                backtrack(visited, newIndex, nums, can);
            }
            i--;
        }
    }
};

#define min(a, b) ((a) < (b) ? (a) : (b))

// 动态规划算法
class SolutionDP
{
public:
    bool canJump(vector<int> &nums)
    {
        // 1 好位置 0 坏位置 -1 未知
        vector<int> situation(nums.size(), -1);
        situation[nums.size() - 1] = 1;
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            // 如果当前元素 与 元素值的和不小于 上一个 好位置的索引, 那么就表示 从 当前位置能够调到上一个好位置
            int further_max_good = min(i + nums[i], nums.size() - 1);
            for (int j = i + 1; j <= further_max_good; j++)
            {
                if (situation[j] == 1)
                {
                    situation[i] = 1;
                    break;
                }
            }
        }
        // 检查
        return situation[0] == 1;
    }
};

// 贪心算法
class SolutionGreedy
{
public:
    bool canJump(vector<int> &nums)
    {
        // 假设能够到达最后一个元素, 从后向前遍历, 检查最后一个好的位置是否是起点 0
        int lastGoodPosition = nums.size() - 1;
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            // 如果当前元素 与 元素值的和不小于 上一个 好位置的索引, 那么就表示 从 当前位置能够调到上一个好位置
            if ((i + nums[i]) >= lastGoodPosition)
            {
                lastGoodPosition = i;
            }
        }
        // 检查
        return lastGoodPosition == 0;
    }
};