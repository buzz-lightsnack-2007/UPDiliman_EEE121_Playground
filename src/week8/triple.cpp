/**
 * @file triple.cpp
 * @date 2026-03-13
 * 
 * A linked list node that handles duplicates. 
 * 
 * @copyright Copyright (c) 2026
 * 
 */

# include<iostream>
# include <vector>
using namespace std;

template <typename dtype> 
class TripleNode {
	public:
		dtype data; // the data
		TripleNode* left; // the left node
		TripleNode* mid; // the middle node
		TripleNode* right; // the right node
		TripleNode(dtype data){
			this->data = data;
			this->left = nullptr;
			this->mid = nullptr;
			this->right = nullptr;
		};

		/**
		 * Insert a value to the tree. 
		 * 
		 * @param value (dtype) the value to insert
		 */
		TripleNode* insert(dtype value){
			TripleNode* newnode = new TripleNode(value);
			this -> insert(newnode); 
			return newnode; 
		};

		/**
		 * Inserts a node to the tree. 
		 * 
		 * @param node (TripleNode*) the node
		 */
		void insert(TripleNode* node) {
			dtype value = node->data; // The value for comparison
			
			if (value > this->data) {
				if(this->right != nullptr){
					this -> right -> insert(value);
				}else{
					this -> right = node;
				};
			} else if (value < this -> data) {
				if (this -> left != nullptr) {
					this -> left -> insert(value); 
				} else {
					this -> left = node; 
				}
			} else {
				if (this -> mid != nullptr) {
					this -> mid -> insert(node); 
				} else {
					this -> mid = node; 
				};
			}
		}

		/**
		 * Traverse through this tree. 
		 */
		void traverse(){
			if(this->left != nullptr){
				this -> left -> traverse();
			};
			
			cout << this->data << endl;

			if (this -> mid != nullptr) {
				this -> mid -> traverse(); 
			};

			if(this->right != nullptr){
				this -> right -> traverse();
			}
		};
		
		/**
		 * Traverse through this tree. 
		 * 
		 * @param ignorable (vector) the values to ignore
		 */
		void traverse(vector<dtype> ignorable){
			if(this->left != nullptr){
				this -> left -> traverse(ignorable);
			};
			
			bool found = false; 
			for (int index = 0; index < ignorable.size() && !found; index++) {
				found = (ignorable[index] == this->data);
			};

			if (!found) {
				cout << this -> data << endl;
				
				if (this -> mid != nullptr) {
					this -> mid -> traverse(); 
				};
			};

			if(this->right!= nullptr){
				this->right->traverse(ignorable);
			}
		};

		/**
		 * Traverse through this tree. 
		 * 
		 * @param ignorable (dtype) the values to ignore
		 */
		void traverse(dtype ignorable){
			vector<dtype> ignoredall{ignorable}; // Vector of values to ignore
			this->traverse(ignoredall); 
		};

		/**
		 * Find the relative path to the data. 
		 * 
		 * @param data - (dtype) search criteria
		 */
		vector<int> findpath(dtype data) {
			vector<TripleNode*> nodes = this->findpath(data, true); 
			vector<int> paths; 

			for (int index = 0; nodes.size() && index < nodes.size() - 1; index++) {
				if (nodes[index + 1] == nodes[index]->right) {
					paths.push_back(2); 
				} else if (nodes[index + 1] == nodes[index]->left) {
					paths.push_back(1); 
				}; 
			}; 

			return paths; 
		};

		/**
		 * Find the path to the data. 
		 * 
		 * @param data - (dtype) search criteria
		 * @param nodes - (bool) Fill this with any data to return the nodes, not the relative path. 
		 */
		vector<TripleNode*> findpath(dtype data, bool nodes) {
			vector<TripleNode*> paths{this}; 
			vector<TripleNode*> choice; 

			if (this -> data == data) {
				return paths; 
			} else if (data > this -> data && this -> right != nullptr) {
				choice = this -> right -> findpath(data, true); 
			} else if (data < this -> data && this -> left != nullptr) {
				choice = this -> left -> findpath(data, true); 
			} else {
				paths.pop_back(); // Replace with a null pointer to indicate not found. 
				paths.push_back(nullptr); 
			};

			for (int index = 0; choice.size() && choice.back() != nullptr && index < choice.size(); index++) {
				paths.push_back(choice[index]); 
			};
			if (paths.size() == 1 && paths.back() != nullptr) {
				paths.pop_back(); // Because it's a dead end, get rid of it
			}; 

			return paths; 
		}
};

int main() {
	TripleNode<int> root{1};
	for (int i = 0; i < 2; i++) {
		root.insert(0);
		root.insert(-10);
	};
	root.insert(-5);
	root.insert(3);
	root.insert(2);
	root.insert(4);
	root.insert(99);
	root.insert(8);
	root.insert(27);

	root.traverse();

	vector<TripleNode<int>*> path = root.findpath(8, true); 
	vector<int> path_rel = root.findpath(-10); 

	for (int i = 0; i < path.size(); i++) {
		cout << path[i] -> data; 

		if (path.size() - 1 > i) {
			cout << ", "; 
		} else {
			cout << endl; 
		}
	};
	for (int i = 0; i < path_rel.size(); i++) {
		cout << path_rel[i]; 

		if (path_rel.size() - 1 > i) {
			cout << ", "; 
		} else {
			cout << endl; 
		}
	};
}