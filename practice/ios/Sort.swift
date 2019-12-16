//
//  Sort.swift
//  ios-interview-algorithm
//
//  Created by ljtwan on 2019/6/16.
//  Copyright © 2019 JAY. All rights reserved.
//

import Foundation

struct Sort {
    
    @discardableResult static func chooseSort (_ source:[Int]) -> [Int] {
        guard source.count > 1 else {
            return source
        }
        print("chooseSort input: \(source)")
        
        var m = source;
        
        // 遍历一层
        for i in 0 ..<  m.count {
            // 比较第二层
            let from = i + 1
            for j in from ..< m.count {
                if (m[i] > m[j]) {
                    m.swapAt(i, j)
                }
            }
        }
        print(" chooseSort output: \(m)")
        return m
    }
    
    @discardableResult static func bubbleSort(_ source:[Int]) -> [Int] {
        guard source.count > 1 else {
            return source
        }
        print("bubbleSort input: \(source)")
        var m = source;
        
        // 从倒数第几位算起
        for i in 0 ..< m.count {
            // 排除倒数的 第 i 位 的左侧开始 再次排序
            // 每次循环将最大的放在最右侧, 稳定排序
            for j in 0 ..< (m.count - i - 1) {
                if (m[j] > m [j+1]) {
                    m.swapAt(j, j+1)
                }
            }
        }
        
        print(" bubbleSort output: \(m)")
        return m
    }
    
    @discardableResult static func insertSort(_ source:[Int]) -> [Int] {
        guard source.count > 1 else {
            return source
        }
        print("insertSort input: \(source)")
        var m = source
        
        for i in 1 ..< m.count {
            for j in 0 ..< i {
                // 如果 i 比 j 小就插入到前面
                if (m[i] < m[j]) {
                    m.insert(m[i], at: j)
                    // 长度变了
                    m.remove(at: i + 1)
                }
            }
        }
        
        print(" insertSort output: \(m)")
        return m
    }
    
    
    @discardableResult static func mergeSort(_ source:[Int]) -> [Int] {
        print("mergeSort input: \(source)")
        guard source.count > 1 else {
            return source
        }
        
        var m = source
        // 先分开
        let middle = m.count / 2 - 1
        let a = Array(m[0...middle])
        let b = Array(m[(middle + 1)..<m.count])
//        print("a: \(a) b: \(b)")
        
        let sortedA = mergeSort(a);
        let sortedB = mergeSort(b);
//        print("sortedA: \(sortedA) sortedB: \(sortedB)")

        let sorted = mertSortedPart(sortedA, sortedB)
        print(" mergeSort output: \(sorted)")
        return sorted;
    }
    
    static private func mertSortedPart(_ inputA:[Int],_ inputB:[Int]) -> [Int] {
        var sortedA = inputA
        var sortedB = inputB

        var fromA = 0
        while !sortedB.isEmpty {
            for j in fromA..<sortedA.count {
                // 比大小, 或者 j 到尾部了
                if (sortedB[0] < sortedA[j]) {
                    sortedA.insert(sortedB[0], at: j)
                    sortedB.remove(at: 0)
                }
                fromA = j+1
            }
            
            // 终止条件
            if (sortedA.count == 0) {
                sortedA = sortedB
                break;
            }
            
            // 终止条件
            if (sortedB.count == 0) {
                break;
            }
            
            // 终止条件
            if (sortedB[0] > sortedA.last!) {
                sortedA = sortedA + sortedB
                break
            }
        }
        return sortedA;
    }
    
    
    @discardableResult static func quickSort(_ source:[Int]) -> [Int] {
        print("quickSort input: \(source)")
        let sorted = quicksort(source)
        print(" quickSort output: \(sorted)")
        return []
    }
    
    // https://github.com/raywenderlich/swift-algorithm-club/tree/master/Quicksort
    static func quicksort<T: Comparable>(_ a: [T]) -> [T] {
        guard a.count > 1 else { return a }
        
        let pivot = a[a.count/2]
        let less = a.filter { $0 < pivot }
        let equal = a.filter { $0 == pivot }
        let greater = a.filter { $0 > pivot }
        
        return quicksort(less) + equal + quicksort(greater)
    }

    /*
    * 分割 , 返回 pivot 点
    */
    static func partitionLomuto<T:Comparable>(_ a:[T], left: Int , right: Int) -> Int {
        let pivot = getPivot(_ a[T]);
        let pivot = a[high]
        var i = low
        for j in low..<high {
            if a[j] <= pivot {
            (a[i], a[j]) = (a[j], a[i])
            i += 1
            }
        }

        (a[i], a[high]) = (a[high], a[i])
        return min + 1
    }

    static func getPivot(_ arr:[T], left: Int , right: Int) -> Int {
        return right
    }
    

    func partitionHoare<T: Comparable>(_ a: inout [T], low: Int, high: Int) -> Int {
        let pivot = a[low]
        var i = low - 1
        var j = high + 1

        // 两层while
        while true {
            // 内层while
            repeat { j -= 1 } while a[j] > pivot
            repeat { i += 1 } while a[i] < pivot

            if i < j {
            a.swapAt(i, j)
            } else {
            return j
            }
        }
    }
    @discardableResult static func heapSort<T: Comparable> (_ a:[T]) -> [T] {
        guard a.count > 1 else {return a}
        print("heapSort input: \(a)")
        var heap = Heap(a, sort: >)
        let sorted = heap.sort();
        print(" heapSort output: \(sorted)")
        return sorted
    }
}
