#include <bits/stdc++.h>
#include <ctime>

using namespace std ;

class Tree
{
    public :
        Tree()
        {
            for(int i = 0 ; i < 20 ; i++)
            {
                for(int j = 0 ; j < 4 ; j++)
                {
                    root[i][j] = -1 ;
                }
            }
        }
        int insert(int node)
        {
            int f = 0 ;
            int index = 0 ;
            while(root[index][0] != -1)
            {
                index++ ;
            }
            if(index >= 20) return -1 ;
            if(!index)
            {
                root[0][0] = 1 ;
                root[0][1] = node ;
                return 1 ;
            }
            else
            {
                root[index][0] = 1 ;
                root[index][1] = node ;
                while(1)
                {
                    if(root[f][1] < node)
                    {
                        if(root[f][3] == -1)
                        {
                            root[f][3] = index ;
                            return 1 ;
                        }
                        else f = root[f][3] ;
                    }
                    else
                    {
                        if(root[f][2] == -1)
                        {
                            root[f][2] = index ;
                            return 1 ;
                        }
                        else f = root[f][2] ;
                    }
                }
            }
        }
        void inorder()
        {
            int cur = 0 ;
            if(root[cur][0] == -1) return ;
            inorder(root[cur][2]) ;
            cout << root[cur][1] << endl ;
            inorder(root[cur][3]) ;
        }
        void preorder()
        {
            int cur = 0 ;
            if(root[cur][0] == -1) return ;
            cout << root[cur][1] << endl ;
            preorder(root[cur][2]) ;
            preorder(root[cur][3]) ;
        }
        void postorder()
        {
            int cur = 0 ;
            if(root[cur][0] == -1) return ;
            postorder(root[cur][2]) ;
            postorder(root[cur][3]) ;
            cout << root[cur][1] << endl ;
        }
        void levelorder()
        {
            int cur = 0 ;
            if(root[cur][0] == -1) return ;
            queue<int> q ;
            q.push(cur) ;
            while(!q.empty())
            {
                int que = q.front() ;
                cout << root[que][1] << endl ;
                q.pop() ;
                int left = root[que][2] ;
                int right = root[que][3] ;
                if(left != -1) q.push(left) ;
                if(right != -1) q.push(right) ;
            }
        }
    private :
        int root[20][4] ;
        void inorder(int cur)
        {
            if(cur == -1) return ;
            inorder(root[cur][2]) ;
            cout << root[cur][1] << endl ;
            inorder(root[cur][3]) ;
        }
        void preorder(int cur)
        {
            if(cur == -1) return ;
            cout << root[cur][1] << endl ;
            preorder(root[cur][2]) ;
            preorder(root[cur][3]) ;
        }
        void postorder(int cur)
        {
            if(cur == -1) return ;
            preorder(root[cur][2]) ;
            preorder(root[cur][3]) ;
            cout << root[cur][1] << endl ;
        }
} ;

int main(int argc, char const **argv)
{
    Tree *tree = new Tree() ;
    int node ;
    srand(time(NULL)) ;
    for(int i = 0 ; i < 10 ; i++)
    {
        node = rand() ;
        tree -> insert(node) ;
    }
    tree -> inorder() ;
    cout << endl ;
    tree -> preorder() ;
    cout << endl ;
    tree -> postorder() ;
    cout << endl ;
    tree -> levelorder() ;
    cout << endl ;
    return 0 ;
}
