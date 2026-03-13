# include <iostream>
using namespace std;

template <typename dtype>
class LinkedListNode{
    public:
        dtype val;
        LinkedListNode* next;
        LinkedListNode(dtype val){
            this->val = val;
            this->next = nullptr;
        }

        int access(int k, bool verbose = false){
            LinkedListNode *temp = this->next;
            while(k > 0){
				if (verbose) {
					cout << temp->val <<"->";
				};
				
                temp = temp->next;
                k--;
            };
            cout << temp->val << endl;
            return temp->val;
        }

        void insert(int k, dtype val){
            LinkedListNode *newnode = new LinkedListNode{val};
            LinkedListNode *temp = this;

            while(k > 0){
                temp = temp->next;
                k--;
            }
            newnode->next = temp->next;
            temp->next = newnode;
        }

        void deletenode(int k){
            LinkedListNode *temp = this;
            LinkedListNode *temp2 = this->next;
            while(k > 0){
                temp = temp->next;
                temp2 = temp2->next;
                k--;
            }

            temp->next = temp2->next;
            delete temp2;
        }
};

int main(){
    LinkedListNode head{0};
    LinkedListNode node1{10};
    head.insert(0,10);
    head.insert(1,12);
    head.insert(0,1234);
    head.access(2);
    head.deletenode(2);
    head.access(1);
}