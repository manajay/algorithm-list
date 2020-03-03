/**
 * 
给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。

示例 1:

输入: 1->2->3->4->5->NULL, k = 2
输出: 4->5->1->2->3->NULL
解释:
向右旋转 1 步: 5->1->2->3->4->NULL
向右旋转 2 步: 4->5->1->2->3->NULL
示例 2:

输入: 0->1->2->NULL, k = 4
输出: 2->0->1->NULL
解释:
向右旋转 1 步: 2->0->1->NULL
向右旋转 2 步: 1->2->0->NULL
向右旋转 3 步: 0->1->2->NULL
向右旋转 4 步: 2->0->1->NULL

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rotate-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
using namespace std;

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (head == NULL || k == 0)
        {
            return head;
        }
        // 第一遍扫描链表的长度 ,对k取余得到真正移动的次数, m
        // 做成循环链表, 在真正需要断开的地方断开, 并返回该节点
        int length = 0;
        ListNode *dump = head;
        ListNode *last = NULL;
        while (dump != NULL)
        {
            if (dump->next == NULL)
            {
                last = dump;
            }
            dump = dump->next;
            length++;
        }
        k = k % length;
        // 如果是左旋就可以这样算
        // 如果是右旋
        k = length - k;
        // 循环链表
        last->next = head;
        // 重新链表并断开
        dump = new ListNode(-1);
        dump->next = head;
        for (int i = 0; i < k; i++)
        {
            dump = dump->next;
        }
        // dump 的下一个节点为断开的节点
        head = dump->next;
        dump->next = NULL;
        return head;
    }
};