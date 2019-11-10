/**
 * 
 * 给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

说明：你不能倾斜容器，且 n 的值至少为 2。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/container-with-most-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

示例:

输入: [1,8,6,2,5,4,8,3,7]
输出: 49
 * 
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    /**
     * 
     * ① 高效处理, 从最大宽度开始算起,哪侧低,则收缩哪侧, 因为较高的那侧收缩不仅宽度减少,并且高度不会增加; 
     * ② 收缩一个值后,你会发现,这就变成递归求解了, 大问题变成小问题!! 
     * 
    */
    int maxArea(vector<int>& height) {
        int area = 0, maxArea = 0, minHeight;
        for (int i = 0 , j = height.size() - 1 ; i < j ;) {
            // 当然也可以先计算面积,再收敛
            minHeight = height.at(i) < height.at(j) ? height.at(i ++) : height.at(j --);
            // j - i + 1的原因是 前面宽度已经收缩了
            area = minHeight * (j - i + 1);
            maxArea = max(maxArea,area);
        }
        return maxArea;
    }
    // 1664 ms	
    int maxAreaBFSkip(vector<int>& height) {
        int area = 0;
        int oldY = 0;
        int curArea = 0;
        for (int i = 0 ; i < height.size() - 1 ; i++) {
            oldY = 0;
            for (int j = height.size() - 1; j > i; j--) {
                if (height.at(j) > oldY) {
                    curArea = min(height.at(j) , height.at(i)) * (j - i);
                    cout << "area: " << curArea << endl;
                    if (curArea > area) {
                        area = curArea;
                        oldY = height.at(j);
                    }
                }
            }
        }
        return area;
    }

    /// 超时
    int maxAreaBF(vector<int>& height) {
        int area = 0;
        for (int i = 0 ; i < height.size() - 1 ; i++) {
            for (int j = i + 1; j < height.size(); j++) {
                // 高 * 宽 ; 高是 minY, 宽是 deltaX
                area = max(area, min(height.at(j) , height.at(i)) * (j - i));
            }
        }
        return area;
    }
};


int main () {
    vector<int> height = {1,8,6,2,5,4,8,3,7};
    int max = Solution().maxArea(height);
    cout << "maxArea: " << max << endl;
    return 0;
}