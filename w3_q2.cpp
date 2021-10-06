#include <bits/stdc++.h>
#define SIZE 100

using namespace std ;

class Queue
{
    public :
        Queue() : top(0), bottom(0), tag(0) {}
        bool isFull() { return this -> top % SIZE == this -> bottom && this -> tag ; }
        bool isEmpty() { return this -> top == this -> bottom && !tag ; }
        int enqueue(int data)
        {
            if(isFull() || (this -> top == SIZE - 1 && !this -> bottom)) return -1 ;
            else
            {
                this -> top = (this -> top + 1) % SIZE ;
                this -> data[this -> top] = data ;
                if(this -> top == this -> bottom) this -> tag = 1 ;
                return 1 ;
            }
        }
        int *dequeue()
        {
            if(isEmpty()) return NULL ;
            else
            {
                this -> bottom = (this -> bottom + 1) % SIZE ;
                int *data = &(this -> data[this -> bottom]) ;
                if(this -> bottom == this -> top) this -> tag = 0 ;
                return data ;
            }
        }
    private :
        int data[SIZE] ;
        int top ;
        int bottom ;
        int tag ;
} ;

int main(int argc, char **argv)
{
    int data, *temp ;
    char command[50] ;
    Queue *queue = new Queue() ;
    while(1)
    {
        cin >> command ;
        if(strcmp(command, "exit") == 0) break ;
        else if(strcmp(command, "enqueue") == 0)
        {
            cout << "Please input a integer data:" ;
            cin >> data ;
            if(queue -> enqueue(data) == 1) cout << "Successfully enqueue data " << data << " into queue." << endl ;
            else cout << "Failed to enqueue data into queue." << endl ;
        }
        else if(strcmp(command, "dequeue") == 0)
        {
            temp = queue -> dequeue() ;
            if(temp == NULL) cout << "Failed to dequeue a data from queue" << endl ;
            else cout << "Dequeue data " << *temp << " from queue." << endl ;
        }
    }
    return 0 ;
}
