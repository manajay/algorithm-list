/**
 * 
让我们一起来玩扫雷游戏！

给定一个代表游戏板的二维字符矩阵。 'M' 代表一个未挖出的地雷，'E' 代表一个未挖出的空方块，'B' 代表没有相邻（上，下，左，右，和所有4个对角线）地雷的已挖出的空白方块，数字（'1' 到 '8'）表示有多少地雷与这块已挖出的方块相邻，'X' 则表示一个已挖出的地雷。

现在给出在所有未挖出的方块中（'M'或者'E'）的下一个点击位置（行和列索引），根据以下规则，返回相应位置被点击后对应的面板：

如果一个地雷（'M'）被挖出，游戏就结束了- 把它改为 'X'。
如果一个没有相邻地雷的空方块（'E'）被挖出，修改它为（'B'），并且所有和其相邻的方块都应该被递归地揭露。
如果一个至少与一个地雷相邻的空方块（'E'）被挖出，修改它为数字（'1'到'8'），表示相邻地雷的数量。
如果在此次点击中，若无更多方块可被揭露，则返回面板。
 

示例 1：

输入: 

[['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'M', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E']]

Click : [3,0]

输出: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

解释:

示例 2：

输入: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Click : [1,2]

输出: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'X', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

解释:

 

注意：

输入矩阵的宽和高的范围为 [1,50]。
点击的位置只能是未被挖出的方块 ('M' 或者 'E')，这也意味着面板至少包含一个可点击的方块。
输入面板不会是游戏结束的状态（即有地雷已被挖出）。
简单起见，未提及的规则在这个问题中可被忽略。例如，当游戏结束时你不需要挖出所有地雷，考虑所有你可能赢得游戏或标记方块的情况。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minesweeper
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
*/

#include <iostream>
#include <vector>
using namespace std;

/**
 执行用时 :
108 ms, 在所有 C++ 提交中击败了13.18%的用户
内存消耗 :45.6 MB, 在所有 C++ 提交中击败了6.15%的用户

这个问题首先是 理解题意
1. 停止的时机, 当前点击到 地雷或者 周边 点击到第一个地雷的时候 即停止
2. 计算周边的地雷个数, 周边的含义是 vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}; 这 8 个方向
3. 点击 'E' 的时候就是说 换成 空白 'B' 并递归周边的空白
 * 
*/

class Solution
{
public:
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click)
    {
        // 当前点击的位置
        int row = click[0], col = click[1];
        int m = board.size(), n = board[0].size();
        // 条件1 是否点击了 雷
        if (board[row][col] == 'M' || board[row][col] == 'X')
        {
            board[row][col] = 'X';
            return board;
        }
        // 简单方法, 遍历二维数组的多个方向, 记住几个技巧
        vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        int number = 0;
        for (pair<int, int> rc : directions)
        {
            int n_r = row + rc.first;
            int n_c = col + rc.second;
            // 周边有 'M'
            if (n_r >= 0 && n_r < m && n_c >= 0 && n_c < n && board[n_r][n_c] == 'M')
            {
                number++;
            }
        }

        if (number > 0)
        {
            // 更新其数字
            board[row][col] = number + '0';
            return board;
        }
        // 说明没有周围没有地雷, 那么递归去更新即可
        if (board[row][col] == 'E')
        {
            board[row][col] = 'B';
        }
        for (pair<int, int> rc : directions)
        {
            int n_r = row + rc.first;
            int n_c = col + rc.second;
            // 周边有 'M'
            if (n_r >= 0 && n_r < m && n_c >= 0 && n_c < n && board[n_r][n_c] == 'E')
            {
                board[n_r][n_c] = 'B';
                vector<int> new_click = {n_r, n_c};
                updateBoard(board, new_click);
            }
        }
        return board;
    }
};