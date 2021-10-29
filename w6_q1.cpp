#include <bits/stdc++.h>
#include <ctime>
#define SIZE 10

using namespace std ;

class Node
{
    public :
        Node() : Node(0, 0) {}
        Node(int r, int c) : row(r), col(c){}
        int getRow() const { return row ; }
        int getCol() const { return col ; }
        void setRow(int r) { if(r >= 0 && r < SIZE) row = r ; }
        void setCol(int c) { if(c >= 0 && c < SIZE) col = c ; }
    private :
        int col ;
        int row ;
} ;

class List
{
    public :
        List() : top(0) {}
        void addElement(int r, int c) { data[top++] = Node(r, c) ; }
        Node *removeElement()
        {
            if(!top) return NULL ;
            return &(data[--top]) ;
        }
        void printList()
        {
            for(int i = top - 1 ; i >= 0 ; i--)
            {
                cout << "(" << data[i].getRow() << ", " << data[i].getCol() << ")" << endl ;
            }
        }
        int getTop() const { return top ; }
    private :
        Node data[SIZE * SIZE] ;
        int top ;
} ;

class Maze
{
    public :
        Maze() : reach(0) { initMaze(SIZE) ; }
        void initMaze(int s)
        {
            int **maze = new int*[s] ;
            for(int i = 0 ; i < s ; i++)
            {
                maze[i] = new int[s] ;
            }
            for(int i = 0 ; i < s ; i++)
            {
                for(int j = 0 ; j < s ; j++)
                {
                    int random = rand() % 100 ;
                    maze[i][j] = (random < 25) ? 1 : 0 ;
                    if((!i && !j) || (i == s - 1 && j == s - 1)) maze[i][j] = 0 ;
                    cout << maze[i][j] << " " ;
                }
                cout << endl ;
            }
            this -> maze = maze ;
        }
        List *getPath()
        {
            List *list = new List() ;
            visit(list, 0, 0) ;
            if(list -> getTop() <= 1) return NULL ;
            return list ;
        }
        void printMaze()
        {
            for(int i = 0 ; i < SIZE ; i++)
            {
                for(int j = 0 ; j < SIZE ; j++)
                {
                    if(!(maze[i][j])) cout << " " ;
                    else if(maze[i][j]) cout << "*" ;
                }
                cout << endl ;
            }
        }
        void visit(List *list, int x, int y)
        {
            if(x == SIZE - 1 && y == SIZE - 1)
            {
                list -> addElement(SIZE - 1, SIZE - 1) ;
                reach = 1 ;
                return ;
            }
            maze[x][y] = 3 ;
            if(!reach && (y + 1) < SIZE && !maze[x][y + 1]) visit(list, x, y + 1) ;
            if(!reach && (y - 1) >= 0 && !maze[x][y - 1]) visit(list, x, y - 1) ;
            if(!reach && (x + 1) < SIZE && !maze[x + 1][y]) visit(list, x + 1, y) ;
            if(!reach && (x - 1) >= 0 && !maze[x - 1][y]) visit(list, x - 1, y) ;
            if(maze[x][y] == 3) maze[x][y] = 0 ;
            if(reach) list -> addElement(x, y) ;
        }
        int getReach() const { return reach ; }
    private :
        int **maze ;
        int reach ;
} ;

int main(int argc, char const **argv)
{
    srand(time(NULL)) ;
    Maze *maze = new Maze() ;
    maze -> printMaze() ;
    List *list = maze -> getPath() ;
    if(maze -> getReach()) list -> printList() ;
    else cout << "No path" << endl ;
    return 0 ;
}
