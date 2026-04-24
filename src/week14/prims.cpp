# include <iostream>
# include <vector>
# include <stack>
# include <map>
# include <algorithm>

using namespace std;

/**
 * Provided code
 */
bool elsort(vector<int> i, vector<int> j){
    return i[2] < j[2];
}
int findset(vector< vector<int> > ds, int node){
    return ds[1][node];
}

vector< vector<int> > unionset(vector< vector<int> > ds, int node, int node2){
    int a = findset(ds, node);
    int b = findset(ds, node2);

    if(a==b){
        return ds;
    }else{
        for(int i = 0; i < ds[1].size(); i++){
            if(ds[1][i]==a){
                ds[1][i]=b;
            }
        }
        return ds;
    }
}

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
vector <vector <int> > djikstra(vector<vector<int>>* matrix, int starting = 0, int placeholder = 9999) {
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

// Copied from representation.cpp
template <typename weight_type>
vector<vector<weight_type>> adjacency_matrix(vector<vector<int>> edges, int placeholder = -1) {
	vector<vector<weight_type>> matrix;

	int dimensions = -1;
	for (int edge = 0; edge < edges.size(); edge++) {
		if (edges[edge].size() >= 2) {// valid?
			int sizes[2] = {edges[edge][0], edges[edge][1]};
			for (int number = 0; number < 2; number++) {
				if (sizes[number] > dimensions) {
					dimensions = sizes[number];
				};
			};
		};
	};

	while (matrix.size() < dimensions + 1) {
		vector<weight_type> connections;
		while (connections.size() < dimensions + 1) {
			connections.push_back(placeholder);
		};
		matrix.push_back(connections);
	};

	for (int edge = 0; edge < edges.size(); edge++) {
		if (edges[edge].size() >= 3) {
			int source = edges[edge][0];
			int target = edges[edge][1];
			weight_type weight = edges[edge][2];

			matrix[source][target] = weight;
		}; // else, something’s wrong
	};

	return matrix;
};

/**
 * Convert a single-dimension node and edge list to an edge list.
 *
 * @param list (vector<node_type>) the combined node and edge list
 * @param width (int) the width
 * @return vector<vector<node_type>>
 * @returns the edge list
 */
template <typename node_type> vector<vector<node_type>> convert(vector<node_type> list, int width) {
	/**
	 * The number of nodes fluctuates between width - 1 and width. Also, the total number of number for each column fluctuates from width - 1 to width. However, it's on every index that is a multiple of 2 but not a multiple of 4 that we have item 0 being an edge. Furthermore, on even-number indices, the middle edges where its index > 0 and < width - 1 refers to both horizontal and vertical edges.
	 */

	// The edge list
	vector<vector<node_type>> el;

	// Split into rows
	vector<vector<node_type>> split;
	for (int indices[2] = {0, 0}; indices[0] < list.size(); indices[0]++) { // These indices refer to the position in the list and the row in groups of 4
		vector<node_type> row; // The row in the split
		int intake = width - (indices[1] % 2); // The next n items to look

		for (int position = 0; position < intake; position++) {
			row.push_back(list[indices[0]]);
			indices[0]++;
		};
		indices[0]--;
		split.push_back(row);
		indices[1]++;

		if (indices[1] >= 4) {
			indices[1] = 0; // Reset the counter
		};
	};

	// Get all horizontal and vertical edges.
	// We'll do the horizontal ones first. It happens that every 2N+1 index in a 2N row is a horizontal edge.
	for (int indices[2] = {0, 0}; indices[0] < split.size(); indices[0] += 2) {
		int minimum = 0;
		if (indices[0] % 4) {minimum = 1; };
		for (indices[1] = minimum; (indices[1] + 2) < split[indices[0]].size(); indices[1] += 2) {
			int nodes[2] = {split[indices[0]][indices[1]], split[indices[0]][indices[1] + 2]};
			for (int repeat = 0; repeat < 2; repeat++) {
				vector<node_type> edge = {nodes[repeat], nodes[1 - repeat], split[indices[0]][indices[1] + 1]};
				el.push_back(edge);
			};
		};
	};

	// Add all vertical edges.
	for (int indices[2] = {0, 0}; (indices[0] + 4) < split.size(); indices[0] += 4) {
		for (indices[1] = 0; indices[1] < split[indices[0]].size(); indices[1] += 2) {
			int nodes[2] = {split[indices[0]][indices[1]], split[indices[0] + 4][indices[1]]};
			for (int repeat = 0; repeat < 2; repeat++) {
				vector<node_type> edge = {nodes[repeat], nodes[1 - repeat], split[indices[0] + 2][indices[1]]};
				el.push_back(edge);
			};
		};
	};

	// Add all diagonal edges.
	for (int row = 0; (row + 2) < split.size(); row += 2) {
		if (row % 4 < 2) {
			for (int index = 0; (width - index) >= 2; index += 2) {
				int nodes[2] = {split[row][index], split[row + 2][index + 1]};
				for (int repeat = 0; repeat < 2; repeat++) {
					vector<node_type> edge = {nodes[repeat], nodes[1 - repeat], split[row + 1][index]};
					el.push_back(edge);
				};
			};
			for (int index = 2; index < width; index += 2) {
				int nodes[2] = {split[row][index], split[row + 2][index - 1]};
				for (int repeat = 0; repeat < 2; repeat++) {
					vector<node_type> edge = {nodes[repeat], nodes[1 - repeat], split[row + 1][index - 1]};
					el.push_back(edge);
				};
			};
		} else {
			for (int index = 1; (width - index) >= 2; index += 2) {
				int nodes[2] = {split[row][index], split[row + 2][index + 1]};
				for (int repeat = 0; repeat < 2; repeat++) {
					vector<node_type> edge = {nodes[repeat], nodes[1 - repeat], split[row + 1][index]};
					el.push_back(edge);
				};
			};
			for (int index = 1; index < width; index += 2) {
				int nodes[2] = {split[row][index], split[row + 2][index - 1]};
				for (int repeat = 0; repeat < 2; repeat++) {
					vector<node_type> edge = {nodes[repeat], nodes[1 - repeat], split[row + 1][index - 1]};
					el.push_back(edge);
				};
			};
		};
	};

	return el;
}

int main() {
	vector<vector<int>> lists = {
		{0, 13, 1, 33, 2, 53, 3, 53, 4, 64, 62, 81, 88, 10, 62, 39, 53, 51, 5, 87, 6, 25, 7, 15, 8, 92, 22, 43, 81, 58, 77, 43, 10, 96, 9, 79, 10, 95, 11, 73, 12, 93, 13, 69, 18, 96, 35, 80, 99, 96, 3, 99, 14, 58, 15, 41, 16, 6, 17, 27, 47, 62, 70, 23, 39, 88, 2, 6, 18, 67, 19, 38, 20, 21, 21, 11, 22, 7, 71, 2, 38, 1, 77, 86, 98, 2, 23, 94, 24, 80, 25, 4, 26, 25, 80, 32, 82, 61, 54, 38, 52, 14, 27, 91, 28, 75, 29, 70, 30, 17, 31, 21, 48, 13, 95, 60, 26, 39, 63, 48, 32, 94, 33, 78, 34, 46, 35, 98, 65, 82, 87, 65, 4, 65, 64, 61, 36, 75, 37, 18, 38, 76, 39, 86, 40},
		{0, 10, 1, 28, 2, 14, 3, 3, 4, 6, 5, 95, 6, 65, 7, 19, 42, 19, 79, 98, 55, 68, 73, 34, 42, 23, 92, 48, 56, 16, 8, 56, 9, 43, 10, 41, 11, 75, 12, 28, 13, 94, 14, 21, 76, 15, 63, 41, 81, 19, 41, 93, 53, 14, 97, 83, 14, 69, 15, 26, 16, 51, 17, 33, 18, 41, 19, 16, 20, 4, 21, 7, 22, 46, 40, 10, 80, 64, 19, 61, 45, 10, 24, 23, 22, 60, 31, 86, 23, 98, 24, 64, 25, 40, 26, 81, 27, 19, 28, 13, 29, 45, 80, 90, 91, 73, 46, 91, 98, 57, 45, 74, 92, 90, 86, 65, 30, 52, 31, 50, 32, 11, 33, 49, 34, 87, 35, 78, 36, 41, 37, 42, 78, 63, 63, 62, 29, 8, 52, 64, 58, 40, 45, 52, 63, 28, 38, 67, 39, 73, 40, 30, 41, 77, 42, 2, 43, 79, 44, 29, 73, 18, 29, 11, 86, 2, 4, 43, 19, 84, 4, 10, 8, 90, 45, 45, 46, 36, 47, 11, 48, 97, 49, 4, 50, 67, 51, 40, 52, 3, 51, 63, 53, 64, 84, 97, 45, 54, 77, 53, 52, 51, 59, 31, 53, 12, 54, 83, 55, 54, 56, 27, 57, 98, 58, 71, 59, 15, 60, 17, 48, 79, 11, 94, 88, 26, 32, 85, 78, 86, 93, 80, 60, 7, 61, 78, 62, 32, 63, 15, 64, 65, 65, 83, 66, 31, 67, 93, 52, 69, 69, 66, 63, 23, 20, 87, 70, 63, 16, 32, 44, 29, 68, 45, 69, 35, 70, 28, 71, 75, 72, 84, 73, 95, 74, 60, 64, 22, 57, 37, 96, 50, 26, 43, 59, 19, 56, 25, 12, 50, 75, 41, 76, 87, 77, 42, 78, 8, 79, 97, 80, 16, 81, 14, 82, 43, 20, 94, 72, 7, 92, 61, 44, 90, 68, 70, 49, 48, 89, 79, 83, 55, 84, 52, 85, 89, 86, 78, 87, 67, 88, 66, 89, 95, 99, 55, 62, 72, 16, 90, 4, 9, 70, 13, 35, 24, 88, 14, 90, 25, 91, 91, 92, 69, 93, 24, 94, 4, 95, 20, 96, 43, 97, 95, 81, 81, 94, 77, 70, 42, 90, 49, 56, 41, 41, 86, 40, 20, 98, 10, 99, 24, 100, 17, 101, 57, 102, 41, 103, 45, 104, 71, 47, 84, 15, 97, 14, 17, 31, 80, 98, 29, 5, 73, 29, 50, 105, 73, 106, 76, 107, 58, 108, 95, 109, 96, 110, 22, 111, 86, 112}
	};
	vector<int> sizes = {9, 15};
	vector<int> maximum = {40, 112};
	vector< vector<vector<int>>> els;
	vector< vector<vector<int>>> adjmats;
	vector< vector<vector<int>>> sdts; // Shortest distance tables

	for (int list_ID = 0; list_ID < lists.size(); list_ID++) {
		els.push_back(convert<int>(lists[list_ID], sizes[list_ID]));
		adjmats.push_back(adjacency_matrix<int>(els[list_ID]));

		sdts.push_back(djikstra(&(adjmats[list_ID]), 19, 9999999));

		// Kruskal's processing
		vector < vector < int > > el = els[list_ID];
	    sort(el.begin(), el.end(), elsort);
	    vector<vector <int> > mst;
	    vector<vector <int> > ds;

		for (int size = 0; ds.size() < 2; size++) {
			vector<int> row;
			for (int index = 0; index < maximum[list_ID] + 1; index++) {
				row.push_back(index);
			};
			ds.push_back(row);
		};
	    //
	    while(mst.size() < 8) {
	        for(int i = 0; i < el.size(); i++){
	            if(findset(ds, el[i][0])!= findset(ds, el[i][1])){
	                mst.push_back(el[i]);
	                ds = unionset(ds, el[i][0], el[i][1]);
	            }
	        };
	    };

		cout << "Edge List " << list_ID << ": " << endl;
		for (int edge = 0; edge < els[list_ID].size(); edge++) {
			for (int entry = 0; entry < els[list_ID][edge].size(); entry++) {
				cout << "\t";
				cout << els[list_ID][edge][entry];

				if ((entry + 1) < els[list_ID][edge].size()) {
					cout << ",";
				} else {
					cout << endl;
				};
			};
		};

		cout << "Shortest Distance Table " << list_ID << ": " << endl;
		for (int edge = 0; edge < sdts[list_ID].size(); edge++) {
			cout << "\t" << edge << "\t" << "|";
			for (int entry = 0; entry < sdts[list_ID][edge].size(); entry++) {
				cout << "\t" << sdts[list_ID][edge][entry];

				if ((entry + 1) < sdts[list_ID][edge].size()) {
					cout << ",";
				} else {
					cout << endl;
				};
			};
		};

		// Kruskal's
		cout << "Kruskal's " << list_ID << ": " << endl;
	    for(int i = 0; i < mst.size(); i++){
			cout << "\t";
	        for(int j = 0; j < 3; j++){
	            cout << mst[i][j] << "\t|\t";
	        }
	        cout << endl;
	    };
	};
};
