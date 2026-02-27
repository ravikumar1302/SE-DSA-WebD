/*
Merge_Two_BSTs_Codestudio


You are given two balanced binary search trees of integers having ‘N’ and ‘M’ nodes. You have to merge the two BSTs into a balanced binary search tree and return the root node to that balanced BST.

A binary search tree (BST) is a binary tree data structure with the following properties.
    • The left subtree of a node contains only nodes with data less than the node’s data.
    • The right subtree of a node contains only nodes with data greater than the node’s data.
    • Both the left and right subtrees must also be binary search trees.
*/

/*************************************************************
    
    Following is the Binary Tree node structure:

    class TreeNode{

        public :
            int data;
            TreeNode *left;
            TreeNode *right;

            TreeNode(int data) {
                this -> data = data;
                left = NULL;
                right = NULL;
            }

            ~TreeNode() {
            if (left){
            delete left;
            }

            if (right){
            delete right;
            }
        }   
    };

*************************************************************/

void inorder(TreeNode<int>* root, vector<int> &value)
{
    if(root == NULL)
        return ;
    inorder(root->left, value);
    value.push_back(root->data);
    inorder(root->right, value);
}

// Function to merge two sorted vectors
vector<int> add_vector(vector<int> &v1, vector<int> &v2)
{
    vector<int> ans(v1.size() + v2.size());
    int len1 = v1.size();
    int len2 = v2.size();
    int i = 0;
    int j = 0;
    int k = 0;
    
    while(i<len1 && j<len2)
    {
        if(v1[i] < v2[j])
            ans[k++] = v1[i++];
        else
            ans[k++]=v2[j++];
    }
    
    while(i<len1)
        ans[k++] = v1[i++];
    while(j<len2)
        ans[k++] = v2[j++];
    
    return ans;
}

TreeNode<int>* buildTree(int s, int e, vector<int> &ans) {

    //Base case
    if(s > e)
        return NULL;
    int mid = (s+e)/2;
    TreeNode<int>* root = new TreeNode<int>(ans[mid]);
    root -> left = buildTree(s, mid-1, ans);
    root -> right = buildTree(mid+1, e, ans);
    
    return root;
}

TreeNode<int> *mergeBST(TreeNode<int> *root1, TreeNode<int> *root2){

// Make 2 inorder (sorted) vectors from BST's
// Merge those two sorted vector 
// Make BST from sorted vector
// Time : O(N+M), space : O(N+M) 
    
    //Step - 1: store inorder
    vector<int> v1, v2;
    inorder(root1, v1);
    inorder(root2, v2);
    
    //Step - 2: merge two sorted vectors
    vector<int> ans = add_vector(v1,v2);
    
    //Step - 3: Build BST from merger inorder vector
    int s = 0;
    int e = ans.size()-1;
    return buildTree(s, e, ans);
}

/**************************************************************************************************************************/

// Approach -2 
// Space O(height-1 + height-2)
/*
Step -1 : Convert 2 BST's to 2 Sorted linked lists in-place
Step -2 : Merge 2 sorted linked list 
Step -3 : Conversion of Sorted linked to BST conversion

Step -1 ALGORITHM
    Convert right subtree to LL (using recursion) and get head of that LL
    and connect root -> right = head and head -> left = root
    now head = root as right subtree and root and a LL now
    Similarly convert left subtree into LL and link it with root

Step -3 ALGORITHM
    Make a left tree from starting N/2 nodes
    next node is root and root -> left = left tree made in above step
    head = head -> next
    remaining (n - n/2 -1) right nodes are right tree 
    and root -> right = right tree made in above step
*/

// The code is giving some error, but logic wise seems right

// This Function convers BST to a Sorted DLL
void convertBST2LL(TreeNode<int>* root,TreeNode<int>* &head){
        if(root==NULL)
            return ;

        convertBST2LL(root->right,head);
       
        root->right=head;
        if(head!=NULL)
            head->left=root;

        head=root;
        convertBST2LL(root->left,head);
        
    }
    
//This function merges 2 sorted linked list  
TreeNode<int>* mergeLL(TreeNode<int>* head1,TreeNode<int>* head2){
        if(head1==NULL){
            return head2;
        }
        if(head2==NULL){
            return head1;
        }
        
        TreeNode<int>* head=NULL;
        TreeNode<int>* tail=NULL;
        while(head1 && head2)
        {
            if(head1->data<head2->data){
                if(head==NULL)
                {
                    head=head1;
                    tail=head1;
                }
                else
                {
                    tail->right=head1;
                    head1->left=tail;
                    tail=head1;   
                }
                head1=head1->right;
            }
            else
            {
                if(head==NULL)
                {
                    head=head2;
                    tail=head2;
                }
                else
                {
                    tail->right=head2;
                    head2->left=tail;
                    tail=head2;
                }
                head2=head2->right;
            }
        }
        while(head1)
        {
                tail->right=head1;
                head1->left=tail;
                tail=head1;
                head1=head1->right;
        }
        while(head2)
        {
                tail->right=head2;
                head2->left=tail;
                tail=head2;
                head2=head2->right;
        }
        return head;
    }

int countNodes(TreeNode<int>* head){
        if(head==NULL)
            return 0;
        
        int count=0;
        while(head)
        {
            head=head->right;
            count++;
        }
        return count;
    }
   
    
TreeNode<int>* convertLL2BST(TreeNode<int>* &head,int n)
    {
        if(n<=0 || head==NULL)
            return NULL;

        TreeNode<int>* left=convertLL2BST(head,n/2);
        TreeNode<int>* root=head;
        root->left=left;
        head=head->right;
        root->right=convertLL2BST(head,n-n/2-1);
        return root;
        
    }

TreeNode<int> *mergeBST(TreeNode<int> *root1, TreeNode<int> *root2){

       // Step -1 : Convert 2 BST's to 2 Sorted linked lists in-place
       TreeNode<int>* head1=NULL;
       convertBST2LL(root1,head1);
       head1->left=NULL;
    
       TreeNode<int>* head2=NULL;
       convertBST2LL(root2,head2);
       head2->left=NULL;
       
       // Step -2 : Merge 2 sorted linked list
       TreeNode<int>* resultedLL=mergeLL(head1,head2);

       // Step -3 : Conversion of Sorted linked to BST conversion
      int n=countNodes(resultedLL);
      return convertLL2BST(resultedLL,n);
}