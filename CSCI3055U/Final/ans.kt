// define a type to describe the tree nodes of a binary tree
// the type should have 1 generic parameter and multiple constructors
// cannot use var or mutable collections

data class Node<T>(val value: T, val left: Node<T>?, val right: Node<T>?){
    constructor(value: T) : this(value, null, null)
    constructor(value: T, left: Node<T>?) : this(value, left, null)
    constructor(value: T, right: Node<T>?) : this(value, null, right)
}

// use the kotlin type to describe the following tree
//     10
//    / \
//   7   15
//  / \ 
// 3  9 

val tree = Node(10, Node(7, Node(3, null, null), Node(9, null, null)), Node(15, null, null))

// implement binary search tree search
// return true if the value is in the tree, false otherwise
// the function must be type safe
fun <T> search(tree: Node<T>, value: T): Boolean where T : Comparable<T> {
    if (tree.value == value) return true
    if (tree.left != null && value < tree.value) return search(tree.left, value)
    if (tree.right != null && value > tree.value) return search(tree.right, value)
    return false
}

println(search(tree, 7)) // true