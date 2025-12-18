## Tree
No Cycles, Only One or zero (root) parent for a single node.

- Parent Node: Any node that has one or more child nodes

- Child Node: A node with a predecessor (parent)

- Root Node: The topmost node with no parent

- Leaf Node: A node with no 

- Internal Node: A node with at least one child

- Sibling Nodes: Nodes that share the same parent

- Subtree: A tree formed by a node in a tree along with its descendants

- Level: Level represents the generation or distance from the root.

- Depth of a Node: The number of edges from the root to the node

- Degree of a Node: The number of children a node has

- Degree of a Tree: The maximum degree of any node in the tree

- Path: A sequence of consecutive edges from a source node to a destination node

- Path Length: The number of edges in a path

- Height of a Node: The number of nodes from that node to a leaf node

- Height of a Tree: The height of the root node, representing the longest path from the root to a leaf node

```cpp
// Height in recursive
int height(Node* node) {
    if (node == nullptr) 
        return -1;  // Or 0, depends on convention
    return 1 + max(height(node->left), height(node->right));
}
```

- Binary Tree: A tree where each node has at most two children

- Binary Search Tree (BST): For any node N, all values in the left subtree are less than N, and all values in the right subtree are greater than N. Optimized for search operations (O(log n) on average).

- Strictly Binary Tree: A binary tree where every node has either 0 or 2 children. Like Huffman Tree.

- Complete Binary Tree: A binary tree where all levels are fully filled except possibly the last level, which is filled from left to right.


- In an Extended Binary Tree (Strictly Binary), number of external nodes = number of internal nodes + 1

- For reconstructing a unique binary tree, we need inorder traversal + either preorder or postorder traversal.
 Because Inorder tells us the left and right subtree division, and preorder/postorder tells us the root node.

- Huffman trees are weighted and strictly binary trees used for optimal prefix coding in data compression.

- Huffman COnstruction: 
    ![huffman](./huffman%20algorithm.png)

- In huffman coding, more frequent characters are assigned shorter codes, while less frequent characters receive longer codes. This variable-length coding minimizes the overall size of the encoded data. 

- In huffman tree, no code is a prefix of any other code, ensuring unambiguous decoding.

- Huffman Decoding:
    ![huffman decoding](./huffman%20decoding.png)