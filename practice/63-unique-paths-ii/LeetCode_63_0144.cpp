/**
 * 
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？



网格中的障碍物和空位置分别用 1 和 0 来表示。

说明：m 和 n 的值均不超过 100。

示例 1:

输入:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
输出: 2
解释:
3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：
1. 向右 -> 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右 -> 向右

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-paths-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size();
        if (m < 1)
            return 0;
        int n = obstacleGrid[0].size();
        if (n < 1)
            return 1;
        long ans[m][n];
        // 首列
        for (int i = 0; i < m; ++i)
        {
            if (obstacleGrid[i][0] == 1)
            {
                ans[i][0] = 0;
            }
            else
            {
                ans[i][0] = i == 0 ? 1 : ans[i - 1][0];
            }
        }
        // 首行
        for (int i = 0; i < n; ++i)
        {
            if (obstacleGrid[0][i] == 1)
            {
                ans[0][i] = 0;
            }
            else
            {
                ans[0][i] = i == 0 ? 1 : ans[0][i - 1];
            }
        }

        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    ans[i][j] = 0;
                }
                else
                {
                    // 如果不为空
                    ans[i][j] = ans[i - 1][j] + ans[i][j - 1];
                }
            }
        }
        return ans[m - 1][n - 1];
    }
};