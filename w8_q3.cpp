#include <bits/stdc++.h>
#include <ctime>

using namespace std ;

class Tree
{
    public :
        Tree()
        {
            for(int i = 0 ; i < 2000 ; i++)
            {
                root[i] = -1 ;
            }
        }
        int insert(int node)
        {
            int index = 0 ;
            while(index < 2000 && root[index] != -1)
            {
                index = (root[index] < node) ? (index * 2 + 2) : (index * 2 + 1) ;
            }
            root[index] = node ;
        }
        void inorder()
        {
            int cur = 0 ;
            if(root[cur] == -1) return ;
            inorder(cur * 2 + 2) ;
            cout << root[cur] << endl ;
            inorder(cur * 2 + 1) ;
        }
        void preorder()
        {
            int cur = 0 ;
            if(root[cur] == -1) return ;
            cout << root[cur] << endl ;
            preorder(cur * 2 + 2) ;
            preorder(cur * 2 + 1) ;
        }
        void postorder()
        {
            int cur = 0 ;
            if(root[cur] == -1) return ;
            postorder(cur * 2 + 2) ;
            postorder(cur * 2 + 1) ;
            cout << root[cur] << endl ;
        }
        void levelorder()
        {
            int cur = 0 ;
            if(root[cur] == -1) return ;
            queue<int> q ;
            q.push(cur) ;
            while(!q.empty())
            {
                int que = q.front() ;
                cout << root[que] << endl ;
                q.pop() ;
                int left = que * 2 + 2 ;
                int right = que * 2 + 1 ;
                if(root[left] != -1) q.push(left) ;
                if(root[right] != -1) q.push(right) ;
            }
        }
    private :
        int root[2000] ;
        void inorder(int cur)
        {
            if(root[cur] == -1) return ;
            inorder(cur * 2 + 2) ;
            cout << root[cur] << endl ;
            inorder(cur * 2 + 1) ;
        }
        void preorder(int cur)
        {
            if(root[cur] == -1) return ;
            cout << root[cur] << endl ;
            preorder(cur * 2 + 2) ;
            preorder(cur * 2 + 1) ;
        }
        void postorder(int cur)
        {
            if(root[cur] == -1) return ;
            postorder(cur * 2 + 2) ;
            postorder(cur * 2 + 1) ;
            cout << root[cur] << endl ;
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
