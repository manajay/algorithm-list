/**
 * 
编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：

每行中的整数从左到右按升序排列。
每行的第一个整数大于前一行的最后一个整数。
示例 1:

输入:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 3
输出: true
示例 2:

输入:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 13
输出: false

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/search-a-2d-matrix
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int m = matrix.size();
        if (m == 0)
            return false;
        int n = matrix[0].size();

        // 二分查找
        int left = 0, right = m * n - 1;
        int pivotIdx, pivotElement;
        while (left <= right)
        {
            // 中间索引
            pivotIdx = (left + right) / 2;
            // 行中间元素
            pivotElement = matrix[pivotIdx / n][pivotIdx % n];
            if (target == pivotElement)
                return true;
            else
            {
                if (target < pivotElement)
                    right = pivotIdx - 1;
                else
                    left = pivotIdx + 1;
            }
        }
        return false;
    }
};

/**
 * 二分 我的写法
 * 
*/
class Solution
{
public:
    int rows;
    int cols;
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        rows = matrix.size();
        if (rows == 0)
            return false;
        cols = rows > 0 ? matrix[0].size() : 0;
        if (cols == 0)
            return false;

        // 查询中间层是否符合
        int lo = 0, hi = rows - 1;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            int direct = findDirection(mid, matrix, target);
            if (direct == 0)
            {
                return findTarget(mid, matrix, target);
            }
            else if (direct == 1)
            {
                lo = mid + 1;
            }
            else
            {
                hi = mid - 1;
            }
        }
        return false;
    }
    // 在该行的上:-1, 下: 1 , 中间: 0;
    int findDirection(int row, vector<vector<int>> &matrix, int target)
    {
        vector<int> nums = matrix[row];
        int min = nums[0], max = nums[nums.size() - 1];
        if (target < min)
        {
            return -1;
        }
        else if (target > max)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    bool findTarget(int row, vector<vector<int>> &matrix, int target)
    {
        // 二分查询
        vector<int> nums = matrix[row];
        int lo = 0, hi = cols - 1;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target)
            {
                return true;
            }
            else if (nums[mid] < target)
            {
                lo = mid + 1;
            }
            else
            {
                hi = mid - 1;
            }
        }
        return false;
    }
};

int main(int argc, char **argv)
{
}