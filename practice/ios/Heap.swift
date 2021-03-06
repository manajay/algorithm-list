//
//  Heap.swift
//  ios-interview-algorithm
//
//  Created by ljtwan on 2019/6/17.
//  Copyright © 2019 JAY. All rights reserved.
//

import Foundation

public struct Heap <T> {
    
    // 所有节点
    var nodes = [T]()
    
    
    /// 排序函数, 升序还是降序
    private var orderCriteria: (T,T) -> Bool
    
    public var count:Int {
        return nodes.count;
    }
    
    public var isEmpty:Bool {
        return nodes.isEmpty
    }
    
    public var peek:T? {
        return nodes.first
    }
    
    public init(_ array:[T], sort: @escaping (T,T) -> Bool ) {
        self.orderCriteria = sort
        configHeap(from: array)
    }
    
    private mutating func configHeap(from array:[T]){
        nodes = array
        // stride 中间索引, 生成全闭区间数组索引
        // 从 二叉树的 (nodes.count/2 - 1) 一边的最后一个节点开始
        for i in stride(from: (nodes.count/2 - 1), through: 0, by: -1) {
            // 堆化
            shiftDown(i)
        }
    }
    
    //    一般都用数组来表示堆，i结点的父结点下标就为(i – 1) / 2。它的左右子结点下标分别为2 * i + 1和2 * i + 2。如第0个结点左右子结点下标分别为1和2。
    
    internal func leftChildIndex(_ index:Int) -> Int {
        return 2 * index + 1;
    }
    
    internal func rightChildIndex(_ index:Int) -> Int {
        return 2 * index + 2;
    }
    
    
    /// 获取指定元素的父节点索引
    /// 左右子节点 都适用
    /// - Parameter index: 指定节点
    /// - Returns: 父节点索引
    internal func parentIndex(_ index:Int) -> Int {
        return (index - 1) / 2;
    }
    
    /// 堆化 从下往上
    ///
    /// - Parameter index: <#index description#>
    internal mutating func shiftDown(_ index:Int) {
        shiftDown(from: index, util: nodes.count)
    }
    
    /// 每次最多只交换一个节点, 递归调用 shiftDown 时,会略过其左子节点或者右子节点
    internal mutating func shiftDown(from index:Int ,util endIndex:Int ) {
        // 获取左右节点
        let leftChildIndex = self.leftChildIndex(index)
        let rightChildIndex = self.rightChildIndex(index)
        
        // 判断是升序还是降序
        var first = index
        
        // 子节点的键值或者索引总是大于或者小于其父节点
        if leftChildIndex < endIndex && orderCriteria(nodes[leftChildIndex],nodes[first]) {
            first = leftChildIndex
        }
        
        // 子节点的键值或者索引总是大于或者小于其父节点
        if rightChildIndex < endIndex && orderCriteria(nodes[rightChildIndex],nodes[first]) {
            first = rightChildIndex
        }
        
        // 符合直接返回
        if first == index { return }
        
        // 交换
        nodes.swapAt(first, index)
        // 再次从 不符合的子节点索引处
        shiftDown(from: first, util: endIndex)
    }
    
}

extension Heap {
    public mutating func sort() -> [T] {
        for i in stride(from: nodes.count - 1, through: 0, by: -1) {
            print("i: \(i) before: \(nodes)")
            nodes.swapAt(0, i)
            print("i: \(i) after swap: \(nodes)")
            shiftDown(from: 0, util: i)
            print("i: \(i) after shiftDown: \(nodes)")
        }
        return nodes
    }
    
    public mutating func heapSort (_ array:[T], _ sort: @escaping (T,T) -> Bool) -> [T] {
        let reverseOrder = {i1,i2 in sort(i2,i1)}
        var heap = Heap(array, sort: reverseOrder)
        return heap.sort()
    }
}
