# include <iostream>
# include <vector>

using namespace std;

namespace Conversions {
	template <typename weight_type>
	vector<vector<int>> adjacency_list(vector<vector<weight_type>> adjacency_matrix) {
		vector<vector<int>> list;
		for (int node = 0; node < adjacency_matrix.size(); node++) {
			vector<int> connections;
			vector<weight_type> *connections_binary = &(adjacency_matrix[node]); // the connections

			for (int connection = 0; connection < connections_binary->size(); connection++) {
				if ((*connections_binary)[connection]) {
					connections.push_back(connection);
				};
			};
			list.push_back(connections);
		};

		return list;
	};

	template <typename weight_type>
	vector<vector<int>> edge_list(vector<vector<weight_type>> adjacency_matrix) {
		vector<vector<int>> list;
		for (int node = 0; node < adjacency_matrix.size(); node++) {
			vector<weight_type> *connections_binary = &(adjacency_matrix[node]); // the connections

			for (int connection = 0; connection < connections_binary->size(); connection++) {
				if ((*connections_binary)[connection]) {
					vector<int> connections = {node, connection, (*connections_binary)[connection]};
					list.push_back(connections);
				};
			};
		};

		return list;
	};

	template <typename weight_type>
	vector<vector<weight_type>> adjacency_matrix(vector<vector<int>> edges) {
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
				connections.push_back(0);
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

	vector<vector<bool>> adjacency_matrix(vector<vector<int>> adjacency_list) {
		vector<vector<bool>> matrix;

		int dimensions = -1;
		for (int node = 0; node < adjacency_list.size(); node++) {
			for (int neighbour: adjacency_list[node]) {
				if (neighbour > dimensions) {dimensions = neighbour;};
			};
		};

		while (matrix.size() < dimensions + 1) {
			vector<bool> connections;
			while (connections.size() < dimensions + 1) {
				connections.push_back(false);
			};
			matrix.push_back(connections);
		};


		for (int node = 0; node < adjacency_list.size(); node++) {
			for (int neighbour: adjacency_list[node]) {
				matrix[node][neighbour] = true;
			};
		};

		return matrix;
	};


};

int main() {
	vector<vector<int>> matrix = {
		{0, 1, 9},
		{1, 0, 1},
		{0, 1, 0}
	};

	vector<vector<int>> adjlist = Conversions::adjacency_list<int>(matrix);
	vector<vector<int>> edgelist = Conversions::edge_list<int>(matrix);
	vector<vector<int>> original = Conversions::adjacency_matrix<int>(edgelist);
	vector<vector<bool>> original2 = Conversions::adjacency_matrix(adjlist);

	for (int index[2] = {0, 0}; index[0] < adjlist.size(); index[0]++) {
		for (index[1] = 0; index[1] < adjlist[index[0]].size(); index[1]++) {
			cout << adjlist[index[0]][index[1]];

			if (index[1] < adjlist[index[0]].size() - 1) {cout << ",";};
		};
		cout << endl;
	}

	for (int index[2] = {0, 0}; index[0] < edgelist.size(); index[0]++) {
		for (index[1] = 0; index[1] < edgelist[index[0]].size(); index[1]++) {
			cout << edgelist[index[0]][index[1]];

			if (index[1] < edgelist[index[0]].size() - 1) {cout << ",";};
		};
		cout << endl;
	};

	for (int index[2] = {0, 0}; index[0] < original.size(); index[0]++) {
		for (index[1] = 0; index[1] < original[index[0]].size(); index[1]++) {
			cout << original[index[0]][index[1]];

			if (index[1] < original[index[0]].size() - 1) {cout << ",";};
		};
		cout << endl;
	};

	for (int index[2] = {0, 0}; index[0] < original2.size(); index[0]++) {
		for (index[1] = 0; index[1] < original2[index[0]].size(); index[1]++) {
			cout << original2[index[0]][index[1]];

			if (index[1] < original2[index[0]].size() - 1) {cout << ",";};
		};
		cout << endl;
	};
}
