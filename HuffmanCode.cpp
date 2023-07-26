

/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

struct node 
{
    char ch;
    int freq;
    node *left=NULL,*right=NULL;
   
};


 node* get(char c,int f,node *l , node * r)
    {   node*n=new node();
      n->  ch=c;
      n->  freq=f;
      n->  left=l;
      n->  right=r;
        return n;
    }

void encode(node*root,string str, unordered_map<char,string>&huffmancode)
{
    if(root==NULL) return;
    
    if(!root->right and !root->left)// found leaf
    {
        huffmancode[root->ch]=str;
    }
     encode(root->left,str+"0",huffmancode);
     encode(root->right,str+"1",huffmancode);

}
void decode(node*root,int &top_index,string str )
{//  cout<<"enteresd"<<endl;
    if(root==NULL) return;
    
    if(!root->left and !root->right)
    {
        cout<<root->ch;
        return;
    }
    top_index++;
    if(str[top_index]=='0')
     decode(root->left,top_index,str);
     else
     decode(root->right,top_index,str);

    
}
void buildhufftree(string s)
{
    unordered_map<char,int>freq;
   
    for(char &ch:s)freq[ch]++;
    //store leaf node
    // priority_queue<node*,vector<node*>,greater<node*>>pq ;
    priority_queue <node*, vector<node*>, greater<node*>> pq;
    
    for(auto &i:freq)
    {  // cout<<"pushed "<<i.first<<" "<<i.second<<endl;
        pq.push( get(i.first,i.second,NULL,NULL));
        
    }
    
    
    while(pq.size()!=1)
    {
        
        node*left=pq.top(); pq.pop();
        node*right=pq.top();  pq.pop();
        int sum=left->freq   +   right->freq;
        pq.push(get('\0',sum,left,right));
    }
    
    node*root=pq.top();
    node*r=root;


//huffman code storing
    unordered_map<char,string>huffmancode;
    encode(root,"",huffmancode);
    
    cout<<"huffmancode are :"<<endl;
    for(auto &i:huffmancode)
    {
        cout<<i.first<<" "<<i.second<<endl;
        
        
    }
    cout<<"Orignal string is :  "<<s<<endl;
    
    string str="";
    for(char &c:s)
    {
        str+=huffmancode[c];
    }
    cout<<"Encoded string is:   "<<str<<endl;
    //travversing huffman tree to decode
    
    int top_index=   -1;
    cout<<"Decoded string is :";
    root=r;
    // cout<<"str "<<str.size()<<endl;
    // cout<<top_index<<endl;
    // if(top_index<str.size())cout<<"yes"<<endl;
    while(top_index<(int)str.size()-2)
    {
        //cout<<"calling";
        decode(root,top_index,str);
    }
    
}

int main()
{
string s="Huffman coding is a data compression algorithm.";
buildhufftree(s);


    return 0;
}
