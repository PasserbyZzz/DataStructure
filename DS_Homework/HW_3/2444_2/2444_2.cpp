#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 使用扩展前序遍历构造二叉树
TreeNode* buildTree(const vector<string>& preorder, int& index) {
    // 如果索引超出范围或当前值为 "NULL"，返回空节点
    if (index >= preorder.size() || preorder[index] == "NULL") {
        index++; // 跳过当前节点
        return nullptr;
    }

    // 创建当前节点
    TreeNode* root = new TreeNode(stoi(preorder[index]));
    index++; // 处理下一个节点

    // 构造左子树
    root->left = buildTree(preorder, index);

    // 构造右子树
    root->right = buildTree(preorder, index);

    return root;
}

// 前序打印树（验证树是否正确构造）
void printPreorder(TreeNode* root) {
    if (!root) {
        cout << "NULL ";
        return;
    }
    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

int main() {
    // 输入：扩展二叉树的前序遍历
    vector<string> preorder = {"1", "2", "NULL", "NULL", "3", "4", "NULL", "NULL", "5", "NULL", "NULL"};
    
    int index = 0; // 初始化索引
    TreeNode* root = buildTree(preorder, index);

    // 验证构造的二叉树
    cout << "构造的二叉树的前序遍历: ";
    printPreorder(root);
    cout << endl;

    return 0;
}

/*
//递归构造函数
TreeNode* buildTree(vector<int>& preorder, int& index)
{
// 边界条件:如果越界，返回 nullptr
if(index >= preorder.size())return nullptr;
//当前值
int val = preorder[index];index++;//递增索引
//如果值为 -1，表示虚拟节点
if(val == -1)return nullptr;
// 创建当前节点
TreeNode* node:= new TreeNode(val);
//递归构造左子树
node->left = buildTree(preorder, index);
// 递归构造右子树
node->right = buildTree(preorder, index),
return node;
}
*/