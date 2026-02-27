/*
Bheem_Wants_Ladoos

*/


/*
// node structure:

struct Node
{
    int data;
    Node* left;
    Node* right;
};

*/


// 
class Solution{

    public:
    Node* createMapping(Node* root, int home, map<Node*, Node*> &nodeToParent)
    {
        Node* result = NULL;
        queue<Node*> q;
        q.push(root);
        nodeToParent[root] = NULL;
        
        while(!q.empty())
        {
            Node* front = q.front();
            q.pop();
            
            if(front -> data == home)
                result = front;
            
            if(front -> left)
            {
                nodeToParent[front -> left] = front;
                q.push(front -> left);
            }
            if(front -> right)
            {
                nodeToParent[front -> right] = front;
                q.push(front -> right);
            }
        }
        
        return result;
        
    }
    
    int max_lodoos(Node* root, map<Node*, Node*> &nodeToParent, int k)
    {
        map<Node*, bool> visited;
        queue<Node*> q;
        q.push(root);
        visited[root] = true;
        
        int sum = root -> data;
        
        while(!q.empty())
        {
            int size = q.size();
            //bool flag = 0;
            for(int i=0; i<size; i++)
            {
                // processing neighbouring
                Node* front = q.front();
                q.pop();
                
                if(front -> left && !visited[front -> left] && k)
                {
                    //flag = 1;
                    sum += front -> left -> data;
                    q.push(front -> left);
                    visited[front -> left] = 1;
                }
                
                if(front -> right && !visited[front -> right] && k)
                {
                    //flag = 1;
                    sum += front -> right -> data;
                    q.push(front -> right);
                    visited[front -> right] = 1;
                }
                if(nodeToParent[front] && !visited[nodeToParent[front]] && k)
                {
                    //flag = 1;
                    sum += nodeToParent[front]-> data;
                    q.push(nodeToParent[front]);
                    visited[nodeToParent[front]] = 1;
                }
            }
            k--;
        }
        
        return sum;
    }
    
    int ladoos(Node* root, int home, int k)
    {
        // Approach : To go to parent node, we have to store parent of each node like that of burnig tree
        
        map<Node*, Node*> nodeToParent;
        Node* targetNode = createMapping(root, home, nodeToParent);
        
        int ans = max_lodoos(targetNode, nodeToParent, k);
        return ans;
    }
};