/**
一条包含字母 A-Z 的消息通过以下方式进行了编码：

'A' -> 1
'B' -> 2
...
'Z' -> 26
给定一个只包含数字的非空字符串，请计算解码方法的总数。

示例 1:

输入: "12"
输出: 2
解释: 它可以解码为 "AB"（1 2）或者 "L"（12）。
示例 2:

输入: "226"
输出: 3
解释: 它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/decode-ways
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
*/

#include <iostream>
#include <vector>
using namespace std;

class SolutionBad
{
public:
    int total;
    int numDecodings(string s)
    {
        if (s.empty())
            return 0;
        // 10
        // 暴力的方式, 回溯算法 截取一个或者两个
        total = 0;
        numDecodings(s, 0, s.length());
        return total;
    }

    void numDecodings(string &s, int cur, int end)
    {
        if (cur == end)
        {
            cout << total << endl;
            total++;
            return;
        }
        // 选择
        if (s[cur] == '0')
        {
            return;
        }
        else if (s[cur] == '1')
        {
            if (cur <= (end - 2))
            { // 可以选两个
                numDecodings(s, cur + 1, end);
                numDecodings(s, cur + 2, end);
            }
            else
            {
                numDecodings(s, cur + 1, end);
            }
        }
        else if (s[cur] == '2')
        {
            if (cur <= (end - 2) && s[cur + 1] <= '6')
            { // 可以选两个
                numDecodings(s, cur + 1, end);
                numDecodings(s, cur + 2, end);
            }
            else
            {
                numDecodings(s, cur + 1, end);
            }
        }
        else
        {
            numDecodings(s, cur + 1, end);
        }
    }
};

class SolutionBad2
{
public:
    int total;
    int numDecodings(string s)
    {
        if (s.empty() || s[0] == '0')
            return 0;
        total = 0;
        numDecodings(s, 0, s.length());
        return total;
    }

    void numDecodings(string &s, int cur, int end)
    {
        // 能走到最后,可能说明解码成功了
        if (cur == end)
        {
            total++;
            return;
        }
        // 无效解码
        if (s[cur] == '0')
            return;
        //如果可以选两个进行解码
        if (cur <= (end - 2))
        {
            if (s[cur] == '1' ||
                (s[cur] == '2' && s[cur + 1] <= '6'))
            {
                numDecodings(s, cur + 2, end);
            }
        }
        // 绝对可以解码1个的
        numDecodings(s, cur + 1, end);
    }
};

class SolutionGood1
{
public:
    int numDecodings(string s)
    {
        if (s.empty() || s[0] == '0')
            return 0;
        if (s.length() == 1)
            return 1;
        return numDecodings(s, 0, s.length() - 1);
        ;
    }

    int numDecodings(string &s, int begin, int end)
    {
        // 无效解码
        if (s[begin] == '0')
            return 0;
        // 仅一位数字 (排除了'0'),有效解码
        if (end - begin <= 0)
            return 1;
        // 起码两位长度的字符串了
        // 先取一位
        const int count1 = numDecodings(s, begin + 1, end);
        const int value = stoi(s.substr(begin, 2));
        int count2 = 0;
        if (value >= 10 && value <= 26)
            count2 = numDecodings(s, begin + 2, end);
        return count1 + count2;
    }
};

// 懵逼了有点: 推荐 查看解题方式 https://leetcode-cn.com/problems/decode-ways/solution/c-wo-ren-wei-hen-jian-dan-zhi-guan-de-jie-fa-by-pr/

/**
 * 犯的错误 
 * 1. 没有手写举例 几个 case, 心算容易有问题
 * 2. ASCII 码认识有问题, '1' 直接当做了 1
 * 
 * 一定要回想走楼梯或者偷东西两个案例
*/
int numDecodings(string s)
{
    if (s[0] == '0')
        return 0;
    int pre = 1, curr = 1; //dp[-1] = dp[0] = 1 为什么呢, 这是因为更新了 pre
    for (int i = 1; i < s.size(); i++)
    {
        int tmp = curr;
        if (s[i] == '0')
            if (s[i - 1] == '1' || s[i - 1] == '2')
                curr = pre;
            else
                return 0;
        else if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] >= '1' && s[i] <= '6'))
            curr = curr + pre;
        pre = tmp;
    }
    return curr;
}

/***
 *  推荐题解二 
 链接：https://leetcode-cn.com/problems/decode-ways/solution/jing-dian-di-tui-by-haozheyan97/

   迁移方程
  f(0) = 1
  f(i) = valid(lastOneSymbol) * f(i - 1) + valid(lastTwoSymbols) * f(i - 2)

 * 
 * 
*/

class Solution
{
public:
    int *dp;

    bool check(char h, char l)
    {
        int hh = h - '0', ll = l - '0';
        int val = hh * 10 + ll;

        return val >= 10 && val <= 26;
    }

    int numDecodings(string s)
    {
        int n = s.length();
        dp = (int *)malloc((n + 1) * sizeof(int));

        dp[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            dp[i] = 0;
            if (s[i - 1] > '0')
                dp[i] += dp[i - 1];
            if (i > 1 && check(s[i - 2], s[i - 1]))
                dp[i] += dp[i - 2];
        }

        return dp[n];
    }
};

class SolutionDP1
{
public:
    int numDecodings(string s)
    {
        if (s.empty() || s[0] == '0')
            return 0;
        if (s.length() == 1)
            return 1;
        // 定义 dp[i] 为从0~i的子字符串的解码情况
        vector<int> dp(s.length(), 0);
        // 空字符串 解码为一种
        dp[-1] = 1;
        // 单个字符的话(排除了'0') 解码为一种
        dp[0] = 1;
        /// 我们仅仅需要累计 解码一个字符与解码两个字符 的情况即可
        for (int i = 1; i < s.length(); ++i)
        {
            if (!isValidSingle(s[i]) && !isValidTwoChar(s[i - 1], s[i]))
            { // 如果s[i] 无效 且 s[i]s[i-1] 那么不管s[i-2]如何大,都没用,后面的两个数值都无法完成解码
                dp[i] = 0 + 0;
            }
            else if (!isValidSingle(s[i]) && isValidTwoChar(s[i - 1], s[i]))
            { // 如果 s[i] 无效, s[i-1][i] 有效, 说明两个字符的解码成功, 一个字符的解码失败
                dp[i] = 0 + dp[i - 2];
            }
            else if (isValidSingle(s[i]) && !isValidTwoChar(s[i - 1], s[i]))
            { // 如果 s[i] 有效 s[i-1]s[i] 无效 ,那么 说明两个字符的没有解码成功, 一个字符的解码成功了
                dp[i] = dp[i - 1] + 0;
            }
            else
            { // 肯定是 两个都有效了
                dp[i] = dp[i - 1] + dp[i - 2];
            }
        }
        return dp[s.length() - 1];
    }

private:
    bool isValidSingle(const char c)
    {
        return c != '0';
    }
    bool isValidTwoChar(const char l, const char r)
    {
        const int value = (l - '0') * 10 + (r - '0');
        return value >= 10 && value <= 26;
    }
};