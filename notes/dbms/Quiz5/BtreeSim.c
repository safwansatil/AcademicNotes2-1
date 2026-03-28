#include <stdio.h>
#include <stdlib.h>

// B-Tree Node structure
typedef struct Node {
    int *keys;
    struct Node **children;
    int num_keys;
    int is_leaf;
} Node;

// Global variable for B-Tree order
int m;

// Function to create a new node
Node* createNode(int is_leaf) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->is_leaf = is_leaf;
    // B-tree of order m has max m-1 keys and m children
    node->keys = (int*)malloc(sizeof(int) * m); // Extra space for temporary overflow if needed
    node->children = (Node**)malloc(sizeof(Node*) * (m + 1));
    node->num_keys = 0;
    for (int i = 0; i <= m; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Function to print paths from root to leaf
void printPaths(Node* node, char* path, int depth) {
    if (node == NULL) return;

    // Build the string representation of the current node [k1|k2|...]
    char current_node_str[1024];
    int pos = 0;
    pos += sprintf(current_node_str + pos, "[");
    for (int i = 0; i < node->num_keys; i++) {
        pos += sprintf(current_node_str + pos, "%d", node->keys[i]);
        if (i < node->num_keys - 1) {
            pos += sprintf(current_node_str + pos, "|");
        }
    }
    pos += sprintf(current_node_str + pos, "]");

    // Append to path
    char new_path[4096];
    if (depth == 0) {
        sprintf(new_path, "%s", current_node_str);
    } else {
        sprintf(new_path, "%s -> %s", path, current_node_str);
    }

    if (node->is_leaf) {
        printf("%s\n", new_path);
    } else {
        for (int i = 0; i <= node->num_keys; i++) {
            if (node->children[i] != NULL) {
                printPaths(node->children[i], new_path, depth + 1);
            }
        }
    }
}

// Function to split a child of parent
// i is the index of child in parent->children[]
void splitChild(Node* parent, int i) {
    Node* child = parent->children[i];
    int mid_idx = (m - 1) / 2;
    int mid_key = child->keys[mid_idx];

    Node* newNode = createNode(child->is_leaf);
    newNode->num_keys = (child->num_keys) - mid_idx - 1;

    // Transfer the upper half of keys to newNode
    for (int j = 0; j < newNode->num_keys; j++) {
        newNode->keys[j] = child->keys[j + mid_idx + 1];
    }

    // Transfer children if not leaf
    if (!child->is_leaf) {
        for (int j = 0; j <= newNode->num_keys; j++) {
            newNode->children[j] = child->children[j + mid_idx + 1];
        }
    }

    child->num_keys = mid_idx;

    // Shift parent's children to make room for newNode
    for (int j = parent->num_keys; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = newNode;

    // Shift parent's keys to make room for mid_key
    for (int j = parent->num_keys - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = mid_key;
    parent->num_keys++;
}

// Function to insert into a non-full node (where non-full means num_keys < m)
void insertNonFull(Node* node, int key) {
    int i = node->num_keys - 1;

    if (node->is_leaf) {
        // Find position and shift keys
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        // Find child to recurse into
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;
        // Insert into child
        insertNonFull(node->children[i], key);
        
        // If child now has m keys, split it
        if (node->children[i]->num_keys == m) {
            splitChild(node, i);
        }
    }
}

// Main insert function
Node* insert(Node* root, int key) {
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = key;
        root->num_keys = 1;
        return root;
    }

    insertNonFull(root, key);

    // If root overflows, split it
    if (root->num_keys == m) {
        Node* s = createNode(0);
        s->children[0] = root;
        splitChild(s, 0);
        return s;
    }
    
    return root;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *values = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    if (scanf("%d", &m) != 1) return 0;

    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
        printf("Step %d: Insert %d\n", i + 1, values[i]);
        printPaths(root, "", 0);
        printf("\n");
    }

    return 0;
}