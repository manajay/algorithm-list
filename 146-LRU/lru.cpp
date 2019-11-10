#include <iostream>
#include <unordered_map>
#include <list>
#include <utility> // pair
using namespace std;

// hash 
// 双向链表, 方便快速删除
// https://www.cnblogs.com/smiler/p/4457622.html

/*
* hash 记录数据, 和访问顺序没有关系, 做到访问 O(1)
* 
**/
class LRUCache {
private:
    // mark max length
    int capacity;
    // 双向链表存储 key,value
    list<pair<int, int> > linklist;
    // map 存储 key , node
    unordered_map<int,list<pair<int, int> >::iterator>map;

public:
    LRUCache(int capacity) {
        this -> capacity = capacity;
    }
    
    int get(int key) {
        // key in map
        auto it = map.find(key);
        if (it == map.end()){return -1;}
        //存在
        pair<int, int>kv = *map[key];
        // 更新链表 至 head, 从原来的位置删除,然后再插入到最前面
        linklist.erase(map[key]);
        linklist.push_front(kv);
        // 更新 map -> key,iterator
        map[key] = linklist.begin();
        return kv.second;
    }
    
    void put(int key, int value) {
        // key in map
        auto it = map.find(key);
        if (it != map.end()){
            // 更新到head
            linklist.erase(map[key]);
            linklist.push_front(make_pair(key,value));
            map[key] = linklist.begin();
            return;
        }
        // 检查容量
        if (linklist.size() == capacity){
            auto last = linklist.back();
            int lastKey = last.first;
            map.erase(lastKey);
            linklist.pop_back();
        }

        linklist.push_front(make_pair(key,value));
        map[key] = linklist.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main () {
    LRUCache* obj = new LRUCache(4);
    obj ->put(1,49);
    obj ->put(3,41);
    obj ->put(5,43);
    obj ->put(21,54);

    int val1 = obj->get(3);
    cout << "key 3 -> val: " << val1 << endl;
    int val2 = obj->get(32);
    cout << "key 32 -> val: " << val2 << endl;

    return 0;
}