#include <iostream>
#include <lemon/list_graph.h>

using namespace lemon;
using namespace std;

typedef struct {
	int lines, columns, colors;
	ListGraph table;
} flood_info_t;

int solveFlood(flood_info_t *mp)
{
	cin >> (*mp).lines >> (*mp).columns >> (*mp).colors;

	ListGraph::NodeMap<int> map((*mp).table);

	for (int i_index = 0; i_index < (*mp).lines; i_index++) {
		for (int j_index = 0; j_index < (*mp).columns; j_index++) {
			ListGraph::Node nd = (*mp).table.addNode();
			cin >> map[nd];
		}
	}

	cout << (*mp).lines << " " << (*mp).columns << " " << (*mp).colors << endl;

	for (ListGraph::NodeIt n((*mp).table); n != INVALID; ++n) {
		cout << map[n] << ":" << (*mp).table.id(n) << " ";
		if ((*mp).table.id(n) % (*mp).lines == 0)
			cout << endl;
	}

	return 0;
}


int main()
{
	flood_info_t fi_info;

	solveFlood(&fi_info);

	return 0;
}
