# include <iostream>
# include <iomanip>
# include <vector>
# include <stack>
using namespace std;

/**
 * Determine a random direction. 
 * 
 * @return int 
 */
int choose() {
	// Choose a random seed
	srand(rand());
	
	// Generate a direction
	int direction = (rand() % 3) - 1; // Get the direction
	return direction; 
};

/**
 * Randomise the container selection.  
 * 
 * @param size (int) size
 * @return (vector<int>) history of container numbers, the top being our desired
 */
stack<int> fall(int width = 7, int height = 5) {
	int position = width / 2; // Sets the middle position
	if (!(width % 2)) {position -= 1; } // Decrement odd by one
	stack<int> history; 

	int random = choose(); 
	while (history.size() < height) {
		random = choose();
		position = position + random; 
		
		// Set boundaries. 
		if (position <= 0) {position = 0; }
		else if (position >= width) {position = width - 1;};

		history.push(position);

	};

	return history; 
};

/**
 * Increment randomly. 
 * 
 * @param container 
 * @return vector<vector<int>> 
 */
vector<vector<int>> insert(vector<vector<int>> *container, int size = 1, int threshold = 99) {
	stack<int> positions = fall(); // Generate random
	int insertion = (*container).size() - 1;
	int *number = &(*container)[insertion][positions.top()]; 

	*number += size; // At position add number
	if (threshold && *number > threshold) {
		int difference = *number - threshold;
		*number = threshold; 
		
		insertion--; 
		for (bool dropped = false; !dropped && insertion >= 0; insertion--) {
			int *above = &((*container)[insertion][positions.top()]); 
			*above += difference; 
			dropped = (*above <= threshold); 

			if (!dropped) {
				difference = *above - threshold; 
				*above = threshold;
			};
		};
	};

	return *container; 
};

int main(){
	int maximum = 3000; 
	int threshold = 99;

	srand(9999);
	for(int i = 0; i < 5; i++){
		cout << rand()%3 << "|";
	};

	cout << endl;
	vector< vector<int> > container;
	vector<int> temp;

	// Initialising 5 rows by 7 columns
	cout << "Initializaing" << endl;
	for(int i = 0; i < 5; i++){
		temp = vector<int>{0,0,0,0,0,0,0};
		container.push_back(temp);
	};

	// Code for insertion
	cout << "Dropping" << endl;
	for (int count = 0; count < maximum; count++) {
		insert(&container, 1, threshold);
	};

	// Display the new container
	for(int j = 0; j < 5; j++){
		for(int k = 0; k < 7; k++){
			if (!(container[j][k])) {
				cout << "\033[2m";
			} else if (container[j][k] == threshold) {
				cout << "\033[32m";
			};

			cout << setw(3) << setfill('0') << container[j][k] << "\033[0m" << "|";
		}
		cout << endl;
	}
}