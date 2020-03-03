#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>

using namespace std;
class Solution
{
public:
    vector<int> threeWaysQuickSort(vector<int> &arr)
    {
        if (arr.size() <= 1)
        {
            return arr;
        }
        return threeWaysSwapQuickSort(arr);
        //       return threeWaysCountingQuickSort(arr);
    }

    /// 效率特别高, O(n)
    vector<int> threeWaysSwapQuickSort(vector<int> &arr)
    {
        // 交换法 , 肯定需要用指针定位才可以
        /// 分界线 zero 右侧表示 1
        int zero = -1;
        /// 分界线 two 左侧表示 1
        int two = arr.size();
        // 这样就能使用这两个索引 将数组分为 三份,  zero(索引)  [x,x,x,x,x,x,x]  two(索引)
        // 下一个需要确认 1 的位置
        int i = 0;
        while (i < two)
        {
            if (arr[i] == 0)
            {
                // 下一个放zero的位置
                zero++;
                // 替换0到正确的位置
                swap(arr, zero, i);
                //
                i++;
            }
            else if (arr[i] == 1)
            {
                // 等于1 本身就在正确的位置, 不需要交互
                i++;
            }
            else
            {
                // 挪出来正确的位置, (原因是two从 size 开始)
                two--;
                // 替换2到正确的位置
                swap(arr, i, two);
            }
        }
        return arr;
    }

    /// 需要额外空间 , O(n) ,但是扩展性好, 比如分为4份, 5 份等等
    vector<int> threeWaysCountingQuickSort(vector<int> &arr)
    {
        int maxValue = 3;
        vector<int> counters = vector<int>(maxValue + 1, 0);
        for (auto v : arr)
        {
            counters[v]++;
        }
        vector<int> ans = vector<int>(arr.size(), 0);
        int next = 0;
        for (int i = 0; i < counters.size(); i++)
        {
            int count = counters[i];
            while (count)
            {
                ans[next] = i;
                next++;
                count--;
            }
        }
        return ans;
    }
    void swap(vector<int> &arr, int lo, int hi)
    {
        int temp = arr[lo];
        arr[lo] = arr[hi];
        arr[hi] = temp;
    }
};

int main()
{
    // 算法题, 红白蓝 三个颜色的乱序数组, 整理成有序的数组
    vector<int> v = {2, 0, 2, 1, 1, 0};
    Solution().threeWaysQuickSort(v);
}