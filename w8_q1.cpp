#include <bits/stdc++.h>
#include <ctime>

using namespace std ;

class Node
{
    public :
        int level ;
        int data ;
        Node *left ;
        Node *right ;
} ;

class Tree
{
    public :
        Tree() : root(NULL) {}
        int insert(Node *n) { insert(&root, n, 0) ; }
        void inorder()
        {
            if(root == NULL) return ;
            inorder(root -> left) ;
            cout << root -> data << "\t" << root -> level << endl ;
            inorder(root -> right) ;
        }
        void preorder()
        {
            if(root == NULL) return ;
            cout << root -> data << "\t" << root -> level << endl ;
            preorder(root -> left) ;
            preorder(root -> right) ;
        }
        void postorder()
        {
            if(root == NULL) return ;
            postorder(root -> left) ;
            postorder(root -> right) ;
            cout << root -> data << "\t" << root -> level << endl ;
        }
        void levelorder()
        {
            if(root == NULL) return ;
            queue<Node*> q ;
            q.push(root) ;
            while(!q.empty())
            {
                Node *node = q.front() ;
                cout << node -> data << "\t" << node -> level << endl ;
                q.pop() ;
                if(node -> left != NULL) q.push(node -> left) ;
                if(node -> right != NULL) q.push(node -> right) ;
            }
        }
    private :
        Node *root ;
        void insert(Node **r, Node *n, int level)
        {
            if(*r == NULL)
            {
                n -> level = level ;
                *r = n ;
            }
            else if(n -> data > (*r) -> data) insert(&((*r) -> right), n, level + 1) ;
            else insert(&((*r) -> left), n, level + 1) ;
        }
        void inorder(Node *root)
        {
            if(root == NULL) return ;
            inorder(root -> left) ;
            cout << root -> data << "\t" << root -> level << endl ;
            inorder(root -> right) ;
        }
        void preorder(Node *root)
        {
            if(root == NULL) return ;
            cout << root -> data << "\t" << root -> level << endl ;
            preorder(root -> left) ;
            preorder(root -> right) ;
        }
        void postorder(Node *root)
        {
            if(root == NULL) return ;
            postorder(root -> left) ;
            postorder(root -> right) ;
            cout << root -> data << "\t" << root -> level << endl ;
        }
} ;

int main(int argc, char const **argv)
{
    Tree *tree = new Tree() ;
    Node *node ;
    srand(time(NULL)) ;
    for(int i = 0 ; i < 10 ; i++)
    {
        node = new Node() ;
        node -> data = rand() ;
        node -> left = NULL ;
        node -> right = NULL ;
        tree -> insert(node) ;
    }
    tree -> inorder() ;
    cout << endl ;
    tree -> preorder() ;
    cout << endl ;
    tree -> postorder() ;
    cout << endl ;
    cout << endl ;
    tree -> levelorder() ;
    cout << endl ;
    return 0 ;
}
