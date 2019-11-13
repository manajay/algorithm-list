//
//  BinarySearchTree.swift
//  ios-interview-algorithm
//
//  Created by ljtwan on 2019/6/19.
//  Copyright © 2019 JAY. All rights reserved.
//

import Foundation

class Node<T:Comparable> {
    var value:T
    var visited:Bool = false
    var leftNode:Node<T>?
    var rightNode:Node<T>?
    
    init(_ value:T) {
        self.value = value
    }

}


/// 二叉树 , 是否为空, 数量, 深度 , 高度 , 是否是二叉查找树 (左子节点小于父节点, 右子节点大于父节点)
class BinarySearchTree<T:Comparable> {
    var nodes = [Node<T>]()
    
    var isEmpty:Bool {
        return nodes.isEmpty
    }
    
    var count:Int {
        return nodes.count
    }
    
    var peek:Node<T>? {
        return nodes.last
    }
    
    init(_ values:[Node<T>] = [Node<T>]()) {
        self.nodes = values
        // 排序
    }
    
    
    /// 检查是否是 二叉查找树
    /// 规律 根节点的左子树中所有节点都小于根节点, 根节点的右子树中所有节点都大于根节点
    /// - Parameter rootNode: <#rootNode description#>
    /// - Returns: <#return value description#>
    public func isValidBST(_ rootNode:Node<T>? ) -> Bool {
        return checkNodes(node: rootNode, maxValue: nil, minValue: nil)
    }
    
    private func checkNodes(node: Node<T>?, maxValue:T?, minValue:T?) -> Bool {
        
        // 根节点
        guard let node = node else {
            return true
        }
        
        // 所有右子节点的值必须大于根节点
        if let minValue = minValue , node.value <= minValue {
            return false
        }
        
        // 所有左子节点的值必须小于根节点
        if let maxValue = maxValue, node.value >= maxValue {
            return false
        }

        return checkNodes(node: node.leftNode, maxValue: minValue, minValue: node.value) && checkNodes(node: node.rightNode, maxValue: node.value, minValue: maxValue)
    }
    
    // Traversal 遍历 前序 中序 后序, 层级(BFS)
    
    // 前序遍历, 先打印父节点, 再打印左子树, 最后打印右子树
    func preoderTraversal (_ root:Node<T>?) -> [T]{
        // 非递归的方法, 使用栈
        var res = [T]()
        var stack = [Node<T>]()
        var node = root
        while !stack.isEmpty || node != nil {
            if node != nil {
                res.append(node!.value)
                stack.append(node!)
                node = node?.leftNode
            } else {
                node = stack.removeLast().rightNode
            }
        }
        
        return res
    }
    
    // 中序遍历 , 左 -> 中 -> 右  中序遍历二叉查找树输出有顺序的
    func inOrderTraversal(_ root:Node<T>?) -> [T] {
        // 非递归的方法, 使用栈
        var res = [T]()
        var stack = [Node<T>]()
        var node = root
        while !stack.isEmpty || node != nil {
            // 先走左节点
            while node != nil {
                stack.append(node!)
                node = node?.leftNode
            }
            
            if !stack.isEmpty {
                node = stack.removeLast()
                res.append(node!.value)
                node =  node?.rightNode
            }
        }
        
        return res
    }
    
    
    
    
//    public func traverseInOrder(process: (T) -> Void) {
//        left?.traverseInOrder(process: process)
//        process(value)
//        right?.traverseInOrder(process: process)
//    }
//
//    public func traversePreOrder(process: (T) -> Void) {
//        process(value)
//        left?.traversePreOrder(process: process)
//        right?.traversePreOrder(process: process)
//    }
//
//    public func traversePostOrder(process: (T) -> Void) {
//        left?.traversePostOrder(process: process)
//        right?.traversePostOrder(process: process)
//        process(value)
//    }
    
    
    
}

extension BinarySearchTree {
    // 后序遍历, 先左子树, 再右子树, 再根节点
    /// 后序遍历的难点在于：需要判断上次访问的节点是位于左子树，还是右子树
    func postOrderTranserval (_ root:Node<T>? ) -> [T] {
        // 非递归的方法, 使用栈
        var res = [T]()
        var stack = [Node<T>]()
        var node = root
        
        while !stack.isEmpty || node != nil {
            
            // 将左子树下沉到底部
            while node != nil {
                stack.append(node!)
                node = node!.leftNode
            }
            
            node = stack.removeLast()
            
            let rightNode = node?.rightNode;
            // 根节点遍历 , 前提是没有右子树,或者右子树已经被添加了
            if rightNode == nil || rightNode!.visited {
                res.append(node!.value)
                node?.visited = true
            } else {
                // 右子树没有添加
                node = rightNode// 子节点
            }
        }
        
        return res
    }
}
