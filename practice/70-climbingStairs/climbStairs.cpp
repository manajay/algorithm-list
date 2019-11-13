/**
 * 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

注意：给定 n 是一个正整数。

示例 1：

输入： 2
输出： 2
解释： 有两种方法可以爬到楼顶。
1.  1 阶 + 1 阶
2.  2 阶
示例 2：

输入： 3
输出： 3
解释： 有三种方法可以爬到楼顶。
1.  1 阶 + 1 阶 + 1 阶
2.  1 阶 + 2 阶
3.  2 阶 + 1 阶


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/climbing-stairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * climbStairs
*/ 

#include <iostream>
using namespace std;

class Solution {
public:

    /**
     * 
     * 解题思路
     * 1. 多看题 
     * 2. 用例 查看规律
     * 3. 要明白程序员写的代码是给机器执行的, 而机器逻辑能力不强, 基本只能执行 if-else ,for-loop, recursive 等操作
     * 所以你只要把边界条件和小问题弄明白, 后面的就会自然很多. 
     * 
     * 明天数学归纳法, 小问题 => 推荐大问题的思想
     * 
     * 
     * 类似这种多少可能的解法问题, 一般是动态的规划, 可以递归,改写 while 等
     * 明白动态迁移方程, 与基础条件
     * f(n) = f(n-1) + f(n-2);
    */
    int climbStairs(int n) {
        if (n <= 3){ return n;}
        int f1 = 1, f2 = 2, f3 = 3, i = 3;
        // 明确这里的循环次数, 可以尝试以 3 为 用例测试这里
        while (i <= n) {
            f3 = f1 + f2;
            f1 = f2;
            f2 = f3;
            i++;
        }
        return f3;
    }
};

int main(){
    int ret = Solution().climbStairs(6);
    cout << "ret: " << ret << endl;
}