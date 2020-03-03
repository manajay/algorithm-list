/***
给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

示例 :

给定这个链表：1->2->3->4->5

当 k = 2 时，应当返回: 2->1->4->3->5

当 k = 3 时，应当返回: 3->2->1->4->5

说明 :

你的算法只能使用常数的额外空间。
你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-nodes-in-k-group
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
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

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        if (head == NULL || head->next == NULL || k == 0 || k == 1)
        {
            return head;
        }
        // 抽离一个反转链表的方法
        // 快慢指针取出 k 个节点 为一个链表
        // 递归求解
        ListNode *preNode = new ListNode(-1);
        preNode->next = head;
        int length = 0;
        for (int i = 1; i <= k; i++)
        {
            if (preNode != NULL)
            {
                preNode = preNode->next;
                length = i;
            }
        }

        // 没有k的长度
        if (length < k)
        {
            return head;
        }
        // 还有一种情况是 刚好k-1个
        if (preNode == NULL)
        {
            return head;
        }

        // 已经反转的下一组head
        ListNode *nextKLinkHead = reverseKGroup(preNode->next, k);
        // 断开
        preNode->next = NULL;
        // 反转k
        ListNode *curHead = reverseLinkList(head);
        head->next = nextKLinkHead;
        return curHead;
    }

    // 反转大于2个的链表
    ListNode *reverseLinkList(ListNode *head)
    {
        if (head == NULL || head->next == NULL)
        {
            return head;
        }
        ListNode *nextHead = reverseLinkList(head->next);
        head->next->next = head;
        head->next = NULL;
        return nextHead;
    }
};