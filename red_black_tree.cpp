#include <iostream>

using namespace std;


struct Node {
	int data; // hold the value
	Node *parent; // pointer to the parent
	Node *left; // pointer to left child
	Node *right; // pointer to right child
	int color; // 1 -> Red, 0 -> Black
};

typedef Node *NodePtr;


class RBTree {
private:
	NodePtr root;
	NodePtr NIL;

	

	// fix the rb tree modified by the delete operation
	void RBDeleteFixUp(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == 0) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == 1) {
					
					s->color = 0;
					x->parent->color = 1;
					LeftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					
					s->color = 1;
					x = x->parent;
				} else {
					if (s->right->color == 0) {
						
						s->left->color = 0;
						s->color = 1;
						RightRotate(s);
						s = x->parent->right;
					} 

					
					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					LeftRotate(x->parent);
					x = root;
				}
			} else {
				s = x->parent->left;
				if (s->color == 1) {
					
					s->color = 0;
					x->parent->color = 1;
					RightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) {
					
					s->color = 1;
					x = x->parent;
				} else {
					if (s->left->color == 0) {
						
						s->right->color = 0;
						s->color = 1;
						LeftRotate(s);
						s = x->parent->left;
					} 

					
					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					RightRotate(x->parent);
					x = root;
				}
			} 
		}
		x->color = 0;
	}


	void RBTransplant(NodePtr u, NodePtr v){
		if (u->parent == NULL) {
			root = v;
		} else if (u == u->parent->left){
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		
		v->parent = u->parent;
		
	}

	
	
	// fix the red-black tree
	void RBInsertFixUp(NodePtr k){
		NodePtr u;
		if(k==root)
     {
         k->color=0;
         return;
     }
		while (k->parent!=NULL && k->parent->color == 1) {
			
			if (k->parent == k->parent->parent->right) {
				
				u = k->parent->parent->left; 
				if (u->color == 1) {
					
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} 
				
				else if (k == k->parent->left) {
						
						k = k->parent;
						RightRotate(k);
				}
				else{
					k->parent->color = 0;
					k->parent->parent->color = 1;
					LeftRotate(k->parent->parent);
				}
			 
			} else {
				
				u = k->parent->parent->right; 

				if (u->color == 1) {
					
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;	
				} 
				
				else if (k == k->parent->right) {
						
						k = k->parent;
						LeftRotate(k);
				}
				else{
					k->parent->color = 0;
					k->parent->parent->color = 1;
					RightRotate(k->parent->parent);
				}
			
			}
			
		}
		root->color = 0;
	}






void display(NodePtr ptr, int level)
{
    int i;
    if (ptr != NIL)
    {
        display(ptr->right, level+1);
        cout<<endl;
        if (ptr == root)
            cout<<"Root->:";
        else
        {
            for (i = 0;i < level;i++)
                cout<<"       ";
	    }
        if (ptr->color == 0)
		{
        cout<<ptr->data<<"(B)";
		}
		   
        else
		{
        cout<<"<"<<ptr->data<<">"<<"(R)";
		}
       display(ptr->left, level+1);

        

    }
}

NodePtr SearchNode(NodePtr node, int key) {
		if (node == NIL || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return SearchNode(node->left, key);
		} 
		else{
		return SearchNode(node->right, key);
		}
		
	}



public:
	RBTree() {
		NIL = new Node;
		NIL->color = 0;
		NIL->left = NULL;
		NIL->right = NULL;
		root = NIL;
	}

	

	// search the tree for the key and return the corresponding node
	void searchTree(int k) {
		 if(root==NIL)
         {
           cout<<"\nEmpty Tree." ;
           return ;
         }
		NodePtr v= SearchNode(this->root, k);

		if (v == NIL) {
			cout<<"Element Not Found in the tree"<<endl;
			return;
		} 
		else{
            cout<<"\n NODE FOUND: ";
                cout<<"\n Key: "<<v->data<<endl;
				if(v->color==0){
					cout<<" Colour: BLACK"<<endl;
				}else{
					cout<<" Colour: RED"<<endl;

				}
               

		}

	}

	// find the node with the minimum key
	NodePtr minimum(NodePtr node) {
		while (node->left != NIL) {
			node = node->left;
		}
		return node;
	}

	// find the node with the maximum key
	NodePtr maximum(NodePtr node) {
		while (node->right != NIL) {
			node = node->right;
		}
		return node;
	}

    NodePtr FindMaximum() {
		
		return maximum(this->root);
	}
    
	NodePtr FindMinimum() {
		
		return minimum(this->root);
	}
    

	// rotate left at node x
	void LeftRotate(NodePtr x) {
		if(x->right==NULL){
           return ;
		}
		else{
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != NIL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
		}
	}

	// rotate right at node x
	void RightRotate(NodePtr x) {
     if(x->left==NULL){
          return ;
		  
	 }

     else{
		NodePtr y = x->left;
		if (y->right != NIL) {
		x->left = y->right;
			y->right->parent = x;
		}
		else{
                 x->left=NIL;
		}
		y->parent = x->parent;
		if (x->parent == NULL) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
     }
	}

	// Insert the key to the tree 
	void Insert(int key) {
		
		NodePtr node = new Node;
		node->parent = NULL;
		node->data = key;
		node->left = NIL;
		node->right = NIL;
		node->color = 1; 

		NodePtr y = NULL;
		NodePtr x = this->root;


	
		while (x != NIL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		
		node->parent = y;
		if (y == NULL) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}
		
		RBInsertFixUp(node);
	}

	


//delete node from the rbtree
void deleteNode(int key) {

		 if(root==NIL)
     {
           cout<<"\nEmpty Tree." ;
           return ;
     }
		
		
		NodePtr z = SearchNode(root,key);
		NodePtr x, y;
		

		if (z == NIL) {
			cout<<"Element Not Found in the tree"<<endl;
			return;
		} 

		y = z;
		int y_original_color = y->color;
		if (z->left == NIL) {
			x = z->right;
			RBTransplant(z, z->right);
		} else if (z->right == NIL) {
			x = z->left;
			RBTransplant(z, z->left);
		} else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			} else {
				RBTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			RBTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0){
			RBDeleteFixUp(x);
		}

	}

	// print the RBtree 
	void PrintTree() {
	    if (root) {
    	
		display(this->root,1);
	
	    }
	}

};

int main() {
	RBTree rbt;
	 rbt.Insert(8);
	 rbt.Insert(5);
	 rbt.Insert(15);
	 rbt.Insert(12);
	 rbt.Insert(19);
	 rbt.Insert(9);
	 rbt.Insert(13);
	 rbt.Insert(23);
	 int ch,y=0;
	 while(y!=1){
                
                cout<<"\n\n 1. Insert in the tree ";
                cout<<"\n 2. Delete a node from the tree";
                cout<<"\n 3. Search for an element in the tree";
                cout<<"\n 4. Display the tree ";
                cout<<"\n 5. Find maximum and minimum value of the tree ";
                cout<<"\n 6. Exit " ;
                cout<<"\nEnter Your Choice: ";
                cin>>ch;
                switch(ch)
                {
                          case 1 : int z;
                                   cout<<"\nEnter key of the node to be inserted: ";
                                   cin>>z;
						           rbt.Insert(z);
                                   cout<<"\nNode Inserted.\n";
	                               rbt.PrintTree();
                                   break;
                          case 2 : 
						           int a;
                                   cout<<"\nEnter the value of the node to be deleted: ";
                                   cin>>a;
								   rbt.deleteNode(a);
	                               rbt.PrintTree();
                                   break;
                          case 3 : 
						           int c;
                                   cout<<"\n Enter key of the node to be searched: ";
                                   cin>>c;
						           rbt.searchTree(c);
                                   break;
                          case 4 : rbt.PrintTree();
                                   break;
						  case 5:  cout<<"\nMinimum value - "<<rbt.FindMinimum()->data<<"  color= ";
						            if(rbt.FindMinimum()->color==0){
										cout<<"BLACK";
									}
									else{
										cout<<"RED";
									}
                                   cout<<"\nMaximum value - "<<rbt.FindMaximum()->data<<"  color= ";	

								   if(rbt.FindMaximum()->color==0){
										cout<<"BLACK";
									}
									else{
										cout<<"RED";
									}
									break;   
                          case 6 : y=1;
                                   break;
                          default : cout<<"\nEnter a Valid Choice.";
                }
                cout<<endl;

    }
	return 0;
}