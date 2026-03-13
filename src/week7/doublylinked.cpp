# include <iostream>
using namespace std; 

template <typename dtype>
class DoubleLinkedListNode {
	public: 
		dtype value; 
		DoubleLinkedListNode* right; 
		DoubleLinkedListNode* left; 
		DoubleLinkedListNode(dtype value, DoubleLinkedListNode* left = nullptr, DoubleLinkedListNode* right = nullptr) {
			this->value = value; 
			this->left = left; 
			this->right = right;
		};

		/**
		 * Select an item within the linked list, relative to the current node
		 * 
		 * @param offset 
		 * @return (DoubleLinkedListNode*) the node 
		 */
		DoubleLinkedListNode* access_front(int offset) {
			DoubleLinkedListNode* node = this; 
			
			while (offset) {
				if (offset > 0) {
					if (node->right) {
						node = node->right; 
						offset--; 
					} else {
						break; 
					}
				} else if (offset < 0 && node->left) {
					if (node->left) {
						node = node->left; 
						offset++; 
					} else {
						break; 
					};
				};
			};

			// Null pointer checking
			if ((offset > 0 && node->right == nullptr) || (offset < 0 && node->left == nullptr)) {
				return nullptr; 
			};
			return node; 
		};

		DoubleLinkedListNode* access_back(int offset) {
			DoubleLinkedListNode* node = this; 
			while (node->right) {
				node = node->right; 
			};
			offset = abs(offset); 

			return node->access_front(-offset);
		}

		bool insert_front(dtype data, int offset = 0) {
			DoubleLinkedListNode *created = new DoubleLinkedListNode{data};  // Created node out of data
			return this->insert_front(created, offset);
		}

		bool insert_back(dtype data, int offset = 0) {
			return this->access_back(0)->insert_front(data, abs(offset));
		}

		bool insert_front(DoubleLinkedListNode* appendable, int offset = 0) {
			if (!offset) {
				if (this->right && !(this->left)) {
					offset = 1; 
				} else if (this->left && !(this->right)) {
					offset = -1; 
				} else {
					return false; // not properly configured 
				};
			};

			DoubleLinkedListNode* node = this; 
			
			// Adjust the offset for it to become the target
			// Find the correct node to insert to. 
			if (offset > 0) {
				node = this->access_front(offset - 1);
			} else if (offset < 0) {
				node = this->access_front(offset + 1);
			}; 

			if (!node) {return false; }

			if (offset < 0) {
				appendable->right = node; 

				if (node->left) { // Modify the left
					appendable->left = node->left; 
					node->left->right = appendable;
				};

				node->left = appendable; 
			} else if (offset > 0) {
				appendable->left = node; 

				if (node->right) { // Modify the right
					appendable->right = node->right; 	
					node->right->left = appendable; 
				};

				node->right = appendable; 
			};
			return true; 
		};

		bool insert_back(DoubleLinkedListNode* appendable, int offset = 0) {
			return this->access_back(0)->insert_front(appendable, -abs(offset)); 
		};

		DoubleLinkedListNode* remove_front(int offset = 0) {
			if (!offset) {
				if (this->right && !(this->left)) {
					offset = 1; 
				} else if (this->left && !(this->right)) {
					offset = -1; 
				} else {
					return nullptr; 
				}
			};

			if (offset == 0) {return nullptr;} // Can not delete itself
			
			DoubleLinkedListNode* deletion = this->access_front(offset); // Look for the item to delete. 

			if (deletion->left && deletion->right) { // Skip this node
				deletion->left->right = deletion->right; 
				deletion->right->left = deletion->left; 
			} else if (deletion->left) {
				deletion->left->right = nullptr; // There's nothing on the right
			} else if (deletion->right) {
				deletion->right->left = nullptr; // There's nothing on the left
			};
			
			return deletion; 
		};

		DoubleLinkedListNode* remove_back(int offset = 0) {
			return this->access_back(0)->remove_front(-abs(offset));
		};
};

int main(){
	DoubleLinkedListNode head{0};
	DoubleLinkedListNode tail{123456789, &head};
	head.right = &tail; // Connect the head to the tail

	head.insert_front(99);
	head.insert_front(334342);
	head.insert_back(9999999);
	
	DoubleLinkedListNode<int>* node = nullptr; 
	while (!node || node->right) {
		if (!node) {node = &head;} else {node = node->right;};

		cout << node->value;
		if (node->right) {
			cout << " -> ";
		};
	};
	cout << endl;

	node = nullptr; 
	while (!node || node->left) {
		if (!node) {node = &tail;} else {node = node->left;};

		cout << node->value << " -> ";
	};
	cout << endl;

	head.remove_back();
	head.remove_back();
	head.remove_front();

	node = nullptr; 
	while (!node || node->left) {
		if (!node) {node = &tail;} else {node = node->left;};

		cout << node->value << " -> ";
	};
	cout << endl;
};