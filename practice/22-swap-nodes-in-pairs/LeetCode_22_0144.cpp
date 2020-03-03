/**
给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

 

示例:

给定 1->2->3->4, 你应该返回 2->1->4->3.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/swap-nodes-in-pairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
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

/*
执行用时 :0 ms, 在所有 C++ 提交中击败了100.00%的用户
内存消耗 :8.8 MB, 在所有 C++ 提交中击败了5.10%的用户

看来我这里内存消耗挺多的, 一个是函数调用, 一个是临时变量创建
而且写法不美观, 没有利用原来的函数
*/
class Solution
{
public:
    ListNode *swapPairs(ListNode *head)
    {
        if (head == NULL || head->next == NULL)
        {
            return head;
        }
        // 结果
        ListNode *reverseHead = head->next;

        // 单链表 哨兵
        ListNode *node = new ListNode(-1);
        node->next = head;
        ListNode *cur = head;
        while (cur != NULL && cur->next != NULL)
        {
            node->next = swapTwo(cur, cur->next);
            node = node->next->next;
            cur = node->next;
        }
        return reverseHead;
    }

    ListNode *swapTwo(ListNode *cur, ListNode *next)
    {
        ListNode *temp = next->next;
        next->next = cur;
        cur = next;
        cur->next->next = temp;
        return cur;
    }
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
    ListNode *swapPairs(ListNode *head)
    {
        if (head == NULL || head->next == NULL)
        {
            return head;
        }
        // 递归就是不关心后续的过程, 只关心结果
        ListNode *first = head;
        ListNode *second = head->next;
        // 反正后面两格子, 然后连上前面的
        first->next = swapPairs(second->next);
        // 反转前面的两个格子
        second->next = first;
        return second;
    }
};

/**
执行用时 :4 ms, 在所有 C++ 提交中击败了85.16%的用户内存消耗 :8.7 MB, 
在所有 C++ 提交中击败了18.21%的用户

发现还不如使用递归的方式效率高
 * 
*/

class Solution
{
public:
    ListNode *swapPairs(ListNode *head)
    {
        while (head == NULL || head->next == NULL)
        {
            return head;
        }

        // 前序节点,用于保持连接
        ListNode *preNode = new ListNode(-1);
        // 用于返回结果
        ListNode *res = preNode;
        while (head != NULL && head->next != NULL)
        {
            // 比较重要的一句, 相当于 res->next = head->next, 保证res返回的结果
            preNode->next = head->next;
            // head next指向第三个节点
            head->next = head->next->next;
            // 第二个节点 的next指向 第一个节点
            preNode->next->next = head;
            // prenode-2-1(head)-3-4-5
            // 注意这里head的位置 已经变为 双节点的后节点
            // 更新preNode为 head
            preNode = preNode->next->next;
            // 更新head为 下一个双节点的前节点
            head = head->next;
        }
        return res->next;
    }
};

// 作者：reedfan
// 链接：https://leetcode-cn.com/problems/swap-nodes-in-pairs/solution/di-gui-he-fei-di-gui-liang-chong-jie-fa-java-by-re/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。