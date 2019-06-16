//
//  main.cpp
//  leetcode0001-Two-Sum
//
//  Created by ljtwan on 2019/1/18.
//  Copyright © 2019 JAY. All rights reserved.
//  g++ main.cpp -std=c++11 -o main; 执行main

#include <iostream>
#include <vector>

// 为了区分多个相同变量或函数等符号, OC 就不存在该定义, 所以规范命名的时候经常要在变量或函数中增加前缀
using namespace std;

/**
 Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 
 You may assume that each input would have exactly one solution, and you may not use the same element twice.
 */

class Solution {
public:
    
    /**
     暴力方式 Brute Force
     时间复杂度: O(n^2) for 循环内嵌 for 循环
     空间复杂度: O(n) 一共有 n 个元素分配空间

     @param nums 输入
     @param target 目标
     @return 输出
     */
    vector<int> twoSumBF(vector<int>& nums, int target) {
        for (int i = 0 ; i < nums.size() ; i ++) {
            for (int j = i + 1 ; j < nums.size() ; j ++) {
                if (nums[i] + nums[i] == target) {
                    int res[] = {i, j};
                    return vector<int>(res, res + 2);
                }
            }
        }
        throw invalid_argument("无效数组输入");
    }
    
    vector<int> twoSumHashTableOne(vector<int>& nums, int target) {
        
        return vector<int>();
    }
    
    vector<int> twoSumHashTableTwo(vector<int>& nums, int target) {
        
        return vector<int>();
    }
};

void  printVec(const vector<int> &num_vec){
    for (int num : num_vec) {
        cout << num << " ";
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    const int numbers[] = {3,3};
    int target = 6;
    
    vector<int> nums_vec(numbers, numbers + sizeof(numbers)/ sizeof(int));
    vector<int> resultBF = Solution().twoSumBF(nums_vec, target);
    printVec(resultBF);
    
    return 0;
}
