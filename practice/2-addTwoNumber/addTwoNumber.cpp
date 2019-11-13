/**
 * 
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-two-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
*/

#include <iostream>
#include <vector>
#include <string>
#include <iosfwd>
#include <sstream>
using namespace std;

 // Definition for singly-linked list.
struct ListNode {
     int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};
 
/**
 * 1. 先看题, 多读几遍, 看准条件
 * 2. 先写测试用例, 判断有几种情况
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 从低到高位加和
        // 临时变量记录(商) 进位的数值 本位置保留 余数
        ListNode *ret = new ListNode(-1);;
        ListNode *current = ret;
        int nextV = 0;
        int currentV = 0;
        while (l1 != NULL || l2 != NULL || nextV > 0){
            if (l1 != NULL && l2 != NULL){ // 都不为空
                currentV = nextV + l1->val + l2->val;

                l1 = l1->next;
                l2 = l2->next;
            } else if (l1 != NULL) {// l1 不为空 l2 为空
                currentV = nextV + l1->val;
                
                l1 = l1->next;
            } else if (l2 != NULL) {// l1为空 l2不为空
                currentV = nextV + l2->val;
                l2 = l2->next;
            } else {
                currentV = nextV;
                nextV = 0;
            }
            // 注意这里 进位, 可以使用 bool flag 表示
            nextV = currentV >= 10 ? 1 : 0;
            currentV = currentV % 10;
            
            current -> next = new ListNode(currentV);
            current = current->next;
        }
        
        return ret -> next; 
    }
};


void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

ListNode* stringToListNode(string input) {
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for (int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

string listNodeToString(ListNode* node) {
    if (node == nullptr) {
        return "[]";
    }

    string result;
    while (node) {
        result += to_string(node->val) + ", ";
        node = node->next;
    }
    return "[" + result.substr(0, result.length() - 2) + "]";
}

int main () {
    /**
     * 测试用例
     * [2,4,3]
     * [5,6,4]
     * 
    */
    string line;
    while (getline(cin,line)) {
        ListNode *node1 = stringToListNode(line);
        getline(cin,line);
        ListNode *node2 = stringToListNode(line);
        ListNode *ret = Solution().addTwoNumbers(node1,node2);
        cout << "ret: " << listNodeToString(ret) << endl;
    }
    return 0;
}