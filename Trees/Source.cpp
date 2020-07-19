#include <iostream>
using namespace std;

class chunk {
public:
	int value;
	chunk* left;
	chunk* right;

	chunk() {
		value = 0;
		left = NULL;
		right = NULL;
	}

};
class BST {
public:
	chunk* root;
	BST() {
		root = NULL;
	}
	void add(int x){
		if (root == NULL) {
			root = new chunk;
			root->value = x;
			cout << "Just added: " << x << endl;
			return;
		}
		chunk* slow;
		chunk* fast;
		slow = fast = root;

		while (fast != NULL) {
			if (x < fast->value) {
				slow = fast;
				fast = fast->left;
			}
			else if (x > fast->value) {
				slow = fast;
				fast = fast->right;
				
			}
			else {
				cout << "No duplicate numbers" << endl;
				return;
			}
		}
		if (x < slow->value) {
			slow->left = new chunk;
			slow->left->value = x;
		}
		else {
			slow->right = new chunk;
			slow->right->value = x;
		}
		cout << "Just added: " << x << endl;
	}
	bool search(int key, chunk * start) {
		if (start == NULL) {
			cout << "Couldn't find value" << endl;
			return false;
		}
		else {
			if (key == start->value) {
				cout << "Value found in tree" << endl;
				return true;
			}
			else if (key < start->value) {
				search(key, start->left);
			}
			else {
				search(key, start->right);
			}
		}
	}
	void preorder(chunk * start) {
		if (start == NULL) {
			return;
		}
		else {
			cout << start->value << endl;
			preorder(start->left);
			preorder(start->right);
		}
	}
	void postorder(chunk* start) {
		if (start == NULL) {
			return;
		}
		else {
			postorder(start->left);
			postorder(start->right);
			cout << start->value << endl;
		}
	}
	void inorder(chunk* start) {
		if (start == NULL) {
			return;
		}
		else {
			inorder(start->left);
			cout << start->value << endl;
			inorder(start->right);
		}
	}
	void deletenode(int key) {
		//search -> classify -> delete
		if (root == NULL) {
			cout << "no tree" << endl;
			return;
		}
		chunk* slow;
		chunk* fast;
		slow = root;
		fast = root;

		while (fast != NULL && fast->value != key) {
			if (key < fast->value) {
				slow = fast;
				fast = fast->left;
			}
			else {
				slow = fast;
				fast = fast->right;
			}
		}
		if (fast == NULL) {
			cout << "node doesnt exist" << endl;
			return;
		}
		if (fast->left == NULL && fast->right == NULL) {
			cout << "case 1" << endl;
			if (slow->right == fast) {
				slow->right = NULL;
				cout << "deleting: " << fast->value << endl;
				delete fast;
				
			}
			else {
				slow->left = NULL;
				cout << "deleting: " << fast->value << endl;
				delete fast;
				
			}
		}
		else if((fast->left == NULL && fast->right != NULL) || (fast->left != NULL && fast->right == NULL)) {
			cout << "case 2" << endl;
			
			if (slow->right == fast && fast->left == NULL) {
				slow->right = fast->right;
				cout << "deleting: " << fast->value << endl;
				delete fast;
			}
			else if(slow->right == fast && fast->right == NULL) {
				slow->right = fast->left;
				cout << "deleting: " << fast->value << endl;
				delete fast;

			}
			else if (slow->left == fast && fast->left == NULL) {
				slow->left = fast->right;
				cout << "deleting: " << fast->value << endl;
				delete fast;

			}
			else if (slow->left == fast && fast->right == NULL) {
				slow->left = fast->left;
				cout << "deleting: " << fast->value << endl;
				delete fast;
			}
		}
		else{
			cout << "case 3" << endl;
			chunk* third;
			chunk* fourth;
			fourth = slow;
			third = fast;
			slow = fast;
			fast = fast->right;
			if (fast->left == NULL) {
				if (fourth->right->value == slow->value) {
					slow->value = fast->value;
					slow->right = fast->right;
					fourth->right = slow;
					delete fast;
				}
				else {
					slow->value = fast->value;
					slow->right = fast->right;
					fourth->left = slow;
					delete fast;
				}
			}
			else if (fast->left != NULL) {
				while (fast->left != NULL) {
					third = fast;
					fast = fast->left;
				}
				cout << "replacing " << slow->value << " with " << fast->value << endl;
				if (fourth->right->value == slow->value) {
					slow->value = fast->value;
					if (fast->right == NULL) {
						third->left = NULL;
						delete fast;
					}
					else {
						third->left = fast->right;
						delete fast;
					}
					fourth->right = slow;
				}
				else {
					slow->value = fast->value;
					if (fast->right == NULL) {
						third->left = NULL;
						delete fast;
					}
					else {
						third->left = fast->right;
						delete fast;
					}
					fourth->left = slow;
				}
			}
		}
	}
};

int main() {
	BST tree;
	/*tree.add(30);
	tree.add(15);
	tree.add(60);
	tree.add(7);
	tree.add(22);
	tree.add(45);
	tree.add(75);
	tree.add(17);
	tree.add(27);
	tree.add(65);*/

	while (1) {
		cout << "press 1 to add a node" << endl;
		cout << "press 2 to delete a node" << endl;
		cout << "press 3 for preorder display" << endl;
		cout << "press 4 for inorder display" << endl;
		cout << "press 5 for postorder display" << endl;
		cout << "press 6 to search for a value" << endl;
		cout << "press 7 to exit" << endl;
		int x;
		cin >> x;
		switch (x) {
		case 1:
			int value;
			cout << "What value to add?" << endl;
			cin >> value;
			tree.add(value);
			break;
		case 2:
			int dvalue;
			cout << "What value to delete?" << endl;
			cin >> dvalue;
			tree.deletenode(dvalue);
			break;
		case 3:
			tree.preorder(tree.root);
			break;
		case 4:
			tree.inorder(tree.root);
			break;
		case 5:
			tree.postorder(tree.root);
			break;
		case 6:
			int svalue;
			cout << "What value to search for?" << endl;
			cin >> svalue;
			tree.search(svalue,tree.root);
			break;
		case 7:
			exit(1);
			break;
		}
	}
}
