#include <bits/stdc++.h>
#define SIZE 100

using namespace std ;

class Node
{
    public :
        int data ;
        Node *next ;
} ;

class Stack
{
    public :
        Stack() : data(NULL) {}
        int push(int d)
        {
            Node *node = new Node() ;
            if(node == NULL) return -1 ;
            node -> data = d ;
            node -> next = this -> data ;
            this -> data = node ;
            return 1 ;
        }
        int *pop()
        {
            if(this -> data == NULL) return NULL ;
            else
            {
                Node *deleteNode = this -> data ;
                int *value = &deleteNode -> data ;
                this -> data = deleteNode -> next ;
                return value ;
            }
        }
    private :
        Node *data ;
} ;

int main(int argc, char **argv)
{
    int data, *temp ;
    string command ;
    Stack *stack = new Stack() ;
    while(1)
    {
        cin >> command ;
        if(command.compare("exit") == 0) break ;
        else if(command.compare("push") == 0)
        {
            cout << "Please input a integer data:" ;
            cin >> data ;
            if(stack -> push(data) == 1) cout << "Successfully push data " << data << " into stack." << endl ;
            else cout << "Failed to push data into stack." << endl ;
        }
        else if(command.compare("pop") == 0)
        {
            temp = stack -> pop() ;
            if(temp == NULL) cout << "Failed to pop a data from stack" << endl ;
            else cout << "Pop data " << *temp << " from stack." << endl ;
        }
    }
    return 0 ;
}
