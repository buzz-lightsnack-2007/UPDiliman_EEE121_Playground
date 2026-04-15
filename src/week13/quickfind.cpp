// sample discussion code, modified

# include <iostream>
# include <vector>
# include <cstdlib>

using namespace std;

int findset(vector<vector<int>> *ds, int node) {
	return (*ds)[1][node];
};

vector<vector<int>> unify(vector<vector<int>> ds, int node[2]) {
	int sets[2] = {findset(&ds, node[0]), findset(&ds, node[1])};
	if (sets[0] != sets[1]) {
		for (int index = 0; index < ds[1].size(); index++) {// Cycles through all elements in the second dimension
			// We will replace all
			if (sets[0] == ds[1][index]) {
				// Replace it
				ds[1][index] = sets[1];
			};
		};
	};

	return ds;
};

int main() {
	vector<vector<int>> adjmat {
		{0, 1, 1, 0, 0, 0, 0},
		{1, 0, 0, 1, 0, 0, 0},
		{1, 0, 0, 1, 0, 0, 0},
		{0, 1, 1, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 1, 0}
	};

	// This implements 7 set creations, one for each node.
	vector<vector<int>> ds1 {};
	for (int index = 0; ds1.size() < 2;) {
		vector<int> sets_or_representatives; // First entry: sets; second entry: set representatives
		for (index = 0; index < adjmat.size(); index++) {
			sets_or_representatives.push_back(index);
		};
		ds1.push_back(sets_or_representatives);
	};

	cout << findset(&ds1, 5) << endl;
	cout << findset(&ds1, 6) << endl;

	for (int i = 0; i < adjmat.size(); i++) {
		cout << ds1[1][i];
		if (i < adjmat.size() - 1) {cout << ", ";};
	};

	for (int indices[2] = {0, 0}; indices[0] < adjmat.size(); indices[0]++) {
		for (indices[1] = 0; indices[1] < adjmat.size(); indices[1]++) {
			if (adjmat[indices[0]][indices[1]]) {
				int nodes[2] = {indices[0], indices[1]} ;
				ds1 = unify(ds1, nodes);
			}
		}
	};

	cout << findset(&ds1, 2);
};
