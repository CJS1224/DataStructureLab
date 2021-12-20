#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <queue>

using namespace std ;

template <class T>
class Node
{
    public :
        Node() { data = new T ; }
        Node(T d)
        {
            data = new T ;
            *data = d ;
        }
        Node &operator=(T d)
        {
            *data = d ;
            return *this ;
        }
        friend ostream &operator<<(ostream &out, Node n)
        {
            out << *(n.data) ;
            return out ;
        }
        friend ostream &operator<<(ostream &out, Node *n)
        {
            out << *(n -> data) ;
            return out ;
        }
        void setData(T d) { *data = d ; }
        T &getData() const { return *data ; }
    private :
        T *data ;
} ;

template <class T>
class ListNode : public Node<T>
{
    public :
        ListNode() : Node<T>(), prev(NULL), next(NULL) {}
        ListNode(T d) : Node<T>(d), prev(NULL), next(NULL) {}
        ListNode(ListNode *p, ListNode *n) : Node<T>(), prev(p), next(n) {}
        ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d), prev(p), next(n) {}
        ListNode *getNext() const { return next ; }
        ListNode *getPrev() const { return prev ; }
        void setNext(ListNode *n) { next = n ; }
        void setPrev(ListNode *p) { prev = p ; }
        ListNode &operator=(T d)
        {
            this -> setData(d) ;
            return *this ;
        }
    private :
        ListNode *prev ;
        ListNode *next ;
} ;

template <class T>
class LinkList
{
    public :
        LinkList() : head(NULL), tail(NULL), size(0) {}
        void addFromHead(T d)
        {
            size++ ;
            ListNode<T> *node = new ListNode<T>(d) ;
            if(head) head -> setPrev(node) ;
            node -> setNext(head) ;
            head = node ;
            if(tail == NULL) tail = node ;
        }
        void addFromTail(T d)
        {
            size++ ;
            ListNode<T> *node = new ListNode<T>(d) ;
            if(tail) tail -> setNext(node) ;
            node -> setPrev(tail) ;
            tail = node ;
            if(head == NULL) head = node ;
        }
        void addAfter(ListNode<T> *at, T d)
        {
            if(!exist(at)) return ;
            size++ ;
            ListNode<T> *node = new ListNode<T>(d) ;
            if(at -> getNext()) at -> getNext() -> setPrev(node) ;
            node -> setNext(at -> getNext()) ;
            at -> setNext(node) ;
            node -> setPrev(at) ;
            if(node -> getNext() == NULL) tail = node ;
        }
        ListNode<T> *removeFromHead()
        {
            size-- ;
            ListNode<T> *n = head ;
            if(head)
            {
                head = head -> getNext() ;
                if(head) head -> setPrev(NULL) ;
                else tail = NULL ;
                n -> setNext(NULL) ;
            }
            return n ;
        }
        ListNode<T> *removeFromTail()
        {
            size-- ;
            ListNode<T> *n = tail ;
            if(tail)
            {
                tail = tail -> getPrev() ;
                if(tail) tail -> setNext(NULL) ;
                else head = NULL ;
                n -> setPrev(NULL) ;
            }
            return n ;
        }
        ListNode<T> *remove(ListNode<T> *n)
        {
            if(!exist(n)) return NULL ;
            size-- ;
            if(n == head) return removeFromHead() ;
            if(n == tail) return removeFromTail() ;
            n -> getPrev() -> setNext(n -> getNext()) ;
            n -> getNext() -> setPrev(n -> getPrev()) ;
            n -> setNext(NULL) ;
            n -> setPrev(NULL) ;
            return n ;
        }
        ListNode<T> *exist(T d)
        {
            ListNode<T> *node = head ;
            while(node)
            {
                if(node -> getData() == d) return node ;
                node = node -> getNext() ;
            }
            return NULL ;
        }
        bool exist(ListNode<T> *n)
        {
            ListNode<T> *node = head ;
            while(node)
            {
                if(node == n) return true ;
                node = node -> getNext() ;
            }
            return false ;
        }
        ListNode<T> &operator[](int n)
        {
            ListNode<T> *node = head ;
            int j ;
            for(j = 0 ; j < n && node ; j++)
            {
                node = node -> getNext() ;
            }
            if(node == NULL) throw invalid_argument("index does not exist.") ;
            return *node ;
        }
        void print() const
        {
            ListNode<T> *node = head ;
            while(node)
            {
                cout << *node << " " ;
                node = node -> getNext() ;
            }
            cout << endl ;
        }
        ListNode<T> *getHead() const { return head ; }
        int getSize() const { return size ; }
    protected :
        ListNode<T> *head ;
        ListNode<T> *tail ;
        int size ;
} ;

template<class T>
class TreeNode : public Node<T>
{
    public :
        TreeNode() : Node<T>() { child = new LinkList<TreeNode<T> *> ; }
        TreeNode(T d) : Node<T>(d) { child = new LinkList<TreeNode<T> *> ; }
        void addChild(TreeNode *n) { child -> addFromTail(n) ; }
        void addChild(T d) { addChild(new TreeNode<T>(d)) ; }
        TreeNode<T> *operator[](int n) { return (*child)[n].getData() ; }
        LinkList<TreeNode<T> *> *getChild() const { return child ; }
        size_t size() const { return child -> getSize() ; }
    private :
        LinkList<TreeNode<T> *> *child ;
} ;

template <class T>
class Tree
{
    public :
        Tree() : root(NULL) {}
        TreeNode<T> *operator[](int n)
        {
            if(root == NULL) return NULL ;
            queue<TreeNode<T> *> q ;
            q.push(this -> root) ;
            int i = 0 ;
            while(!q.empty())
            {
                TreeNode<T> *cur = q.front() ;
                q.pop() ;
                if(i == n) return cur ;
                for(int j = 0 ; j < cur -> size() ; j++)
                {
                    q.push((*cur)[j]) ;
                }
                i++ ;
            }
            return NULL ;
        }
        int count() { return levelorder(1) ; }
        int levelorder(int mode = 0)
        {
            if(root == NULL) return 0 ;
            if(!mode) cout << "levelorder" << endl ;
            int counter = 1 ;
            queue<TreeNode<T> *> q ;
            q.push(root) ;
            while(!q.empty())
            {
                TreeNode<T> *cur = q.front() ;
                if(!mode) cout << cur -> getData() << endl ;
                q.pop() ;
                for(size_t i = 0 ; i < cur -> size() ; i++)
                {
                    q.push((*cur)[i]) ;
                    counter++ ;
                }
            }
            return counter ;
        }
        void preorder()
        {
            cout << "preorder" << endl ;
            preorder(root) ;
        }
        void postorder()
        {
            cout << "postorder" << endl ;
            postorder(root) ;
        }
        void setRoot(T d) { root = new TreeNode<T>(d) ; }
    private :
        TreeNode<T> *root ;
        int counter ;
        void preorder(TreeNode<T> *cur)
        {
            cout << cur -> getData() << endl ;
            for(size_t i = 0 ; i < cur -> size() ; i++)
            {
                preorder((*cur)[i]) ;
            }
        }
        void postorder(TreeNode<T> *cur)
        {
            for(size_t i = 0 ; i < cur -> size() ; i++)
            {
                postorder((*cur)[i]) ;
            }
            cout << cur -> getData() << endl ;
        }
} ;

int main(int argc, char const **argv)
{
    Tree<int> *tree = new Tree<int>() ;
    srand(time(NULL)) ;
    int i, j ;
    for(i = 0 ; i < 20 ; i++)
    {
        if(tree -> count() == 0) tree -> setRoot(rand() % 100) ;
        else
        {
            j = rand() % tree -> count() ;
            (*tree)[j] -> addChild(rand() % 100) ;
        }
    }
    tree -> levelorder() ;
    cout << endl ;
    tree -> preorder() ;
    cout << endl ;
    tree -> postorder() ;
    return 0 ;
}
