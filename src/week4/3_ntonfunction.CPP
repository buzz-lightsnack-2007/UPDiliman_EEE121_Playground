# include <iostream> 
using namespace std; 

int nton(int n) {
	if (n <= 1) {return n;};
	int counter = 0; 

	for (int iteration = 0; iteration < n; iteration++) {
		counter += nton(n-1); 
	};

	return counter; 
}

int main() {
	cout << nton(10) << endl;
};