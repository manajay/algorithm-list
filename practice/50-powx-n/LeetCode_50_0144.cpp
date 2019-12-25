/**
 * 
实现 pow(x, n) ，即计算 x 的 n 次幂函数。

示例 1:

输入: 2.00000, 10
输出: 1024.00000
示例 2:

输入: 2.10000, 3
输出: 9.26100
示例 3:

输入: 2.00000, -2
输出: 0.25000
解释: 2-2 = 1/22 = 1/4 = 0.25
说明:

-100.0 < x < 100.0
n 是 32 位有符号整数，其数值范围是 [−231, 231 − 1] 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/powx-n
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * 
*/

/**
 * 快速幂   求解
 * 
 * 我的解法代码不优化
 * 注意 
 * 1. 边界 特殊值 n: [0,1]
 * 2. 幂的负数情况 2.100000 -2
 * 3. int 边界值 的取反 溢出问题  1.00000 -2147483648
 * 4. 递归的奇偶性问题
 * 
 * 
*/

class Solution
{
public:
    double myOldPow(double x, int n)
    {
        // 二分 结束
        if (n == 1) // 这个不需要, 去掉
            return x;
        if (n == 0)
            return 1;
        long ln = n;
        bool negtive = false;
        if (ln < 0)
        {
            negtive = true;
            ln = -ln;
        }

        // 重复子问题 -> 规模, 单位转换 只需要一次, 递归传值改一下
        double ret = myPow(x, ln / 2);
        // 奇偶数判断
        if (ln % 2 == 0)
        {
            ret = ret * ret;
        }
        else
        {
            ret = ret * ret * x;
        }

        // 不需要这个, 去掉
        if (ret == 0)
            return 0;
        return negtive ? 1 / ret : ret;
    }

    double myPow(double x, int n)
    {
        return myNewPow(x, n);
    }

    double myNewPow(double x, long long n)
    {
        // 二分 结束
        if (x == 0)
            return 0;
        if (n == 0)
            return 1;
        if (n < 0)
        {
            x = 1 / x;
            n = -n;
        }

        // 重复子问题 -> 规模, 单位转换 只需要一次, 递归传值改一下
        double ret = myNewPow(x, n / 2);
        // 奇偶数判断
        if (n % 2 == 0)
        {
            ret = ret * ret;
        }
        else
        {
            ret = ret * ret * x;
        }
        return ret;
    }
};

class SolutionRecommend
{
public:
    double qpow(double a, long long b)
    {
        double res = 1;
        // 自顶向上
        while (b)
        {
            // 奇数
            if (b & 1)
                res = res * a;
            // 二分
            b >>= 1;
            // 二分结果
            a *= a;
        }
        return res;
    }

    double myPow(double x, int n)
    {
        return myPowLongN(x, n);
    }

    double myPowLongN(double x, long long n)
    {
        if (n == 0)
            return 1;
        if (n > 0)
            return qpow(x, n);
        if (n < 0)
            return 1 / qpow(x, -n);
        return 1.0;
    }
};
