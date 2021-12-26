#include <bits/stdc++.h>

using namespace std ;

class Node
{
    public :
        Node(char d) : data(d), beside(nullptr), child(nullptr), end(0) {}
        char getData() const { return data ; }
        bool isEnd() const { return end ; }
        void setEnd(bool val) { end = val ; }
        Node *child ;
        Node *beside ;
    private :
        char data ;
        bool end ;
} ;

class Trie
{
    public :
        Trie() : root(nullptr) {}
        void insert(string s) { insert(s, &root, 1) ; }
        bool search(string s)
        {
            Node *cur = root ;
            bool end ;
            for(char w : s)
            {
                Node *curLevel = cur ;
                while(1)
                {
                    end = 0 ;
                    if(!curLevel) return 0 ;
                    if(w == curLevel -> getData())
                    {
                        end = curLevel -> isEnd() ;
                        cur = curLevel -> child ;
                        break ;
                    }
                    curLevel = curLevel -> beside ;
                }
            }
            if(end) return 1 ;
            return 0 ;
        }
    private :
        Node *root ;
        void insert(string s, Node **cur, bool existed)
        {
            if(s.length() < 1) return ;
            char w = s[0] ;
            if(!(*cur))
            {
                *cur = new Node(w) ;
                if(s.length() == 1) (*cur) -> setEnd(1) ;
                insert(s.substr(1, s.length()), &((*cur) -> child), 0) ;
            }
            else
            {
                bool repeat = (*cur) -> getData() == w ;
                if(existed && !repeat) insert(s, &((*cur) -> beside), 1) ;
                else
                {
                    if(s.length() == 1) (*cur) -> setEnd(1) ;
                    insert(s.substr(1, s.length()), &((*cur) -> child), repeat) ;
                }
            }
        }
} ;

int main(int argc, char const **argv)
{
    Trie *t = new Trie() ;
    int n, m ;
    string s ;
    cin >> n >> m ;
    for(int i = 1 ; i <= n ; i++)
    {
        cin >> s ;
        t -> insert(s) ;
    }
    for(int i = 1 ; i <= m ; i++)
    {
        cin >> s ;
        cout << t -> search(s) << endl ;
    }
    return 0 ;
}
