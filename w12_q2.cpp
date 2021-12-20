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
            ListNode<T> *n = head ;
            if(head)
            {
                head = head -> getNext() ;
                if(head) head -> setPrev(NULL) ;
                else tail = NULL ;
                n -> setNext(NULL) ;
                size-- ;
            }
            return n ;
        }
        ListNode<T> *removeFromTail()
        {
            ListNode<T> *n = tail ;
            if(tail)
            {
                tail = tail -> getPrev() ;
                if(tail) tail -> setNext(NULL) ;
                else head = NULL ;
                n -> setPrev(NULL) ;
                size-- ;
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
        TreeNode<T> *getRoot() const { return root ; }
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

template <class T>
class BinaryTreeNode : public Node<T>
{
    public :
        BinaryTreeNode() : Node<T>(), left(NULL), right(NULL) {}
        BinaryTreeNode(T d) : Node<T>(d), left(NULL), right(NULL) {}
        BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(), left(l), right(r) {}
        BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d), left(l), right(r) {}
        void setLeft(BinaryTreeNode<T> *l) { left = l ; }
        void setRight(BinaryTreeNode<T> *r) { right = r ; }
        BinaryTreeNode<T> *&getLeft() { return left ; }
        BinaryTreeNode<T> *&getRight() { return right ; }
        bool operator>(BinaryTreeNode<T> n)
        {
            if(*(this -> data) > *(n.data)) return true ;
            return false ;
        }
        bool operator==(BinaryTreeNode<T> n)
        {
            if(*(this -> data) == *(n.data)) return true ;
            return false ;
        }
    private :
        BinaryTreeNode<T> *left ;
        BinaryTreeNode<T> *right ;
} ;

template <class T>
class BinaryTree
{
    public :
        BinaryTree() : root(NULL), count(0) {}
        static BinaryTree<T> *convertFromGeneralTree(Tree<T> *tree)
        {
            BinaryTree<T> *_tree = new BinaryTree<T>() ;
            if(tree -> getRoot() == NULL) return _tree ;
            queue<pair<TreeNode<T> *, BinaryTreeNode<T> *>> q ;
            _tree -> root = new BinaryTreeNode<T>(tree -> getRoot() -> getData()) ;
            q.push(pair<TreeNode<T> *, BinaryTreeNode<T> *>(tree -> getRoot(), _tree -> root)) ;
            _tree -> count++ ;
            while(!q.empty())
            {
                pair<TreeNode<T> *, BinaryTreeNode<T> *> cur = q.front() ;
                for(int i = 0 ; ; i++)
                {
                    BinaryTreeNode<T> *n ;
                    try { n = new BinaryTreeNode<T>((*(cur.first))[i] -> getData()) ; }
                    catch(invalid_argument e) { break ; }
                    if(i) q.back().second -> setRight(n) ;
                    else cur.second -> setLeft(n) ;
                    q.push(pair<TreeNode<T> *, BinaryTreeNode<T> *>((*(cur.first))[i], n)) ;
                    _tree -> count++ ;
                }
                q.pop() ;
            }
            return _tree ;
        }
        virtual BinaryTreeNode<T> *insert(T d)
        {
            BinaryTreeNode<T> *node = new BinaryTreeNode<T>(d) ;
            if(root == NULL) root = node ;
            else
            {
                int j = count + 1 ;
                int k = 1 ;
                BinaryTreeNode<T> *cur = root ;
                while(k <= j)
                {
                    k = k << 1 ;
                }
                k = k >> 2 ;
                while(k > 1)
                {
                    if(k & j) cur = cur -> getRight() ;
                    else cur = cur -> getLeft() ;
                    k = k >> 1 ;
                }
                if(k & j) cur -> setRight(node) ;
                else cur -> setLeft(node) ;
            }
            count++ ;
            return node ;
        }
        BinaryTreeNode<T> *remove(BinaryTreeNode<T> *n)
        {
            if(!exist(n)) return NULL ;
            BinaryTreeNode<T> *last = getLast() ;
            if(last == root)
            {
                count-- ;
                root = NULL ;
                return n ;
            }
            BinaryTreeNode<T> *lastsFather = getFather(last) ;
            if(lastsFather -> getLeft() == last) lastsFather -> setLeft(NULL) ;
            else lastsFather -> setRight(NULL) ;
            if(last == n)
            {
                count-- ;
                return n ;
            }
            if(n != root)
            {
                BinaryTreeNode<T> *father = getFather(n) ;
                if(father -> getLeft() == n) father -> setLeft(last) ;
                else father -> setRight(last) ;
            }
            else root = last ;
            last -> setLeft(n -> getLeft()) ;
            last -> setRight(n -> getRight()) ;
            n -> setLeft(NULL) ;
            n -> setRight(NULL) ;
            count-- ;
            return n ;
        }
        BinaryTreeNode<T> *getFather(BinaryTreeNode<T> *n)
        {
            if(n == root || !exist(n)) return NULL ;
            return _getFather(root, n) ;
        }
        bool exist(BinaryTreeNode<T> *n) { return _exist(root, n) ; }
        BinaryTreeNode<T> *getRoot() { return root ; }
        void print() { _print(root, 0) ; }
        void swapNode(BinaryTreeNode<T> *n1, BinaryTreeNode<T> *n2)
        {
            if(!exist(n1) || !exist(n2)) return ;
            BinaryTreeNode<T> *father1 = getFather(n1) ;
            BinaryTreeNode<T> *father2 = getFather(n2) ;
            if(father1)
            {
                if(father1 -> getLeft() == n1) father1 -> setLeft(n2) ;
                else father1 -> setRight(n2) ;
            }
            else root = n2 ;
            if(father2)
            {
                if(father2 -> getLeft() == n2) father2 -> setLeft(n1) ;
                else father2 -> setRight(n1) ;
            }
            else root = n1 ;
            BinaryTreeNode<T> *n1L = n1 -> getLeft() ;
            BinaryTreeNode<T> *n1R = n1 -> getRight() ;
            BinaryTreeNode<T> *n2L = n2 -> getLeft() ;
            BinaryTreeNode<T> *n2R = n2 -> getRight() ;
            n1 -> setLeft(n2L) ;
            n1 -> setRight(n2R) ;
            n2 -> setLeft(n1L) ;
            n2 -> setRight(n1R) ;
        }
    protected :
        BinaryTreeNode<T> *root ;
        int count ;
    private :
        BinaryTreeNode<T> *getLast()
        {
            int j = count, k = 1 ;
            BinaryTreeNode<T> *cur = root ;
            while(k <= j)
            {
                k = k << 1 ;
            }
            k = k >> 2 ;
            while(k > 0)
            {
                if(k & j) cur = cur -> getRight() ;
                else cur = cur -> getLeft() ;
                k = k >> 1 ;
            }
            return cur ;
        }
        bool _exist(BinaryTreeNode<T> *r, BinaryTreeNode<T> *n)
        {
            if(n == r) return true ;
            if(r -> getLeft() && _exist(r -> getLeft(), n)) return true ;
            if(r -> getRight() && _exist(r -> getRight(), n)) return true ;
            return false ;
        }
        BinaryTreeNode<T> *_getFather(BinaryTreeNode<T> *r, BinaryTreeNode<T> *n) const
        {
            if(r == NULL) return NULL ;
            if(r -> getLeft() == n || r -> getRight() == n) return r ;
            BinaryTreeNode<T> *t ;
            t = _getFather(r -> getLeft(), n) ;
            if(t) return t ;
            t = _getFather(r -> getRight(), n) ;
            return t ;
        }
        void _print(BinaryTreeNode<T> *r, int n)
        {
            if(r == NULL) return ;
            int j ;
            _print(r -> getRight(), n + 1) ;
            for(j = 0 ; j < n ; j++)
            {
                cout << "   " ;
            }
            cout << r << endl ;
            _print(r -> getLeft(), n + 1) ;
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
    cout << endl ;
    BinaryTree<int> *binaryTree = BinaryTree<int>::convertFromGeneralTree(tree) ;
    binaryTree -> print() ;
    return 0 ;
}
