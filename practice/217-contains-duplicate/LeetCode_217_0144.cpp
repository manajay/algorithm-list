/**
 给定一个整数数组，判断是否存在重复元素。

如果任何值在数组中出现至少两次，函数返回 true。如果数组中每个元素都不相同，则返回 false。

示例 1:

输入: [1,2,3,1]
输出: true
示例 2:

输入: [1,2,3,4]
输出: false
示例 3:

输入: [1,1,1,3,3,4,3,2,4,2]
输出: true

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/contains-duplicate
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
*/

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    bool containsDuplicate(vector<int> &nums)
    {
        if (nums.size() == 0)
            return false;
        unordered_map<int, int> map;
        int size = nums.size();
        // 不需要初始化, 只需要查询count
        for (int i = 0; i < size; i++)
        {
            map[nums[i]] = 0;
        }
        for (int i = 0; i < size; i++)
        {
            map[nums[i]] += 1;
            if (map[nums[i]] > 1)
            {
                return true;
            }
        }
        return false;
    }
};

// 1. 排序后 发现连续的是否有相等的
// 2. 使用 hash 计算重复元素
// 3. 使用 set 计算重复元素

/// 语法不熟悉, 不初始化
class Solution
{
public:
    bool containsDuplicate(vector<int> &nums)
    {
        unordered_map<int, int> map; //无序map更快
        for (int i = 0; i < nums.size(); i++)
            if (map.count(nums[i]) != NULL)
                return true;
            else
                map[nums[i]] += 1;
        return false;
    }
};

// 作者：heroine - yun
//                     链接：https : //leetcode-cn.com/problems/contains-duplicate/solution/wei-shi-yao-yong-map-by-vailing/
//                                   来源：力扣（LeetCode）
//                                       著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

class Solution
{
public:
    bool containsDuplicate(vector<int> &nums)
    {
        set<int> s(nums.begin(), nums.end());
        return s.size() != nums.size();
    }
};

// 作者：QQqun902025048
// 链接：https://leetcode-cn.com/problems/contains-duplicate/solution/2xing-c-by-qqqun902025048/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
