# include <iostream> 
using namespace std; 

/**
 * Design two `O(n)` functions with different runtime steps. One must have longer runtime when the input is less than 5. 
 */

void columns(int n) {
	cout << "\t" << "|";
	for (int i = 1; i<=n; i++) {
		cout << "\t" << i; 
	};
	cout << endl; 
};

void rows(int n) {
	if (n >= 5) {
		for (int i = 1; i<=n; i++) {
			cout << i << "\t" << "|" << endl; 
		};
	};
};

int main() {
	int size = 4;
	columns(size); 
	rows(size);
}