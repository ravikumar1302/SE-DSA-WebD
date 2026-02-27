#include<iostream>
#include<queue>
using namespace std;

class node{
    public:
    int data;
    node* left;
    node* right;

    node(int d) {
        this -> data = d;
        this-> left = NULL;
        this-> right = NULL;
    }

};

void levelOrderTraversal(node* root) {
    queue<node*> q;
    q.push(root);
    q.push(NULL);   //for separator, to print new level in new line

    while(!q.empty()) {
        node* temp = q.front();
        q.pop();

        if(temp == NULL) { 
            //purana level complete traverse ho chuka hai
            cout << endl;
            if(!q.empty()) { 
                //queue still has some child ndoes
                q.push(NULL);
            }  
        }
        else{
            cout << temp -> data << " ";
            if(temp -> left) {
                q.push(temp ->left);
            }

            if(temp ->right) {
                q.push(temp -> right);
            }
        }
    }

}

// Coincedently, Inorder of a BST is sorted
void inorder(node* root) {
    //base case
    if(root == NULL) {
        return ;
    }

    inorder(root->left);
    cout << root-> data << " ";
    inorder(root->right);

}

void preorder(node* root) {
    //base case
    if(root == NULL) {
        return ;
    }

    cout << root-> data << " ";
    preorder(root->left);
    preorder(root->right);

}

void postorder(node* root) {
    //base case
    if(root == NULL) {
        return ;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root-> data << " ";

}

// Insertion in BST takes O(logN) time (because like binary search it neglects one portion based on the value)
node* insertIntoBST(node* &root, int d) {
    //base case
    if(root == NULL)    {
        root = new node(d);
        return root; 
    }

    if(d > root-> data) {
        //insert in right part
        root-> right = insertIntoBST(root -> right, d);
    }
    else    {
        //insert in left part
        root-> left = insertIntoBST(root -> left, d);
    }

    return root; 
}

void takeInput(node* &root)    {
    int data;
    cin >> data;

    while(data != -1)   {
        insertIntoBST(root, data);
        cin>>data;
    }
}

node* minValue(node* root)
{
    node* temp = root;

    while(temp -> left != NULL)
        temp = temp -> left;
    
    return temp;
}

node* maxValue(node* root)
{
    node* temp = root;

    while(temp -> right != NULL)
        temp = temp -> right;
    
    return temp;
}

node* deleteFromBST (node* root, int value)
{
    // Base case
    if(root == NULL)
        return NULL;
    
    if(root-> data == value)
    {
        // 0 child
        if(root-> left == NULL && root -> right == NULL)
        {
            delete root;
            return NULL;
        }

        // 1 child
        // left child
        if(root-> left != NULL && root -> right == NULL)
        {
            node* temp = root -> left;
            delete root;
            return temp;
        }
        // right child
        if(root-> left == NULL && root -> right != NULL)
        {
            node* temp = root -> right;
            delete root;
            return temp;
        }

        // 2 child
        if(root-> left != NULL && root -> right != NULL)
        {
            int mini = minValue(root -> right) -> data;
            root -> data = mini;

            root -> right = deleteFromBST(root-> right, mini);
            return root;
        }
    }

    else if(root -> data > value)
    {
        //Go to the left part
        root -> left = deleteFromBST(root -> left, value);
        return root;
    }
    else
    {
        //Go to the right part
        root -> right = deleteFromBST(root -> right, value);
        return root;
    }
} // Deleteion takes time O(height) in avg case and O(N) in worst case (skew tree)

int main() {
    node* root = NULL;

    cout<<"Enter data to create BST "<<endl;
    takeInput(root);
    //10 8 21 7 27 5 4 3 -1

    cout<<"Printing the BST"<<endl;
    levelOrderTraversal(root);

    cout<<endl<<"Printing inorder"<<endl;
    inorder(root);

    cout<<endl<<"Printing preorder"<<endl;
    preorder(root);

    cout<<endl<<"Printing postorder"<<endl;
    postorder(root);

    cout<<endl<< "Printing min value "<< minValue(root) -> data <<endl;
    cout<<endl<< "Printing max value "<< maxValue(root) -> data <<endl;

    root = deleteFromBST(root, 27);
    cout<<"Printing the BST"<<endl;
    levelOrderTraversal(root);

    return 0;
}