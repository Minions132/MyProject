#pragma once
#include <iostream>
#include <vector>

struct TreeNode{
    std::string code;
    char data;
    int weight;
    int level;
    TreeNode* lchild;
    TreeNode* rchild;
    TreeNode();
};

class HuffmanTree{
private:
    TreeNode* root;
    bool tree_generated;
public:
    HuffmanTree();
    ~HuffmanTree();
    HuffmanTree(const HuffmanTree& t);
    TreeNode* merge_Node(TreeNode* node_1, TreeNode* node_2);
    void Add_TreeNode_Tovector(std::vector<TreeNode*>& v, char c, int weight);
    TreeNode* Create_Node(std::vector<TreeNode*>& node);
    void BuildTree_cin(std::string s);
    void BuildTree_fin(std::string path);
    void stockpile();
    void Coding(std::string path);
    void Decoding(std::string path);
    void calculate_level();
    void Vertical_output();
    void Count_Code();
    bool Get_state() const;
};

