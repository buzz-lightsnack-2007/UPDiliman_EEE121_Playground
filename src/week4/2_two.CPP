# include <iostream> 
using namespace std; 

void top(int n) {
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			cout << col << "\t"; 
		};
		cout << endl;
	};
};

void bottom(int n) {
	n = n - 5; 
	for (int counter = 0; n && counter < 5; counter++) {
		n += 1; // Attempt restoring to previous state
	}; 
	n = abs(n); 
	int iterations = n; 
	cout << iterations; 
	
	for (int x =1; x <= iterations; x++) {		
		for (int y =1; y <= iterations; y++) {
			for (int z =1; z <= iterations; z++) {
				cout << "(" << x << ", " << y << ", " << z << ")"; 
			};
		};
	};
};

int main() {
	top(5); 
	bottom(5); 
}