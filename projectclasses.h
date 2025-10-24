#ifndef PROJECTCLASSES_H
#define PROJECTCLASSES_H

#include <bits/stdc++.h>
#define M 5

using namespace std;

class node{
public:
    int val;
    node* next;
    node(int data){
        val = data;
        next = NULL;
    }
};

class TreeNode{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data){
        val = data;
        left = NULL;
        right = NULL;
    }
};

class BTreeNode {
public:
    int num_keys;
    int keys[M - 1];
    BTreeNode* children[M];
    bool is_leaf;
    BTreeNode(bool leaf) {
        is_leaf = leaf;
        num_keys = 0;
        for (int i = 0; i < M; i++)
            children[i] = nullptr;
    }
};

#endif
