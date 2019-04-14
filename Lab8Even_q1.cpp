#include<iostream>
using namespace std;


class Node{
public:
	int data;
	//children
	Node* left;
	Node* right;
	Node* parent;
	
	Node(int value){
		data=value;
		left=NULL;
		right=NULL;
		parent=NULL;
	}
};

class BiST{
public:
	Node* root;
	int NodeCount;
	
	BiST(){
		root=NULL;
		NodeCount=0;
	}
	
	void insert(int value){
		insertHelper(root,value);
	}
	void insertHelper(Node* curr, int value){
		//base case if curr is NULL, insert there.
		if(root==NULL){
			root = new Node(value);
			NodeCount=1;
		}
		//Else compare the curr data with value
		else if(value<curr->data){
			//if value < curr data ->
			//If left is null, insert it. 
			//else move left and call insertH
			if(curr->left==NULL){
				curr->left = new Node(value);
				curr->left->parent=curr;
				NodeCount++;
			}
			else insertHelper(curr->left, value);
		}
		else{
			//else move right and call insertH
			if(curr->right==NULL) {
				curr->right = new Node(value);
				curr->right->parent=curr;
				NodeCount++;
			}
			else insertHelper(curr->right, value);
		}
	}
	
	void display(){
		display2(root);
		cout << endl;
	}
	void display2(Node* curr){
		//Base condition
		if(curr==NULL) return;
		//display left
		display2(curr->left);
		//Display current
		cout << curr->data <<",";
		//display right
		display2(curr->right);
	}
	
	Node* search(int value){
		search2(value, root);
	}
	Node* search2(int value, Node* curr){
		//if empty or at end i.e. not found
		if(curr==NULL) return curr;
		//match
		if(value==curr->data) return curr;
		//smaller
		else if(value<curr->data) return search2(value,curr->left);
		//greater
		else if(value>curr->data) return search2(value,curr->right);	
	}
	
	Node* find_min(Node* curr){
		if(curr->left==NULL) return curr;
		else find_min(curr->left);
	}
	
	void replace_with_parent(Node* A, Node* B){
		//if A is not root
		if(A!=root){
			//if A is left child: add B
			if(A->parent->left==A) A->parent->left=B;
			//if A is right child: add B  
	        else if(A->parent->right==A) A->parent->right=B;
			//connect B back  
	        if(B!=NULL) B->parent=A->parent;
			//disconnect A 
	        A->parent=NULL;  
		}
		//if root
		else  
			root=B;  
	}
	
		void delet(int value){
		//search node with the value and store
		Node* remove = search(value);
		//if not present
		if(remove==NULL){
			cout << value << " node-value is not present." << endl;
		}
		//if present
		else{
			//replacement node
			Node* replace ;
			//if the delet node has two children
			if(remove->left!=NULL and remove->right!=NULL){
				//find replacement
				replace = find_min(remove->right);
				//cout << replace->data << endl;
				//swap values
				int temp=replace->data;
				replace->data=remove->data;
				remove->data=temp;
				//remove the swaped node
				remove=replace;
				//replace_with_parent(remove,replace);
				//establish connection 
				//with left side
				//replace->left = remove->left;
				//remove->left->parent = replace;
				//if right sub tree has more children
//				if(remove->right!=replace){
//					replace->right = remove->right;
//					remove->right->parent = replace;
//				}
//				*/
			}
			//else{
				//if only left child
				if(remove->right==NULL){
					replace = remove->left;
				}
				//if only right child
				else if(remove->left==NULL){
					replace = remove->right;
				}
				//if no child, then simply delet
				//replace
				replace_with_parent(remove, replace);
				//if root is removed , replace becomes new root
				if(root == remove) root = replace;
			//}
			delete remove;
		}
	}
	
	int countNode(){
		countNode2(root);
	}
	int countNode2(Node* curr){
		if(curr==NULL)return 0;
		return 1 + countNode2(curr->left) + countNode2(curr->right);
	}
	
	int height(){
		height2(root);
	}
	int max(int a, int b){
        if (a>b) return a;
        else return b;
    }
    int height2(Node * curr){
        if (curr==NULL) return 0;
        return 1 + max(height2(curr->left),height2(curr->right));
    }
    
	int rangeSearch(int k1, int k2){
		return rangeSearch2(root, k1, k2);
		cout << endl;
	}
	int rangeSearch2(Node*curr, int k1, int k2){
		if(curr!=NULL){//if the end of the tree is not reached
            if(curr->data>k1 and curr->data<k2){//and the data in the node is within the range
           		cout<<curr->data<<", ";//it is printed
            	return (1+rangeSearch2(curr->left,k1,k2)+rangeSearch2(curr->right,k1,k2));//and counted along with those in its left subtree and the right subtree
	    	}
	    	else//otherwise
	    	return rangeSearch2(curr->left,k1,k2)+rangeSearch2(curr->right,k1,k2);//elements in the range of its left subtree and right subtree and counted 
		}
        else//if the end of the tree is reached
        return 0;//base case 
    }//emd of the function to print all elements of the tree between k1 and k2
	
};

int main(){
	BiST t1;
	
	t1.insert(10);
	t1.insert(13);
	t1.insert(5);
	t1.insert(3);
	t1.insert(7);
	t1.insert(12);
	t1.insert(14);
	t1.insert(15);
	t1.insert(1);
	t1.insert(11);
	t1.insert(6);
	t1.insert(8);
	t1.insert(4);
	t1.insert(2);
	t1.insert(9);
	t1.display();
    
    cout << "Number of Nodes = " << t1.countNode() << endl;
    cout << "Height of the tree = " << t1.height() << endl;
    cout << "Range = " << t1.rangeSearch(5,13) << endl;
    
	return 0;
}
