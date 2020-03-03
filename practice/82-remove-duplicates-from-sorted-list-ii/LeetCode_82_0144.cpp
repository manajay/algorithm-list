/**
 * 
给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字。

示例 1:

输入: 1->2->3->3->4->4->5
输出: 1->2->5
示例 2:

输入: 1->1->1->2->3
输出: 2->3

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (head == NULL || head->next == NULL)
        {
            return head;
        }
        ListNode *dump = new ListNode(-1);
        dump->next = head;

        // 记录上一个不能被删除的
        ListNode *preNode = dump;
        while (head != NULL && head->next != NULL)
        {
            if (head->val == head->next->val)
            { // 相同, head前进
                head = head->next;
                // 特殊情况
                if (head->next == NULL)
                {
                    preNode->next = NULL;
                }
            }
            else
            { // 不相等
                if (preNode->next == head)
                { // pre与head 相邻, 因为pre是有效数字 相当于连续3个有效数字, 可以前进
                    preNode = head;
                    head = head->next;
                }
                else
                {
                    preNode->next = head->next;
                    head = head->next;
                }
            }
        }
        return dump->next;
    }
};

class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (head == NULL)
            return head;
        if (head->next != NULL && head->val == head->next->val)
        { //找相同数
            while (head->next != NULL && head->val == head->next->val)
                head = head->next;               //忽略所有相同数
            return deleteDuplicates(head->next); //从下一个不同数再开始递归
        }
        else
            head->next = deleteDuplicates(head->next);
        return head;
    }
};

// 作者：24shi - 01fen - _00_01 链接：https : //leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/solution/si-chong-fang-fa-by-24shi-01fen-_00_01-2/
//                                            来源：力扣（LeetCode） 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode *dummy = new ListNode(-1), *slow = dummy, *fast = head;
        dummy->next = head;
        while (fast != NULL && fast->next != NULL)
        { //快指针用于查找相同元素
            if (fast->val != fast->next->val)
            {
                if (slow->next == fast)
                    slow = fast; //快指针先前没查找到相同数
                else
                    slow->next = fast->next; //先前查找到相同数，将出现相同数的前一个数连接到相同数后第一个不同数
            }
            fast = fast->next;
        }
        if (slow->next != fast)
            slow->next = fast->next; // 针对类似[1,1]的情况
        return dummy->next;
    }
};

// 作者：24shi - 01fen - _00_01 链接：https : //leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/solution/si-chong-fang-fa-by-24shi-01fen-_00_01-2/
//                                            来源：力扣（LeetCode） 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。