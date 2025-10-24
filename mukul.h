#ifndef MUKUL_H
#define MUKUL_H

#include "projectclasses.h"

class TreeHandler{
public:
    TreeNode* FormTree(vector<int>& inorder, vector<int>& preorder){
        if(inorder.size() == 0 || preorder.size() == 0) return NULL;
        int rootVal = preorder[0];
        TreeNode* root = new TreeNode(rootVal);
        int rootIndex = -1;
        for(int i = 0; i < inorder.size(); i++){
            if(inorder[i] == rootVal){
                rootIndex = i;
                break;
            }
        }
        vector<int> leftInorder(inorder.begin(), inorder.begin() + rootIndex);
        vector<int> rightInorder(inorder.begin() + rootIndex + 1, inorder.end());
        vector<int> leftPreorder(preorder.begin() + 1, preorder.begin() + 1 + leftInorder.size());
        vector<int> rightPreorder(preorder.begin() + 1 + leftInorder.size(), preorder.end());
        root->left = FormTree(leftInorder, leftPreorder);
        root->right = FormTree(rightInorder, rightPreorder);
        return root;
    }

    int TreeDepth(TreeNode* root){
        if(root == NULL) return 0;
        int leftDepth = TreeDepth(root->left);
        int rightDepth = TreeDepth(root->right);
        return max(leftDepth, rightDepth) + 1;
    }
    int TreeDiameter(TreeNode* root){
        if(root == NULL) return 0;
        int leftDepth = TreeDepth(root->left);
        int rightDepth = TreeDepth(root->right);
        int leftDiameter = TreeDiameter(root->left);
        int rightDiameter = TreeDiameter(root->right);
        return max(leftDepth + rightDepth, max(leftDiameter, rightDiameter));
    }
    int TreeLeftRadius(TreeNode* root){
        if(root == NULL) return 0;
        int leftRadius = TreeLeftRadius(root->left);
        return leftRadius + 1;
    }
    int TreeRightRadius(TreeNode* root){
        if(root == NULL) return 0;
        int rightRadius = TreeRightRadius(root->right);
        return rightRadius + 1;
    }

    void ExportToGraphviz(TreeNode* root, const string& filename = "binarytree.dot") {
        ofstream fout(filename);
        fout << "digraph BinaryTree {\n";
        fout << "    node [shape=circle, style=filled, fillcolor=lightblue, fontname=\"Arial\"];\n";
        fout << "    edge [color=gray50];\n";

        function<void(TreeNode*)> dfs = [&](TreeNode* node) {
            if (!node) return;
            fout << "    \"" << node << "\" [label=\"" << node->val << "\"];\n";
            if (node->left) {
                fout << "    \"" << node << "\" -> \"" << node->left << "\";\n";
                dfs(node->left);
            }
            if (node->right) {
                fout << "    \"" << node << "\" -> \"" << node->right << "\";\n";
                dfs(node->right);
            }
        };

        dfs(root);
        fout << "}\n";
        fout.close();
        cout << "DOT file generated: " << filename << endl;
    }
    
    void PrintTree(TreeNode* root) {
        ExportToGraphviz(root);
        system("dot -Tpng binarytree.dot -o binarytree.png");
        system("xdg-open binarytree.png");
    }
};

class BTreeHandler {
public:
    BTreeNode* root;

    void writeDot(const string& filename) {
        ofstream fout(filename);
        fout << "digraph BTree {\n";
        fout << "  node [shape=record];\n";

        int nullCount = 0;
        writeDotHelper(fout, root, nullCount);

        fout << "}\n";
        fout.close();
    }
  
    int writeDotHelper(ofstream& fout, BTreeNode* node, int& nullCount) {
        if (!node) return -1;

        // Node label
        stringstream label;
        label << "<f0>";
        for (int i = 0; i < node->num_keys; i++) {
            label << " | " << node->keys[i] << " | <f" << i+1 << ">";
        }

        int nodeId = reinterpret_cast<uintptr_t>(node); // unique id using pointer
        fout << "  \"" << nodeId << "\" [label=\"" << label.str() << "\"];\n";

        // Children edges
        if (!node->is_leaf) {
            for (int i = 0; i <= node->num_keys; i++) {
                if (node->children[i]) {
                    int childId = writeDotHelper(fout, node->children[i], nullCount);
                    fout << "  \"" << nodeId << "\":f" << i << " -> \"" << childId << "\";\n";
                } else {
                    int nullId = nullCount++;
                    fout << "  null" << nullId << " [shape=point];\n";
                    fout << "  \"" << nodeId << "\":f" << i << " -> null" << nullId << ";\n";
                }
            }
        }

        return nodeId;
    }

    void traverse(BTreeNode* node) {
        if (!node) return;
        int i;
        for (i = 0; i < node->num_keys; i++) {
            if (!node->is_leaf)
                traverse(node->children[i]);
            cout << node->keys[i] << " ";
        }
        if (!node->is_leaf)
            traverse(node->children[i]);
    }

    void insertNonFull(BTreeNode* node, int key) {
        int i = node->num_keys - 1;

        if (node->is_leaf) {
            // Shift keys to make space
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
            node->num_keys++;
        } else {
            while (i >= 0 && key < node->keys[i])
                i--;
            i++;
            if (node->children[i]->num_keys == M - 1) {
                splitChild(node, i, node->children[i]);
                if (key > node->keys[i])
                    i++;
            }
            insertNonFull(node->children[i], key);
        }
    }

    void splitChild(BTreeNode* parent, int index, BTreeNode* child) {
        BTreeNode* newChild = new BTreeNode(child->is_leaf);
        newChild->num_keys = M / 2 - 1;

        // Copy keys
        for (int j = 0; j < M / 2 - 1; j++)
            newChild->keys[j] = child->keys[j + M / 2];

        // Copy children if not leaf
        if (!child->is_leaf) {
            for (int j = 0; j < M / 2; j++)
                newChild->children[j] = child->children[j + M / 2];
        }

        child->num_keys = M / 2 - 1;

        // Shift parent's children to insert newChild
        for (int j = parent->num_keys; j >= index + 1; j--)
            parent->children[j + 1] = parent->children[j];
        parent->children[index + 1] = newChild;

        // Shift parent's keys
        for (int j = parent->num_keys - 1; j >= index; j--)
            parent->keys[j + 1] = parent->keys[j];

        parent->keys[index] = child->keys[M / 2 - 1];
        parent->num_keys++;
    }


    BTreeHandler() {
        root = new BTreeNode(true);
    }

    void insert(int key, int step = -1) {
        if (root->num_keys == M - 1) {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->children[0] = root;
            splitChild(newRoot, 0, root);
            int i = (newRoot->keys[0] < key) ? 1 : 0;
            insertNonFull(newRoot->children[i], key);
            root = newRoot;
        } else {
            insertNonFull(root, key);
        }
    }

    void traverse() {
        writeDot("BTree.dot");
        cout << "B-Tree image generated" << endl;
        system("dot -Tpng BTree.dot -o BTree.png");
        system("xdg-open BTree.png");
    }
};



#endif
