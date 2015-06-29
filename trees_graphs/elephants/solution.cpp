
#include <iostream>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

struct elephant {
	int id;
	vector<elephant*> smaller_elephants;
	bool visited;
};

static void dfs_visit(elephant *node) {
	if (node->visited == true) {
		return;
	}

	node->visited = true;

	for (vector<elephant*>::iterator it = node->smaller_elephants.begin();
	     it != node->smaller_elephants.end();
	     it++) {
		dfs_visit(*it);
	}

	cout << node->id << " ";
}

void topological_sort(map<int, elephant*> &graph) {
	for (map<int, elephant*>::iterator el_it = graph.begin();
	     el_it != graph.end();
	     el_it++) {
		el_it->second->visited = false;
	}
	for (map<int, elephant*>::iterator el_it = graph.begin();
	     el_it != graph.end();
	     el_it++) {
		dfs_visit(el_it->second);
	}
	cout << endl;
}

static elephant *get_node(map<int, elephant*> &graph, int id) {
	if (graph.find(id) == graph.end()) {
		graph[id] = new elephant;
		graph[id]->id = id;
	}
	return graph[id];
}

int main(void) {
	cout << "Enter the number of input lines of information. Then, for each line, enter either of:" << endl;
	cout << "T id1 id2 - this means that elephant with ID `id1` is taller than elephant with ID `id2`" << endl;
	cout << "S id1 id2 - this means that elephant with ID `id1` is smaller than elephant with ID `id2`" << endl;
	cout << "> ";

	unsigned lines;
	while (cin >> lines) {

		map<int, elephant*> graph;

		for (unsigned i = 0; i < lines; i++) {
			char op;
			cin >> op;

			int id1, id2;
			cin >> id1 >> id2;

			elephant *id1_elephant = get_node(graph, id1);
			elephant *id2_elephant = get_node(graph, id2);

			if (op == 'T') {
				id1_elephant->smaller_elephants.push_back(id2_elephant);
			} else if (op == 'S') {
				id2_elephant->smaller_elephants.push_back(id1_elephant);
			} else {
				assert(0);
			}
		}

		topological_sort(graph);

		cout << "> ";
	}

	return 0;
}
