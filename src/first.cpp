#include <iostream>
#include <stdlib.h>
#include <strings.h>
#include <graphviz/cgraph.h>

typedef struct {
	Agrec_t header;
	int color, qtd;
} node_data_t;

int solveMap()
{
	Agraph_t *graph_map;
	Agnode_t *node, *edon;
	Agedge_t *edge;
	node_data_t *data;

	int lines, columns, colors, count;
	char *temp = (char*)malloc(sizeof(char)*21);

	std::cin >> lines >> columns >> colors;
	
	graph_map = agopen("floodmap", Agundirected, NULL);

	// Cria nodos com a cor
	count = 1;
        for (int i_index = 0; i_index < lines; i_index++) {
		for (int j_index = 0; j_index < columns; j_index++) {
			sprintf(temp, "%d", count);
        		node = agnode(graph_map, temp, TRUE);
			data = (node_data_t*)agbindrec(node, temp, sizeof(node_data_t), TRUE);
			std::cin >> data->color;
			data->qtd = 1;
			count++;
		}
	}

	count = 1;
	
	// Canto superior esquerdo
	sprintf(temp, "%d", 1);
	node = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", 2);
	edon = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", count);
	count++;
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(temp, "%d", columns+1);
	edon = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", count);
	count++;
	edge = agedge(graph_map, node, edon, temp, TRUE);

	// Canto superior direito
	sprintf(temp, "%d", columns);
	node = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", columns-1);
	edon = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", count);
	count++;
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(temp, "%d", 2*columns);
	edon = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", count);
	count++;
	edge = agedge(graph_map, node, edon, temp, TRUE);

	
	// Canto inferior esquerdo
	sprintf(temp, "%d", ((lines-1)*columns)+1);
	node = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", ((lines-1)*columns)+2);
	edon = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", count);
	count++;
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(temp, "%d", ((lines-2)*columns)+1);
	edon = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", count);
	count++;
	edge = agedge(graph_map, node, edon, temp, TRUE);
	

	// Canto inferior direito
	sprintf(temp, "%d", lines*columns);
	node = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", (lines*columns)-1);
	edon = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", count);
	count++;
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(temp, "%d", ((lines-1)*columns));
	edon = agnode(graph_map, temp, FALSE);
	sprintf(temp, "%d", count);
	count++;
	edge = agedge(graph_map, node, edon, temp, TRUE);

	// Superior


	// Esquerda

	
	// Direita
	

	// Inferior


	// Meio
	for (int i_index = 1; i_index < lines; i_index++) {
		for (int j_index = 2; j_index < columns; j_index++) {
			sprintf(temp, "%d", (i_index*lines)+j_index);
			node = agnode(graph_map, temp, FALSE);
			sprintf(temp, "%d", (i_index*lines)+j_index+1);
			edon = agnode(graph_map, temp, FALSE);
			sprintf(temp, "%d", (i_index*lines)+j_index-1);
			edon = agnode(graph_map, temp, FALSE);
			sprintf(temp, "%d", ((i_index-1)*lines)+j_index);
			edon = agnode(graph_map, temp, FALSE);
			sprintf(temp, "%d", ((i_index+1)*lines)+j_index);
			edon = agnode(graph_map, temp, FALSE);
			sprintf(temp, "%d", ((i_index-1)*lines)+j_index+1);
			edon = agnode(graph_map, temp, FALSE);
			sprintf(temp, "%d", ((i_index-1)*lines)+j_index-1);
			edon = agnode(graph_map, temp, FALSE);
			sprintf(temp, "%d", ((i_index+1)*lines)+j_index+1);
			edon = agnode(graph_map, temp, FALSE);
			sprintf(temp, "%d", ((i_index+1)*lines)+j_index-1);
			edon = agnode(graph_map, temp, FALSE);
		}
	}

	int lc = lines*columns;
	for (int counter = 1; counter <= lc; counter++) {
		sprintf(temp, "%d", counter);
		node = agnode(graph_map, temp, FALSE);
		data = (node_data_t*)aggetrec(node, temp, TRUE);
		std::cout << data->color << " ";
		if (counter % columns == 0) std::cout << "\n";
	}

	
	return 0;
}

int main()
{
	solveMap();

	return 0;
}

//------------------------------------------------------------------------------

