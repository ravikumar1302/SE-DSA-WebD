/*
Polynomial_Addition_GFG

Given two polynomial numbers represented by a linked list. The task is to complete the function addPolynomial() that adds these lists meaning adds the coefficients who have the same variable powers.
Note:  Given polynomials are sorted in decreasing order of power.

    Example 1:
    Input : LinkedList1:  (1,x2); LinkedList2:  (1,x3)
    Output : 1x^3 + 1x^2
    Explanation: Since, x2 and x3 both have different powers as 2 and 3. So, their coefficient can't be added up.

    Example 2:
    Input : LinkedList1:  (1,x3) -> (2,x2);  LinkedList2:  (3,x3) -> (4,x2)
    Output : 4x^3 + 6x^2
    Explanation: Since, x3 has two different coefficients as 3 and 1. Adding them up will lead to 4x3. Also, x2 has two coefficients as 4 and 2. So, adding them up will give 6x2.

Expected Time Complexity: O(N+M)
Expected Auxiliary Space: O(1)

*/

/* Structure of Node used
struct Node
{
    int coeff;
    int pow;
    struct Node* next;
    
    Node(int c, int p){
        coeff = c;
        pow = p;
        next = NULL;
    }
    
};
*/

class Solution{
  public:
    /* The below method print the required sum of polynomial
    p1 and p2 as specified in output  */
    Node* addPolynomial(Node *p1, Node *p2)
    {
        Node* ans = new Node(-1,-1);
        Node* anstail = ans;
        
        while(p1 && p2)
        {
            if(p1->pow == p2->pow)
            {
                Node* temp = new Node(p1->coeff + p2-> coeff, p1->pow);
                anstail -> next = temp;
                anstail = anstail -> next;
                // Updating p1 and p2 pointers
                p1 = p1 -> next;
                p2 = p2 -> next;
                
            }
            
            else if(p1->pow > p2->pow)
            {
                Node* temp = new Node(p1->coeff, p1->pow);
                anstail -> next = temp;
                anstail = anstail -> next;
                p1 = p1 -> next;
            }
            else    // p1->pow < p2->pow
            {
                Node* temp = new Node(p2->coeff, p2->pow);
                anstail -> next = temp;
                anstail = anstail -> next;
                p2 = p2 -> next;
            }
        }
        
        // If one of the list ends, but other not
        if(p1)
            anstail -> next = p1;
        if(p2)
            anstail -> next = p2;
        
        return ans -> next;
    }
};