#include <bits/stdc++.h>
#define SIZE 100

using namespace std ;

class Stack
{
    public :
        Stack() : top(0) {}
        int push(int data)
        {
            if(top + 1 >= SIZE) return -1 ;
            this -> data[top++] = data ;
            return 1 ;
        }
        int *pop()
        {
            if(top == 0) return NULL ;
            return &(data[--top]) ;
        }
    private :
        int data[SIZE] ;
        int top ;
} ;

int main(int argc, char **argv)
{
    int data, *temp ;
    char command[50] ;
    Stack *stack = new Stack() ;
    while(1)
    {
        cin >> command ;
        if(strcmp(command, "exit") == 0) break ;
        else if(strcmp(command, "push") == 0)
        {
            cout << "Please input a integer data:" ;
            cin >> data ;
            if(stack -> push(data) == 1) cout << "Successfully push data " << data << " into stack." << endl ;
            else cout << "Failed to push data into stack." << endl ;
        }
        else if(strcmp(command, "pop") == 0)
        {
            temp = stack -> pop() ;
            if(temp == NULL) cout << "Failed to pop a data from stack" << endl ;
            else cout << "Pop data " << *temp << " from stack." << endl ;
        }
    }
    return 0 ;
}
