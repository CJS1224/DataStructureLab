#include <iostream>

using namespace std ;

class Grid
{
    public :
        Grid() {}
        Grid(string t) : things(t) {}
        Grid(string t, int n) : things(t), number(n) {}
        void setVisit(int v) { visit = v ; }
        int getVisit() const { return visit ; }
        int getNumber() const { return number ; }
        string getThings() const { return things ; }
    private :
        string things ;
        int visit = 0 ;
        int number = 0 ;
} ;

class Nurikabe
{
    public :
        Nurikabe(char game[20][20], int n)
        {
            result = 0 ;
            Size = n ;
            for(int i = 0 ; i < n ; i++)
            {
                for(int j = 0 ; j < n ; j++)
                {
                    if(game[i][j] == 'W' || game[i][j] == 'w') grid[i][j] = Grid("wall") ;
                    else if(game[i][j] == '.') grid[i][j] = Grid("dot") ;
                    else if(isdigit(game[i][j])) grid[i][j] = Grid("number", game[i][j] - '0') ;
                    else grid[i][j] = Grid("number", game[i][j] - '0') ;
                }
            }
            if(checkDot() && checkWall()) result = 1 ;
        }
        int isCorrect() const { return result ; }
    private :
        Grid grid[20][20] = {} ;
        int Size ;
        int dotCount ;
        int result ;
        int getFirstWall(int m)
        {
            for(int i = 0 ; i < Size ; i++)
            {
                for(int j = 0 ; j < Size ; j++)
                {
                    if(grid[i][j].getThings() == "wall") return (!m) ? i : j ;
                }
            }
            return Size + 1 ;
        }
        void visitWall(int x, int y)
        {
            if(grid[x][y].getThings() != "wall") return ;
            grid[x][y].setVisit(1) ;
            if(y + 1 < Size && !(grid[x][y + 1].getVisit())) visitWall(x, y + 1) ;
            if(y - 1 >= 0 && !(grid[x][y - 1].getVisit())) visitWall(x, y - 1) ;
            if(x + 1 < Size && !(grid[x + 1][y].getVisit())) visitWall(x + 1, y) ;
            if(x - 1 >= 0 && !(grid[x - 1][y].getVisit())) visitWall(x - 1, y) ;
        }
        int isSquare(int x, int y)
        {
            if(x + 1 >= Size || y + 1 >= Size) return 0 ;
            if(grid[x][y + 1].getThings() == "wall" && grid[x + 1][y].getThings() == "wall" && grid[x + 1][y + 1].getThings() == "wall")
            {
                return 1 ;
            }
            return 0 ;
        }
        int checkWall()
        {
            int x = getFirstWall(0) ;
            int y = getFirstWall(1) ;
            if(x > Size || y > Size) return 0 ;
            visitWall(x, y) ;
            for(int i = 0 ; i < Size ; i++)
            {
                for(int j = 0 ; j < Size ; j++)
                {
                    if(grid[i][j].getThings() == "wall")
                    {
                        if(!(grid[i][j].getVisit()) || isSquare(i, j)) return 0 ;
                    }
                }
            }
            return 1 ;
        }
        void visitDot(int x, int y, int m)
        {
            if(!m)
            {
                if(grid[x][y].getThings() != "dot") return ;
            }
            if(dotCount == -1) return ;
            if(grid[x][y].getVisit() == 1)
            {
                dotCount = -1 ;
                return ;
            }
            dotCount++ ;
            grid[x][y] .setVisit(2) ;
            if(y + 1 < Size && !(grid[x][y + 1].getVisit())) visitDot(x, y + 1, 0) ;
            if(y - 1 >= 0 && !(grid[x][y - 1].getVisit())) visitDot(x, y - 1, 0) ;
            if(x + 1 < Size && !(grid[x + 1][y].getVisit())) visitDot(x + 1, y, 0) ;
            if(x - 1 >= 0 && !(grid[x - 1][y].getVisit())) visitDot(x - 1, y, 0) ;
        }
        void setDotToVisit()
        {
            for(int i = 0 ; i < Size ; i++)
            {
                for(int j = 0 ; j < Size ; j++)
                {
                    if(grid[i][j].getVisit() == 2) grid[i][j].setVisit(1) ;
                }
            }
        }
        int checkDot()
        {
            for(int i = 0 ; i < Size ; i++)
            {
                for(int j = 0 ; j < Size ; j++)
                {
                    if(grid[i][j].getThings() == "number")
                    {
                        dotCount = 0 ;
                        visitDot(i, j, 1) ;
                        setDotToVisit() ;
                        if(dotCount != grid[i][j].getNumber()) return 0 ;
                    }
                }
            }
            return 1 ;
        }
} ;

int main(int argc, char const **argv)
{
    int n ;
    char game[20][20]  ;
    cin >> n ;
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            cin >> game[i][j] ;
        }
    }
    Nurikabe *a = new Nurikabe(game, n) ;
    cout << a -> isCorrect() ;
    return 0 ;
}
