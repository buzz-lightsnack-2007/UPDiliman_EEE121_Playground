# include <iostream>
# include <vector>
# include <map>
using namespace std;

//Will be helpful when used with: https://cplusplus.com/reference/algorithm/sort/
bool pqsort(vector<int> i, vector<int> j){
	return i[1] < j[1];
};

//What does this do?
void print2d(vector< vector<int> > v2d, string info = "default"){
	cout << info << endl;
	for(int i = 0; i < v2d.size(); i ++){
		for(int j = 0; j < v2d[i].size(); j++){
			cout << v2d[i][j]<<"|";
		}
		cout <<endl;
	}
	cout <<"|||||||||||||"<<endl;
};

//How is this different from printst
void printst(vector< vector<int> > v2d, string info = "default"){
	cout << info << endl;
	for(int i = 0; i < v2d.size(); i ++){
		cout << i <<"||";
		for(int j = 0; j < v2d[i].size(); j++){
			cout <<v2d[i][j]<<"|";
		}
		cout <<endl;
	}
	cout <<"|||||||||||||"<<endl;
}

/**
 * Djikstra’s algorithm
 * Get the shortest distance from a source node to any node.
 *
 * @param matrix (vector<vector<int>> *) - the adjacency matrix
 * @param starting (int) - the starting item
 * @param placeholder (int) - the placeholder value
 */
vector <vector <int> > djikstra(vector<vector<int>>* matrix, int starting = 0, int placeholder = 999) {
	vector <vector <int> > pq; // the priority queue
	vector<vector<int> > sdt; // the shortest distance table
	map<int, bool> visited; // the visited
	int selected = abs(starting);

	// Initialise the SDT and the priority queue.
	for (int item = 0; item < (*matrix).size(); item++){
		if (item == starting) {
			pq.push_back({item, 0}); // Add this to the priority queue
			sdt.push_back({0, item}); // Set the SD table row to 0 (for distance) and itself (for previous node)
		} else {
			pq.push_back({item, placeholder});
			sdt.push_back({placeholder, -1}); // Previous column to -1 since not visited yet
		};
	};
	// printst(sdt);

	// Initialize the visited map.
	for(int i = 0; i < (*matrix).size(); i++){
		visited[i] = false;
	};

	while (pq.size()) { // While the priority queue isn’t empty, find the smallest item
		int smallest = -1; // the smallest item
		int priority = placeholder; // the current priority
		int index = -1; // the index

		for (int entry = 0; entry < pq.size(); entry++) {
			if (smallest < 0 || pq[entry][1] < priority) { // then update the priority and the smallest value
				smallest = pq[entry][0];
				priority = pq[entry][1];
				index = entry;
			};
		};

		vector<int>* current = &((*matrix)[smallest]);
		for (int neighbor = 0; neighbor < (*current).size(); neighbor++) {
			if (((*current)[neighbor] >= 0) && !(visited[neighbor]) && neighbor != smallest) {
				if (sdt[smallest][0] + (*current)[neighbor] < sdt[neighbor][0]) {
					sdt[neighbor][0] = sdt[smallest][0] + (*current)[neighbor]; // Set the shortest distance table
					sdt[neighbor][1] = smallest;

					// Update the priority queue
					for (int entry = 0; entry < pq.size(); entry++) {
						if (pq[entry][0] == neighbor) {
							pq[entry][1] = sdt[neighbor][0]; break;
						};
					};
				};
			};
		};

		// Dequeue and mark as seen
		visited[smallest] = true;
		pq.erase(pq.begin() + index);
	};
	return sdt;
};

int main(){

	//Start node is set to 1 you may want to change this as needed
	int start = 1;
	//You will need to initialize adjmat.
	//The entries should be the distance to the neighboring desination node(column)
	//-1 will be used to indicate no connection

	//Example we had in class.
	//Is it necessary to change the diagonal to 0 indicating 0 distance to self?
	vector < vector < vector<int>>> matrices = {
		{
			{-1,-1,6,3,-1},
			{3,-1,-1,-1,-1},
			{-1,-1,-1,2,-1},
			{-1,1,1,-1,-1},
			{-1,4,-1,2,-1},
		},
		{
			{-1, 1, 9},
			{1, -1, 1},
			{9, 1, -1}
		},
		{
			{-1, 96, 4, 99},
			{0, -1, 1, 3},
			{4, 1, -1, 5},
			{99, 3, 5, -1}
		},
		{
			{-1, 96, 4, 1},
			{0, -1, 1, 3},
			{4, 1, -1, 5},
			{1, 3, 5, -1}
		}
	};

	for (int matrix = 0; matrix < matrices.size(); matrix++) {
		vector<vector<int>> st = djikstra(&(matrices[matrix]));
		printst(st);
	};
}
