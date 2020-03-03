/*
设计一个最大栈，支持 push、pop、top、peekMax 和 popMax 操作。

 

push(x) -- 将元素 x 压入栈中。
pop() -- 移除栈顶元素并返回这个值。
top() -- 返回栈顶元素。
peekMax() -- 返回栈中最大元素。
popMax() -- 返回栈中最大的元素，并将其删除。如果有多个最大元素，只要删除最靠近栈顶的那个。
 

样例 1:

MaxStack stack = new MaxStack();
stack.push(5); 
stack.push(1);
stack.push(5);
stack.top(); -> 5
stack.popMax(); -> 5
stack.top(); -> 1
stack.peekMax(); -> 5
stack.pop(); -> 1
stack.top(); -> 5
 

注释:

-1e7 <= x <= 1e7
操作次数不会超过 10000。
当栈为空的时候不会出现后四个操作。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/max-stack
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
using namespace std;

class MaxStack
{
public:
    /** initialize your data structure here. */
    vector<int> nums;
    vector<int> maxs;
    MaxStack()
    {
    }

    void push(int x)
    {
        int size = nums.size();
        if (size == 0)
        {
            maxs.push_back(0);
        }
        else
        {
            int val = maxs.back();
            if (x < nums[val])
            {
                maxs.push_back(val);
            }
            else
            {
                maxs.push_back(size);
            }
        }
        nums.push_back(x);
    }

    int pop()
    {
        int val = nums.back();
        nums.pop_back();
        maxs.pop_back();
        return val;
    }

    int top()
    {
        return nums.back();
    }

    int peekMax()
    {
        int val = maxs.back();
        return nums[val];
    }
    /**
    case 1
    [2,3,4,5,2,7,7,2,5,8]
    [0,1,2,3,3,5,6,6,6,9]
     case 2
    [2,3,4,5,2,7,7,2,5]
    [0,1,2,3,3,5,6,6,6]
    */
    int popMax()
    {
        int size = nums.size();
        // 当前最大索引
        int val = maxs.back();
        int ans = nums[val];

        // 后面的数值需要重新计算maxs, 如果使用线性表,其时间复杂度为 O(n), 不能再优化, 除非使用其他的数据结构
        vector<int> res;
        for (int i = size - 1; i >= val; i--)
        {
            if (i != val)
            {
                res.push_back(nums[i]);
            }
            nums.pop_back();
            maxs.pop_back();
        }

        size = res.size();
        for (int i = size - 1; i >= 0; i--)
        {
            push(res[i]);
        }
        return ans;
    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */