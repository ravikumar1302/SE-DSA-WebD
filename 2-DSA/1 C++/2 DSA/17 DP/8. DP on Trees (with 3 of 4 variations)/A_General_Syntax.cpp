/*
General_Syntax


*/


int solve(node* root, int &res)     // res is used to store ans in DP for trees
{
    // Base case
    if(root == NULL)
        return 0;
    
    int l = solve(root -> left, res);
    int r = solve(root -> right, res);

    int temp = 1 + max(l,r);    // temp ans
    int ans = max(temp, some realtion to find remaning ans);

    int res = max(res, ans);

    return temp;
}

int fun_name(node* root)
{
    int res = INT_MIN;
    solve(root, res);

    return res;
}