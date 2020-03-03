/** 

https://leetcode-cn.com/problems/reverse-bits/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-4-9/

颠倒给定的 32 位无符号整数的二进制位。


示例 1：

输入: 00000010100101000001111010011100
输出: 00111001011110000010100101000000
解释: 输入的二进制串 00000010100101000001111010011100 表示无符号整数 43261596，
      因此返回 964176192，其二进制表示形式为 00111001011110000010100101000000。
示例 2：

输入：11111111111111111111111111111101
输出：10111111111111111111111111111111
解释：输入的二进制串 11111111111111111111111111111101 表示无符号整数 4294967293，
      因此返回 3221225471 其二进制表示形式为 10101111110010110010011101101001。
 

提示：

请注意，在某些语言（如 Java）中，没有无符号整数类型。在这种情况下，输入和输出都将被指定为有符号整数类型，并且不应影响您的实现，因为无论整数是有符号的还是无符号的，其内部的二进制表示形式都是相同的。
在 Java 中，编译器使用二进制补码记法来表示有符号整数。因此，在上面的 示例 2 中，输入表示有符号整数 -3，输出表示有符号整数 -1073741825。
 

进阶:
如果多次调用这个函数，你将如何优化你的算法？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-bits
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        // 注意这里的单位也得 无符号32位
        uint32_t ans = 0;
        int i = 0;
        while (i < 32)
        {
            // 左移一位, 空余出位置来获取n的该位置的值
            ans <<= 1;
            ans += (n & 1);
            n >>= 1;
            i++;
        }
        return ans;
    }
};

class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t ret = 0;
        // (((n>>(31-i)) & 1) << i) 所做的操作就是 ((从最低位往最高位取出 n 对应位上的值) << 将取到的值从最高位往最低位偏移)，其实就是将 n 的第 31 -i 位颠倒
        for (int i = 31; i >= 0; i--)
        {
            ret = ret | (((n >> (31 - i)) & 1) << i);
        }

        return ret;
    }
};

// 作者：li-ke-sen
// 链接：https://leetcode-cn.com/problems/reverse-bits/solution/li-yong-wei-cao-zuo-jie-ti-qian-xian-yi-dong-by-li/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

// 和反转字符串一样
class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        // 递归颠倒
        n = ((n & 0xffff0000) >> 16) | ((n & 0x0000ffff) << 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
    }
};