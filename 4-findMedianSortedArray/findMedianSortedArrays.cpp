/***
 * 给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。

请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

你可以假设 nums1 和 nums2 不会同时为空。

示例 1: 总长度奇数个

nums1 = [1, 3]
nums2 = [2]

则中位数是 2.0
示例 2: 总长度偶数个

nums1 = [1, 2]
nums2 = [3, 4]

则中位数是 (2 + 3)/2 = 2.5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
  

分成三组数据：

第一组数据 20 分，代表已经可以解决当前问题，但是面试官并不满意。

第二组数据 60 分，代表已经达到面试要求。

第三组数据 100 分，代表这是最高效的解法。

PS. 这是拼多多 客户端三面面试题，要求白板代码，大家可以体验一下。
  * 
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdint> 
#include <stdint.h>
#include <limits>
#include <climits>
#include <string>      
#include <sstream> 
#include <iomanip>

using namespace std;

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        if (n > m) {
            return findMedianSortedArrays(nums2,nums1);
        }
        
        int lMax1,lMax2,rMin1,rMin2,c1,c2,lo = 0, li = 2 * n;
        
        while (lo <= li) {
            c1 = (lo + li) / 2;
            c2 = m + n - c1;
            lMax1 = (c1 == 0) ? INT_MIN : nums1.at( (c1-1)/2 );
            rMin1 = (c1 == 2 * n) ? INT_MAX : nums1.at( c1/2 );
            lMax2 = (c2 == 0) ? INT_MIN : nums2.at( (c2-1)/2 );
            rMin2 = (c2 == 2 * m) ? INT_MAX : nums2.at( c2/2 );
            
            if (lMax1 > rMin2) {
                li = c1 - 1;
            } else if (lMax2 > rMin1) {
                lo = c1 + 1;
            } else {
                break;
            }
        }
        
        return (max(lMax1, lMax2) + min(rMin1, rMin2)) / 2.0;
    }
};

int main () {
    int n , m ;
    while (cin >> n >> m) {
        vector<int> nums1;
        int temp;
        for (int i = 0 ; i < n; i ++) {
            cin >> temp;
            nums1.push_back(temp);
        }

        vector<int> nums2;
        for (int i = 0 ; i < m; i ++) {
            cin >> temp;
            nums2.push_back(temp);
        }
        double ret = Solution().findMedianSortedArrays(nums1,nums2); 
        cout  << setiosflags(ios::fixed) << setprecision(1) << ret << endl;
    }
}