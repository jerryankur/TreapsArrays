#include <bits/stdc++.h> 
using namespace std;
#ifndef max_size
#define max_size 100000
#endif
class TreapsArrays
{
public:
	class Node
	{
	public:
		int data;
		int priority;
		Node *left, *right;
		int size;
		Node(int data)
		{
			this->data=data;
			this->left=this->right=nullptr;
			this->priority=rand()%max_size;
			this->size=1;
		}
	};
	Node *root;
	int size;
	TreapsArrays()
	{
		this->root=nullptr;
		this->size=0;
	}
	void split(Node *root, Node *&l, Node *&r, int position, int preset=0)
	{
		if(!root) return void(l=r=nullptr);
		int curr=preset+(root->left?root->left->size:0)+1;
		if(position>=curr) split(root->right,root->right,r,position,curr),l=root;
		else split(root->left,l,root->left,position,preset), r=root;
		if(root) root->size=(root->left?root->left->size:0)+(root->right?root->right->size:0)+1;
	}
	void merge(Node *&root, Node *l, Node *r)
	{
		if(!l||!r) root= l?l:r;
		else if(l->priority>r->priority)
			merge(l->right,l->right,r),root=l;
		else merge(r->left,l,r->left), root=r;
		if(root) root->size=(root->left?root->left->size:0)+(root->right?root->right->size:0)+1;
	}
	void insert(int data)
	{
		Node *l, *r, *curr= new Node(data);
		split(this->root,l,r,this->size++);
		merge(this->root,l,curr);
		merge(this->root,this->root,r);
	}
	void remove(int position)
	{
		Node *l,*m,*r;
		split(this->root,l,r,position-1);
		split(r,m,r,1);
		merge(this->root,l,r);
	}
	int atPosition(int position, Node *root=nullptr)
	{
		if(!root) root=this->root;
		for(int preset=0,curr;root;){
			curr= preset+(root->left?root->left->size:0)+1;
			if(position==curr) return root->data;
			if(position<curr) root=root->left;
			else{
				root=root->right;
				preset=curr;
			}
		}
		return int(INFINITY);
	}
	void inorderPrint(Node *root=nullptr)
	{
		if(!root) if(this->root) root=this->root; else return;
		if(root->left) inorderPrint(root->left);
		cout<<root->data<<' '<<root->priority<<' '<<root->size<<endl;
		if(root->right) inorderPrint(root->right);
	}
	void levelorderPrint(Node *root=nullptr)
	{
		if(!root) if(this->root) root=this->root; else return;
		queue<Node *>q;
		q.push(root);
		while(!q.empty())
		{
			root= q.front();
			cout<<root->data<<' '<<root->priority<<' '<<root->size<<endl;
			q.pop();
			if(root->left) q.push(root->left);
			if(root->right) q.push(root->right);
		}
	}
};
int main()
{
	int x,n;
	long a;
	cin>>n;
	TreapsArrays arr;
	for(x=0;x<n;++x)
	{
		cin>>a;
		arr.insert(a);
	}
//	arr.inorderPrint();
//	arr.levelorderPrint();
	for(x=1;x<=n;++x)
	{
		cout<<arr.atPosition(x)<<' ';
	}
}
