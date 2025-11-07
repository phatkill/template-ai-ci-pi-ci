#include<bits/stdc++.h>
using namespace std;
#define mask(n) (1LL<<(n))
#define checkBit(bit,n) ((n) & mask(bit))
#define flipBit(bit,n) ((n) ^ mask(bit))
#define cntBit(n) __builtin_popcount(n)
#define fastIO ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
#define ll long long
#define repu(i,a,b)  for(int i=a;i<=b;i++)  // increasing loop from a to b
#define repd(i,a,b)  for(int i=a;i>=b;i--)  // decreasing loop from a to b

struct Trie{
    struct Node
    {
    Node* child[26];  // array of 26 pointers for letters a-z
    int cnt;          // count words passing through this node
    int exist;        // count words ending at this node
        
        Node(){
            for (int i=0;i<26;i++)
                child[i]=NULL;  // initialize all child pointers to NULL
            
            exist=cnt=0;  // initialize counters to 0
        }
    };

    Node* root;  // root node of Trie
    
    Trie(){
    root=new Node();  // create root node
    }

    // Add a string into the Trie
    void add_string(string s){
        Node* p=root;  // start at root
        
        for (auto f:s){  // iterate characters
            int c=f-'a';  // convert char to index (0-25)

            if (p->child[c]==NULL) 
                p->child[c]=new Node();  // create node if absent
            
            p=p->child[c];  // move to child
            p->cnt++;       // increment pass-through count
        }
        p->exist++;  // mark word termination here
    }

    // Recursive deletion helper
    bool delete_string_recursive(Node* p,string s,int i){
        if (i!=s.size()){
            int c=s[i]-'a';
            // Recurse for next character
            bool is_child_deleted=delete_string_recursive(p->child[c],s,i+1);
            
            if (is_child_deleted) 
                p->child[c]=NULL;  // clear pointer if child deleted
        }
        else 
            p->exist--;  // decrement terminal word count

        if (p!=root){
            p->cnt--;  // decrement pass-through count
            
            if (p->cnt==0){  // if no word passes here
                delete(p);   // free memory
                return true; // signal parent to nullify pointer
            }
        }
        
        return false;
    }

    // Delete a string from Trie
    void delete_string(string s){
        if (!find_string(s)) return;  // check existence first
        delete_string_recursive(root,s,0);
    }

    // Find a string in Trie
    bool find_string(string s){
        Node *p=root;

        for (auto f:s){
            int c=f-'a';

            if (p->child[c]==NULL)
return 0;  // path does not exist

            p=p->child[c];
        }

        return (p->exist!=0);  // true if a word ends here
    }

    // Count words having prefix s
    int prefix_cnt(string s){
        Node *p=root;

        for (auto f:s){  // iterate prefix characters
            int c=f-'a';

            if (p->child[c]==NULL) 
                return 0;  // no word has this prefix

            p=p->child[c];
        }

        return p->cnt;  // number of words passing through last prefix node
    }
};

int main()
{
    // fastIO   
    int n,q;
    cin>>n>>q;  // read number of words and queries

    Trie *tr=new Trie();  // create Trie
    
    string tmp;
    repu(i,1,n){
        cin>>tmp;
    tr->add_string(tmp);  // add n words
    }
    
    repu(i,1,q){
        cin>>tmp;
        cout<<tr->prefix_cnt(tmp)<<"\n";  // answer q-th query
    }
}

/*
EXAMPLE INPUT/OUTPUT:

INPUT:
5 3
apple
app
application
apply
banana
app
ban
cat

Explanation:
- 5 words: apple, app, application, apply, banana
- 3 queries: app, ban, cat

OUTPUT:
4
1
0

Explanation:
- Query "app": 4 words with prefix "app" → apple, app, application, apply
- Query "ban": 1 word with prefix "ban" → banana
- Query "cat": no word → 0

---

INPUT:
4 2
hello
help
world
helper
hel
wor

OUTPUT:
3
1

Explanation:
- Query "hel": 3 words (hello, help, helper)
- Query "wor": 1 word (world)
*/
