#include <bits/stdc++.h>

using namespace std ;

class Node
{
    public :
        Node() : data(0), next(NULL) {}
        int data ;
        Node *next ;
} ;

class Set
{
    public :
        Set() : element(NULL), beginning(NULL) {}
        int addElement(int e)
        {
            Node *node = new Node() ;
            if(node == NULL) return 0 ;
            node -> data = e ;
            if(element == NULL)
            {
                element = node ;
                beginning = node ;
                return 1 ;
            }
            Node *cur = beginning ;
            while(cur)
            {
                if(cur -> data == e) return 0 ;
                cur = cur -> next ;
            }
            element -> next = node ;
            element = element -> next ;
            return 1 ;
        }
        Set *unions(const Set *b) const
        {
            Set *s = new Set() ;
            Node *n1 = getBeginning() ;
            Node *n2 = b -> getBeginning() ;
            while(n1)
            {
                s -> addElement(n1 -> data) ;
                n1 = n1 -> next ;
            }
            while(n2)
            {
                s -> addElement(n2 -> data) ;
                n2 = n2 -> next ;
            }
            return s ;
        }
        Set *intersections(const Set *b) const
        {
            Set *s = new Set() ;
            Node *n1 = getBeginning() ;
            while(n1)
            {
                Node *n2 = b -> getBeginning() ;
                while(n2)
                {
                    if(n1 -> data == n2 -> data) s -> addElement(n1 -> data) ;
                    n2 = n2 -> next ;
                }
                n1 = n1 -> next ;
            }
            return s ;
        }
        bool equivalent(const Set *b) const
        {
            Node *n1 = getBeginning() ;
            Node *n2 = b -> getBeginning() ;
            while(n1)
            {
                if(!same(n1 -> data, n2)) return 0 ;
                n1 = n1 -> next ;
            }
            while(n2)
            {
                if(!same(n2 -> data, n1)) return 0 ;
                n2 = n2 -> next ;
            }
            return 1 ;
        }
        void listAll() const
        {
            Node *cur = beginning ;
            while(cur != NULL)
            {
                cout << cur -> data << " " ;
                cur = cur -> next ;
            }
        }
        Node *getBeginning() const { return beginning ; }
        bool same(int e, Node *node) const
        {
            while(node)
            {
                if(node -> data == e) return 1 ;
                node = node -> next ;
            }
            return 0 ;
        }
    private :
        Node *element ;
        Node *beginning ;
} ;

int main(int argc, char const **argv)
{
    Set *a = new Set() ;
    Set *b = new Set() ;
    Set *c ;
    Node *cur ;
    a -> addElement(1) ;
    a -> addElement(2) ;
    a -> addElement(3) ;
    b -> addElement(3) ;
    b -> addElement(4) ;
    b -> addElement(5) ;
    b -> addElement(5) ;
    c = a -> unions(b) ;
    c -> listAll() ;
    c = a -> intersections(b) ;
    c -> listAll() ;
    if(a -> equivalent(b) == 0) cout << "Not equivalent." << endl ;
    else cout << "Equivalent!" << endl ;
    return 0 ;
}
