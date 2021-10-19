#include <bits/stdc++.h>
#define SIZE 100

using namespace std ;

class Node
{
    public :
        int data ;
        Node *next ;
} ;

class Queue
{
    public :
        Queue() : top(NULL), bottom(NULL) {}
        int enqueue(int data)
        {
            Node *node = new Node() ;
            node -> data = data ;
            node -> next = NULL ;
            if(top == NULL)
            {
                top = node ;
                bottom = node ;
                return 1 ;
            }
            else
            {
                bottom -> next = node ;
                bottom = node ;
                return 1 ;
            }
        }
        int *dequeue()
        {
            if(top == NULL) return NULL ;
            else
            {
                Node *deleteNode = top ;
                int *value = &(deleteNode -> data) ;
                top = top -> next ;
                if(top == NULL) bottom = NULL ;
                return value ;
            }
        }
    private :
        Node *top ;
        Node *bottom ;
} ;

int main(int argc, char **argv)
{
    int data, *temp ;
    string command ;
    Queue *queue = new Queue() ;
    while(1)
    {
        cin >> command ;
        if(command.compare("exit") == 0) break ;
        else if(command.compare("enqueue") == 0)
        {
            cout << "Please input a integer data:" ;
            cin >> data ;
            if(queue -> enqueue(data) == 1) cout << "Successfully enqueue data " << data << " into queue." << endl ;
            else cout << "Failed to enqueue data into queue." << endl ;
        }
        else if(command.compare("dequeue") == 0)
        {
            temp = queue -> dequeue() ;
            if(temp == NULL) cout << "Failed to dequeue a data from queue" << endl ;
            else cout << "Dequeue data " << *temp << " from queue." << endl ;
        }
    }
    return 0 ;
}
