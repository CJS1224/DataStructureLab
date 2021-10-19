#include <bits/stdc++.h>
#define SIZE 100

using namespace std ;

class Queue
{
    public :
        Queue() : top(0), bottom(0), tag(0) {}
        int enqueue(int data)
        {
            if((top % SIZE == bottom && tag) || (top == SIZE && !bottom)) return -1 ;
            else
            {
                top = (top + 1) % SIZE ;
                this -> data[top] = data ;
                if(top == bottom) tag = 1 ;
                return 1 ;
            }
        }
        int *dequeue()
        {
            if(top == bottom && !tag) return NULL ;
            else
            {
                bottom = (bottom + 1) % SIZE ;
                int *data = &(this -> data[bottom]) ;
                if(bottom == top) tag = 0 ;
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
