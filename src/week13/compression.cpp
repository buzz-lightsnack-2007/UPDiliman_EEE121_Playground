# include <cstdlib>
# include <iostream>
# include <vector>
# include <map>
# include <stack>


using namespace std;

/**
 * Compress the parents table from a given reference node.
 *
 * @param nodes (vector<node_type>) the nodes
 * @param node_parents (map<node_type, node_type>) the node parents
 * @param node (node_type) the node
 * @return map<node_type, node_type>
 * @returns the updated `node_parents`
 */
template <typename node_type>
map<node_type, node_type> compress(vector<node_type> nodes, map<node_type, node_type> node_parents, node_type node) {
	stack<node_type> children; // the children for editing

	stack<node_type> parents; // the parents
	parents.push(node);

	// Keep finding parents
	while (parents.top() != node_parents[parents.top()]) { // if there is one
		children.push(parents.top());
		parents.push(node_parents[parents.top()]); // Add another parent
	};
	node_type representative = parents.top();// the set's representative

	// Only edit the children we traversed to.
	while (children.size()) {
		node_type child = children.top();

		node_parents[child] = representative;
		children.pop();
	}

	/* // Below code is incorrect because it's (indiscriminately) editing every node with that parent.
	while (parents.size()) { // Now that we've found it, we'll replace all children one by one
		node_type parent = parents.top();

		for (int node_ID = 0; node_ID < nodes.size(); node_ID++) {
			if (node_parents[nodes[node_ID]] == parent) {
				node_parents[nodes[node_ID]] = representative; // Replace it
			};
		};

		parents.pop();
	}; */

	return node_parents;
};

template <typename node_type>
class Interface {
	protected:
		int size;

	public:
		Interface() {};

		node_type target;
		vector<node_type> nodes; // the nodes
		map<node_type, node_type> parents; // their parents

		/**
		 * Resize the representation of disjoint sets.
		 *
		 * @return int
		 * @returns the size
		 */
		int resize() {
			int size = 0;
			cin >> size;

			this->size = abs(size);
			return this->size;
		};

		/**
		 * Provide entry for nodes and their parents.
		 * @return map<node_type, node_type>
		 * @returns a map of the node and their parents
		 */
		map<node_type, node_type> prefill() {
			vector<vector<node_type>> ds = {{}, {}}; // the nodes and their parent
			for (int round = 0; round < 2; round++) {
				// Add an entry
				for (node_type entry; ds[round].size() < this->size;) {
					cin >> entry;
					ds[round].push_back(entry);
				};
			};

			// Replace the contents of the ds
			this->nodes = ds[0];
			this->parents.clear();
			for (int node = 0; node < ds[0].size(); node++) {
				this->parents[ds[0][node]] = ds[1][node];
			};

			return this->parents;
		};

		/**
		 * Select a node to call findset on.
		 *
		 * @return int
		 * @returns the findset target
		 */
		int findset() {
			node_type target;
			cin >> target;

			this->target = target;

			return target;
		};

		/**
		 * Execute with all provided data.
		 */
		map<node_type, node_type> exec() {
			this->parents = compress(this->nodes, this->parents, this->target);
			return this->parents;
		};

		/**
		 * Display the disjoint set.
		 */
		void display() {
			for (int rounds[2] = {0, 0}; rounds[0] < 2; rounds[0]++) {
				for (rounds[1] = 0; rounds[1] < this->nodes.size(); rounds[1]++) {
					switch (rounds[0]) {
						case 0:
							cout << this->nodes[rounds[1]]; break;
						case 1:
							cout << this->parents[this->nodes[rounds[1]]]; break;
					};
					cout << "|";
				};
				cout << endl;
			};
		};
};

int main() {
	Interface<int> interface;

	interface.resize();
	interface.prefill();
	interface.findset();

	interface.exec();
	interface.display();
};
