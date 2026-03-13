# include <iostream>
using namespace std;

template <typename dtype>
class StackNode{
	protected: 
		StackNode* next;
		
	public:
		dtype data;
		StackNode(dtype data){
			this->data = data;
			this->next = nullptr;
		};

		StackNode* access(){
			if (!(this->next)) {return this;};

			StackNode *node = this->next;

			while (node->next) {
				node = node->next;
			}; 

			return node;
		};
		
		void insert(StackNode* data) {
			StackNode *tail = this->access(); 
			tail->next = data; 
		};
		
		StackNode* insert(dtype data) {
			StackNode *created = new StackNode{data};
			this->insert(created);
			return created; 
		};

		StackNode* remove() {
			StackNode* tail = this -> access(); 
			
			if (tail == this) {return nullptr;}; // Will not remove the only node

			StackNode* editing = this; 
			while ((editing -> next) != tail) {
				editing = editing -> next; 
			}; 

			editing -> next = nullptr; 
			return tail; 
		};
};

int main(){
	StackNode head{0};
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