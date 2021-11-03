#include <bits/stdc++.h>
#include <ctime>
#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

using namespace std ;

class Grid
{
    public :
        Grid() : Grid(0) {}
        Grid(int s)
        {
            state = s ;
            direction[UP] = NULL ;
            direction[DOWN] = NULL ;
            direction[LEFT] = NULL ;
            direction[RIGHT] = NULL ;
        }
        Grid *getDirection(int d) const { return direction[d] ; }
        int getState() const { return state ; }
        void setDirection(int d, Grid *g) { direction[d] = g ; }
        void setState(int s) { state = s ; }
    private :
        Grid *direction[4] ;
        int state ;
} ;

class List
{
    public :
        List() : top(0) {}
        void addElement(Grid *g) { data[top++] = g ; }
        Grid *removeElement()
        {
            if(top == 0) return NULL ;
            return data[--top] ;
        }
        void printPath() const
        {
            for(int i = top - 1 ; i > 0 ; i--)
            {
                if(data[i - 1] == data[i] -> getDirection(UP)) cout << "UP" << endl ;
                else if(data[i - 1] == data[i] -> getDirection(DOWN)) cout << "DOWN" << endl ;
                else if(data[i - 1] == data[i] -> getDirection(LEFT)) cout << "LEFT" << endl ;
                else if(data[i - 1] == data[i] -> getDirection(RIGHT)) cout << "RIGHT" << endl ;
            }
        }
        int getTop() const { return top ; }
    private :
        Grid *data[SIZE * SIZE] ;
        int top ;
} ;

class Maze
{
    public :
        Maze() : reach(0) { initMaze(SIZE) ; }
        void initMaze(int s)
        {
            Grid *maze[s][s] ;
            int wallCounts = 0 ;
            for(int i = 0 ; i < s ; i++)
            {
                for(int j = 0 ; j < s ; j++)
                {
                    maze[i][j] = new Grid() ;
                }
            }
            for(int i = 0 ; i < s ; i++)
            {
                for(int j = 0 ; j < s ; j++)
                {
                    int random = rand() % 100 ;
                    if(random < 25 && wallCounts <= 20)
                    {
                        maze[i][j] -> setState(1) ;
                        wallCounts++ ;
                    }
                    if(i + 1 < SIZE) maze[i][j] -> setDirection(DOWN, maze[i + 1][j]) ;
                    if(j + 1 < SIZE) maze[i][j] -> setDirection(RIGHT, maze[i][j + 1]) ;
                    if(i - 1 >= 0) maze[i][j] -> setDirection(UP, maze[i - 1][j]) ;
                    if(j - 1 >= 0) maze[i][j] -> setDirection(LEFT, maze[i][j - 1]) ;
                }
            }
            maze[0][0] -> setState(0) ;
            maze[9][9] -> setState(0) ;
            this -> maze = **maze ;
        }
        List *getPath(Maze *m)
        {
            List *list = new List() ;
            visit(list, maze, m) ;
            if(list -> getTop() <= 1) return NULL ;
            return list ;
        }
        void printMaze()
        {
            Grid *i = maze, *j ;
            while(i != NULL)
            {
                j = i ;
                while(j != NULL)
                {
                    cout << j -> getState() << " " ;
                    j = j -> getDirection(RIGHT) ;
                }
                cout << endl ;
                i = i -> getDirection(DOWN) ;
            }
            cout << endl ;
        }
        void visit(List *list, Grid *maze, Maze *m)
        {
            maze -> setState(2) ;
            m -> printMaze() ;
            if(maze -> getDirection(RIGHT) == NULL && maze -> getDirection(DOWN) == NULL)
            {
                list -> addElement(maze) ;
                reach = 1 ;
                return ;
            }
            if(!reach && maze -> getDirection(UP) && !(maze -> getDirection(UP) -> getState()))
                visit(list, maze -> getDirection(UP), m) ;
            if(!reach && maze -> getDirection(DOWN) && !(maze -> getDirection(DOWN) -> getState()))
                visit(list, maze -> getDirection(DOWN), m) ;
            if(!reach && maze -> getDirection(RIGHT) && !(maze -> getDirection(RIGHT) -> getState()))
                visit(list, maze -> getDirection(RIGHT), m) ;
            if(!reach && maze -> getDirection(LEFT) && !(maze -> getDirection(LEFT) -> getState()))
                visit(list, maze -> getDirection(LEFT), m) ;
            if(maze -> getState() == 2) maze -> setState(0) ;
            if(reach) list -> addElement(maze) ;
        }
        int getReach() const { return reach ; }
    private :
        Grid *maze ;
        int reach ;
} ;

int main(int argc, char const **argv)
{
    srand(time(NULL)) ;
    Maze *maze = new Maze() ;
    maze -> printMaze() ;
    List *list = maze -> getPath(maze) ;
    if(!list) cout << "No path" << endl ;
    else list -> printPath() ;
    return 0 ;
}
