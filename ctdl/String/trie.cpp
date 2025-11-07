#include<bits/stdc++.h>
using namespace std;
#define mask(n) (1LL<<(n))
#define checkBit(bit,n) ((n) & mask(bit))
#define flipBit(bit,n) ((n) ^ mask(bit))
#define cntBit(n) __builtin_popcount(n)
#define fastIO ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
#define ll long long
#define repu(i,a,b)  for(int i=a;i<=b;i++)  // vòng lặp tăng từ a đến b
#define repd(i,a,b)  for(int i=a;i>=b;i--)  // vòng lặp giảm từ a đến b

struct Trie{
    struct Node
    {
        Node* child[26];  // mảng 26 con trỏ tương ứng 26 chữ cái a-z
        int cnt;          // đếm số từ đi qua node này
        int exist;        // đếm số từ kết thúc tại node này
        
        Node(){
            for (int i=0;i<26;i++)
                child[i]=NULL;  // khởi tạo tất cả con trỏ = NULL
            
            exist=cnt=0;  // khởi tạo các biến đếm = 0
        }
    };

    Node* root;  // node gốc của Trie
    
    Trie(){
        root=new Node();  // khởi tạo node gốc
    }

    // Thêm một chuỗi vào Trie
    void add_string(string s){
        Node* p=root;  // bắt đầu từ root
        
        for (auto f:s){  // duyệt qua từng ký tự
            int c=f-'a';  // chuyển ký tự thành chỉ số (0-25)

            if (p->child[c]==NULL) 
                p->child[c]=new Node();  // tạo node mới nếu chưa tồn tại
            
            p=p->child[c];  // di chuyển xuống node con
            p->cnt++;       // tăng số từ đi qua node này
        }
        p->exist++;  // đánh dấu có từ kết thúc tại đây
    }

    // Xóa chuỗi đệ quy (hàm phụ trợ)
    bool delete_string_recursive(Node* p,string s,int i){
        if (i!=s.size()){
            int c=s[i]-'a';
            // Gọi đệ quy cho ký tự tiếp theo
            bool is_child_deleted=delete_string_recursive(p->child[c],s,i+1);
            
            if (is_child_deleted) 
                p->child[c]=NULL;  // xóa con trỏ nếu node con đã bị xóa
        }
        else 
            p->exist--;  // giảm số từ kết thúc tại node này

        if (p!=root){
            p->cnt--;  // giảm số từ đi qua node này
            
            if (p->cnt==0){  // nếu không còn từ nào đi qua
                delete(p);   // giải phóng bộ nhớ
                return true; // báo node cha xóa con trỏ đến node này
            }
        }
        
        return false;
    }

    // Xóa một chuỗi khỏi Trie
    void delete_string(string s){
        if (!find_string(s)) return;  // kiểm tra chuỗi có tồn tại không
        delete_string_recursive(root,s,0);
    }

    // Tìm kiếm một chuỗi trong Trie
    bool find_string(string s){
        Node *p=root;

        for (auto f:s){
            int c=f-'a';

            if (p->child[c]==NULL)
return 0;  // không tìm thấy đường đi

            p=p->child[c];
        }

        return (p->exist!=0);  // trả về true nếu có từ kết thúc tại đây
    }

    // Đếm số từ có tiền tố là s
    int prefix_cnt(string s){
        Node *p=root;

        for (auto f:s){  // duyệt theo tiền tố
            int c=f-'a';

            if (p->child[c]==NULL) 
                return 0;  // không có từ nào có tiền tố này

            p=p->child[c];
        }

        return p->cnt;  // trả về số từ đi qua node cuối của tiền tố
    }
};

int main()
{
    // fastIO   
    int n,q;
    cin>>n>>q;  // đọc số từ và số truy vấn

    Trie *tr=new Trie();  // khởi tạo Trie
    
    string tmp;
    repu(i,1,n){
        cin>>tmp;
        tr->add_string(tmp);  // thêm n từ vào Trie
    }
    
    repu(i,1,q){
        cin>>tmp;
        cout<<tr->prefix_cnt(tmp)<<"\n";  // trả lời q truy vấn
    }
}

/*
VÍ DỤ INPUT/OUTPUT:

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

Giải thích input:
- 5 từ trong TODO list: apple, app, application, apply, banana
- 3 truy vấn: app, ban, cat

OUTPUT:
4
1
0

Giải thích output:
- Query "app": có 4 từ có tiền tố "app" là: apple, app, application, apply → in ra 4
- Query "ban": có 1 từ có tiền tố "ban" là: banana → in ra 1
- Query "cat": không có từ nào có tiền tố "cat" → in ra 0

---

VÍ DỤ 2:

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

Giải thích:
- Query "hel": có 3 từ (hello, help, helper) có tiền tố "hel" → in ra 3
- Query "wor": có 1 từ (world) có tiền tố "wor" → in ra 1
*/
