#include <bits/stdc++.h> 
using namespace std ; 

struct TreeNode {
    int val ;
    TreeNode *left ;
    TreeNode *right ;
    TreeNode(int x) : val(x) , left(NULL) , right(NULL) {

    }
};

// 建立二叉树 , 注意 root 前面的 & 引用
void rebuild(TreeNode * &root , vector<string> arr , int &flag) {
    if(arr[flag] == "#"){
        return ; 
    }
    int num = stoi(arr[flag]) ; 
    root = new TreeNode(num) ; 
    rebuild(root->left , arr , ++flag ) ; 
    rebuild(root->right , arr , ++flag ) ; 
}

// 递归先序遍历
void preOrder1(TreeNode *root) {
    if(root) {
        cout<<root->val <<" "  ; 
        preOrder1(root->left) ; 
        preOrder1(root->right) ; 
    }
}

// 非递归先序遍历
void preOrder2(TreeNode *root) {

    stack<TreeNode *> sta ; 
    while(root || !sta.empty()) {
        if(root) {
            cout<<root->val<<" " ; 
            sta.push(root) ; 
            root = root->left ; 
        }else {
            root = sta.top() ; sta.pop() ;  
            root = root->right ; 
        }
    }

}

// 递归中序遍历
void inorder1(TreeNode *root) {
    if(root) {
        inorder1(root->left) ; 
        cout<<root->val<< " " ; 
        inorder1(root->right) ; 
    }
}

// 非递归中序遍历
void inorder2(TreeNode *root) {
    
    stack<TreeNode *> sta ; 
    while(root || !sta.empty()) {
        if(root) {
            sta.push(root) ;
            root = root->left ;  
        } else {
            root = sta.top() ; sta.pop() ; 
            cout<<root->val<<" " ; 
            root = root->right ; 
        }
    }
}

// 递归后序遍历
void postOrder1(TreeNode *root) {
    if(root) {
        postOrder1(root->left) ; 
        postOrder1(root->right) ; 
        cout<<root->val<<" " ; 
    }
}

// 非递归后序遍历
/*
一种策略：
要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，先将其入栈。
如果P不存在左孩子和右孩子，则可以直接访问它；
或者P存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
若非上述两种情况，则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。
*/
void postOrder2(TreeNode *root) {
    stack<TreeNode *> sta ; 
    TreeNode *cur , *pre ; 
    sta.push(root) ; 
    while(!sta.empty()) {
        cur = sta.top() ; 
        if( (cur->left == NULL && cur->right == NULL ) || 
            (pre != NULL && (cur->left == pre || cur->right == pre) ) ) {
                cout<<cur->val <<" " ; 
                pre = cur ;
                sta.pop() ;  
        }else {
            if(cur->right) {
                sta.push(cur->right) ; 
            }
            if(cur->left) {
                sta.push(cur->left) ; 
            }
        }
    }
}

// 层次遍历
void depthOrder(TreeNode *root) {
    queue<TreeNode *> q ; 
    q.push(root) ; 
    TreeNode *cur ; 
    while(!q.empty()) {
        cur = q.front() ; q.pop() ; 
        cout<<cur->val <<" " ; 
        if(cur->left) q.push(cur->left) ; 
        if(cur->right) q.push(cur->right) ; 
    }
}

// 统计结点个数
int countTreeNode(TreeNode *root) {
    if(root == NULL) {
        return 0 ; 
    }
    return countTreeNode(root->left) + countTreeNode(root->right) + 1 ; 
}

// 二叉树的深度
int depthTreeNode(TreeNode *root) {
    if(root == NULL) {
        return 0 ; 
    }
    int left = depthTreeNode(root->left) + 1 ; 
    int right =  depthTreeNode(root->right) + 1 ; 
    return max(left , right) ; 
}

int main() 
{
    vector<string> arr{"11","25","#","#","64","32","#","#","12","#","#"} ; 
    TreeNode *root = new TreeNode(0) ; 
    int flag = 0 ; 
    rebuild(root , arr , flag) ; 

    preOrder1(root) ; cout<<endl ; 
    preOrder2(root) ; cout<<endl ; 
    inorder1(root) ; cout<<endl ; 
    inorder2(root) ; cout<<endl ; 
    postOrder1(root) ; cout<<endl ; 
    postOrder2(root) ; cout<<endl ; 
    depthOrder(root) ; cout<<endl ; 
    cout<<countTreeNode(root)<<endl ; 
    cout<<depthTreeNode(root)<<endl ; 
    return 0 ; 
}