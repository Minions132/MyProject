#include "HuffmanTree.h"
#include <vector>
#include <utility>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>

TreeNode::TreeNode(){
    lchild = nullptr;
    rchild = nullptr;
    weight = 0;
    data = '#';
    code = "";
    level = 0;
}

HuffmanTree::HuffmanTree(){
    root = nullptr;
    tree_generated = false;
}

HuffmanTree::~HuffmanTree(){
    if(root == nullptr) return;
    std::queue<TreeNode*> q;
    TreeNode* p;
    q.push(root);
    while(!q.empty()){
        p = q.front();
        if(q.front()->lchild != nullptr){
            q.push(q.front()->lchild);
        }
        if(q.front()->rchild != nullptr){
            q.push(q.front()->rchild);
        }
        delete p;
        q.pop();
    }
}

HuffmanTree::HuffmanTree(const HuffmanTree &t){
    if(t.root == nullptr){
        root = t.root;
        tree_generated = false;
    }
    tree_generated = true;
    std::queue<TreeNode*> q;
    std::queue<TreeNode*> p;
    q.push(t.root);
    p.push(root);
    p.front() = new TreeNode();
    p.front()->code = q.front()->code;
    p.front()->data = q.front()->data;
    p.front()->level = q.front()->level;
    p.front()->weight = q.front()->weight;
    while(!q.empty()){
        if(q.front()->lchild){
            q.push(q.front()->lchild);
            p.front()->lchild = new TreeNode();
            p.front()->lchild->code = q.front()->lchild->code;
            p.front()->lchild->data = q.front()->lchild->data;
            p.front()->lchild->level = q.front()->lchild->level;
            p.front()->lchild->weight = q.front()->lchild->weight;
            p.push(p.front()->lchild);
        }
        if(q.front()->rchild){
            q.push(q.front()->rchild);
            p.front()->rchild = new TreeNode();
            p.front()->rchild->code = q.front()->rchild->code;
            p.front()->rchild->data = q.front()->rchild->data;
            p.front()->rchild->level = q.front()->rchild->level;
            p.front()->rchild->weight = q.front()->rchild->weight;
            p.push(p.front()->rchild);
        }
        q.pop();
        p.pop();
    }
}

TreeNode *HuffmanTree::merge_Node(TreeNode *node_1, TreeNode *node_2)
{
    TreeNode* temp = new TreeNode();
    temp->lchild = node_1;
    temp->rchild = node_2;
    temp->weight = node_1->weight + node_2->weight;
    return temp;
}

void HuffmanTree::Add_TreeNode_Tovector(std::vector<TreeNode*>& v, char c, int weight){
    TreeNode* temp = new TreeNode();
    temp->data = c;
    temp->weight = weight;
    v.push_back(temp);
    return;
}

TreeNode* HuffmanTree::Create_Node(std::vector<TreeNode*>& node){
    int index_min = 0;
    for(size_t i = 0; i < node.size(); i++){
        if(node[index_min]->weight > node[i]->weight){
            index_min = i;
        }
    }
    TreeNode* t1 = node[index_min];
    node.erase(node.begin() + index_min);
    index_min = 0;
    for(size_t i = 0; i < node.size(); i++){
        if(node[index_min]->weight > node[i]->weight){
            index_min = i;
        }
    }
    TreeNode* t2 = node[index_min];
    node.erase(node.begin() + index_min);
    TreeNode* t = merge_Node(t1, t2);
    return t;
}

void HuffmanTree::BuildTree_cin(std::string s){
    int n;
    n = s[0] - 48;
    int index = 2;
    int delta = 2;
    std::vector<TreeNode*> v;
    for(int i = 0; i < n; i++){
        std::string k = s.substr(index, index + delta);
        char c = k[0];
        int weight = k[2] - 48;
        Add_TreeNode_Tovector(v, c, weight);
        index += 4;
    }
    while(v.size() != 1){
        TreeNode* t = Create_Node(v);
        v.push_back(t);
    }
    root = v.front();
    v.clear();
    tree_generated = true;
}

void HuffmanTree::BuildTree_fin(std::string path){
    int n;
    std::ifstream fin(path);
    fin >> n;
    std::string line;
    getline(fin, line);
    std::istringstream sin(line);
    std::vector<TreeNode*> v;
    for(int i = 0; i < n; i++){
        getline(fin, line);
        sin.str("");
        sin.clear();
        sin.str(line);
        char c;
        int weight;
        sin >> c >> weight;
        Add_TreeNode_Tovector(v, c, weight);
    }
    while(v.size() != 1){
        TreeNode* t = Create_Node(v);
        v.push_back(t);
    }
    root = v.front();
    v.clear();
    tree_generated = true;
}

void HuffmanTree::stockpile(){
    if(root == nullptr) return;
    std::vector<TreeNode*> tree;
    std::vector<std::pair<char, int>> output;
    std::queue<TreeNode*> q;
    q.push(root);
    int i = 0;
    while(!q.empty()){
        tree.push_back(q.front());
        if(q.front()->lchild != nullptr){
            q.push(q.front()->lchild);
        }
        if(q.front()->rchild != nullptr){
            q.push(q.front()->rchild);
        }
        q.pop();
    }
    output.push_back(std::make_pair(root->data, -1));
    int j = 1;
    while(j != tree.size()){
        if(tree[j] == tree[i]->lchild){
            output.push_back(std::make_pair(tree[j]->data, i));
            j++;
        }
        else if(tree[j] == tree[i]->rchild){
            output.push_back(std::make_pair(tree[j]->data, i));
            j++;
            i++;
        }
        else i++;
    }
    std::ofstream fout("HuffmanTree.txt");
    for(size_t i = 0; i < output.size(); i++){
        fout << i << " " << output[i].first << " " << output[i].second << std::endl;
    }
}


void HuffmanTree::Coding(std::string path){
    if(root == nullptr) return;
    std::ifstream fin(path);
    std::ofstream fout("HuffmanCode.txt");
    std::queue<TreeNode*> q;
    this->Count_Code();
    std::vector<std::pair<char, std::string>> v;
    q.push(root);
    while(!q.empty()){
        if(q.front()->data != '#'){
            v.push_back(make_pair(q.front()->data, q.front()->code));
        }
        if(q.front()->lchild != nullptr){
            q.push(q.front()->lchild);
        }
        if(q.front()->rchild != nullptr){
            q.push(q.front()->rchild);
        }
        q.pop();
    }
    std::string line;
    while(getline(fin, line)){
        for(int i = 0; i < line.size(); i++){
            for(size_t j = 0; j < v.size(); j++){
                if(line[i] == v[j].first){
                    fout << v[j].second;
                }
            }
        }
    }
}

void HuffmanTree::Decoding(std::string path){
    if(root == nullptr) return;
    std::ifstream fin(path);
    std::ofstream fout("HuffmanText.txt");
    std::string line;
    TreeNode* p = root;
    while(getline(fin, line)){
        for(int i = 0; i < line.size(); i++){
            if(line[i] == '1') p = p->rchild;
            else p = p->lchild;
            if(p->lchild == nullptr && p->rchild == nullptr){
                fout << p->data;
                p = root;
            }
        }
    }
}

void HuffmanTree::calculate_level(){
    if(root == nullptr) return;
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        if(q.front()->lchild != nullptr){
            q.push(q.front()->lchild);
            q.front()->lchild->level = q.front()->level - 1;
        }
        if(q.front()->rchild != nullptr){
            q.push(q.front()->rchild);
            q.front()->rchild->level = q.front()->level + 1;
        }
        q.pop();
    }
}

void HuffmanTree::Vertical_output(){
    if(root == nullptr) return;
    this->Count_Code();
    this->calculate_level();
    std::vector<TreeNode*> v;
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        v.push_back(q.front());
        if(q.front()->lchild != nullptr){
            q.push(q.front()->lchild);
        }
        if(q.front()->rchild != nullptr){
            q.push(q.front()->rchild);
        }
        q.pop();
    }
    for(size_t i = 0; i < v.size(); i++){
        for(size_t j = 0; j < v.size() - 1 - i; j++){
            if(v[j]->level > v[j + 1]->level){
                int temp = v[j]->level;
                v[j]->level = v[j + 1]->level;
                v[j + 1]->level = temp;
            }
        }
    }
    std::ofstream fout("out.txt");
    for(size_t i = 0; i < v.size(); i++){
        if(v[i]->data != '#'){
            fout << v[i]->data << " " << v[i]->code << std::endl;
        }
    }
}

void HuffmanTree::Count_Code(){
    if(root == nullptr) return;
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        if(q.front()->lchild != nullptr){
            q.push(q.front()->lchild);
            q.front()->lchild->code = q.front()->code + "0";
        }
        if(q.front()->rchild != nullptr){
            q.push(q.front()->rchild);
            q.front()->rchild->code = q.front()->code + "1";
        }
        q.pop();
    }
}

bool HuffmanTree::Get_state() const{
    return tree_generated;
}
