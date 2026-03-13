# include <iostream>
using namespace std;

template <typename dtype>
class QueueNode {
	protected: 
		QueueNode* next; 
	
	public: 
		dtype data; 
		QueueNode(dtype data) {
			this->data = data;
			this->next = nullptr;
		};

		QueueNode* access(){
			if (!(this->next)) {return this;};

			QueueNode *node = this->next;
			while (node->next) {node = node->next;}; 

			return node;
		};

		QueueNode* remove() {
			QueueNode* tail = this -> access(); 
			
			if (tail == this) {return nullptr;}; // Will not remove the only node

			QueueNode* editing = this; 
			while ((editing -> next) != tail) {
				editing = editing -> next; 
			}; 

			editing -> next = nullptr; 
			return tail; 
		};

		void insert(QueueNode* data) {
			data->next = this->next; 
			this->next = data; 
		};
		
		QueueNode* insert(dtype data) {
			// The created queue node, containing the current data
			QueueNode *created = new QueueNode{data};  // Copy the current node's data
			this -> insert(created);

			return this -> next; 
		};
};

int main(){
	QueueNode head{0};
	head.insert(99);
	head.insert(334342);
	head.insert(9999999);
	head.remove();
	cout << head.access() -> data << endl; 
	head.remove();
	cout << head.access() -> data << endl; 
	head.remove();
	cout << head.access() -> data << endl; 
}