# include <iostream> 
using namespace std; 

void loop1(int n) {
	for (int iteration = 0; iteration < n; iteration++) {
		cout << iteration << "\t" << "|"; 
		for (int col = 0; col < 10; col++) {
			cout << "\t" << col; 
		}; 

		cout << endl; 
	};
};

int main() {
	loop1(40);
};