/*
Tower_Of_Hanoi_GFG

The tower of Hanoi is a famous puzzle where we have three rods and N disks. The objective of the puzzle is to move the entire stack to another rod. You are given the number of discs N. Initially, these discs are in the rod 1. You need to print all the steps of discs movement so that all the discs reach the 3rd rod. Also, you need to find the total moves.
Note: The discs are arranged such that the top disc is numbered 1 and the bottom-most disc is numbered N. Also, all the discs have different sizes and a bigger disc cannot be put on the top of a smaller disc. Refer the provided link to get a better clarity about the puzzle.

Example 1:

Input : N = 2
Output:
move disk 1 from rod 1 to rod 2
move disk 2 from rod 1 to rod 3
move disk 1 from rod 2 to rod 3
3
Explanation: For N=2 , steps will be as follows in the example and total 3 steps will be taken.

Expected Time Complexity: O(2^N).
Expected Auxiliary Space: O(N).
*/

class Solution{
    public:
    // You need to complete this function

    // avoid space at the starting of the string in "move disk....."
    long long toh(int N, int from, int to, int aux) {
    if(N==1)
   { 
       cout<<"move disk 1 from rod "<<from<<" to rod "<<to<<endl;
       return 1;
       
   }
       toh(N-1,from,aux,to);
       cout<<"move disk "<<N<<" from rod "<<from<<" to rod "<<to<<endl;
       toh(N-1,aux,to,from);
       return pow(2,N)-1;
   
    }
};