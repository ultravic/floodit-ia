#include <iostream>
#include <string>
#include <graphviz/cgraph.h>

typedef struct {
	int lines, columns, colors;
	Agraph_t *table;
} map_info_td;

int createMap(map_info_td *mp)
{
	int auxiliar[2];
	int in;
	Agnode_t *nd;

	std::cin >> (*mp).lines >> (*mp).columns >> (*mp).colors;

	agattr(mp->table, AGNODE, "cor", "0");

	for (int i_index = 0; i_index < (*mp).lines; i_index++) {
		auxiliar[0] = i_index;
		for (int j_index = 0; j_index < (*mp).columns; j_index++) {
			auxiliar[1] = j_index;
			std::cin >> in;
			nd = agnode(mp->table, str(auxiliar), FALSE);
			agset(agnode(mp->table, agnameof(nd), TRUE), "cor", in);
		}
	}
	
	//cout << (*mp).lines << " " << (*mp).columns << " " << (*mp).colors << endl;

	//for (nd = agfstnode((*mp).table); nd; nd = agnxtnode((*mp).table, nd)) {
	//	cout << map[n] << " ";
	//	if ((*mp).table.id(n) % (*mp).lines == 0)
	//		cout << endl;
	//}

	return 0;	
}

int main()
{
	map_info_td map_info;
	
	createMap(&map_info);

	//cout << "Nodes count: " << countNodes(map_info.table) << endl;

	return 0;
}
