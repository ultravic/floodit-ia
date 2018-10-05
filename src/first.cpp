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
	Agedge_t *egde;
	node_data_t *data;
	node_data_t *data_cp;

	int lines, columns, colors, count;
	char *temp = (char*)malloc(sizeof(char)*21);
	char *auxi = (char*)malloc(sizeof(char)*21);

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
	sprintf(auxi, "%d", 2);
	edon = agnode(graph_map, auxi, FALSE);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(auxi, "%d", columns+1);
	edon = agnode(graph_map, auxi, FALSE);
	sprintf(temp, "%d", 1);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(temp, "%d", 2);
	node = agnode(graph_map, temp, FALSE);
	sprintf(auxi, "%d", columns+1);
	edon = agnode(graph_map, auxi, FALSE);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);
	
	// Superior
	for (int i_index = 2; i_index < columns - 1; i_index++) {
		sprintf(temp, "%d", i_index);
		node = agnode(graph_map, temp, FALSE);
		sprintf(auxi, "%d", i_index+1);
		edon = agnode(graph_map, auxi, FALSE);
		strcat(temp, auxi);
		edge = agedge(graph_map, node, edon, temp, TRUE);
	}
	
	// Canto superior direito
	sprintf(temp, "%d", columns);
	node = agnode(graph_map, temp, FALSE);
	sprintf(auxi, "%d", columns-1);
	edon = agnode(graph_map, auxi, FALSE);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(auxi, "%d", 2*columns);
	edon = agnode(graph_map, auxi, FALSE);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(temp, "%d", columns-1);
	node = agnode(graph_map, temp, FALSE);
	sprintf(auxi, "%d", 2*columns);
	edon = agnode(graph_map, auxi, FALSE);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);

	// Esquerda
	for (int i_index = 1; i_index < lines - 2; i_index++) {
		sprintf(temp, "%d", (i_index*columns)+1);
		node = agnode(graph_map, temp, FALSE);
		sprintf(auxi, "%d", ((i_index+1)*columns)+1);
		edon = agnode(graph_map, auxi, FALSE);
		strcat(temp, auxi);
		edge = agedge(graph_map, node, edon, temp, TRUE);
	}

	// Canto inferior esquerdo
	sprintf(temp, "%d", ((lines-1)*columns)+1);
	node = agnode(graph_map, temp, FALSE);
	sprintf(auxi, "%d", ((lines-1)*columns)+2);
	edon = agnode(graph_map, auxi, FALSE);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(auxi, "%d", ((lines-2)*columns)+1);
	edon = agnode(graph_map, auxi, FALSE);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(temp, "%d", ((lines-2)*columns)+1);
	node = agnode(graph_map, temp, FALSE);
	sprintf(auxi, "%d", ((lines-1)*columns)+2);
	edon = agnode(graph_map, auxi, FALSE);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);
	
	// Direita
	for (int i_index = 2; i_index < lines - 1 ; i_index++) {
		sprintf(temp, "%d", (i_index*columns));
		node = agnode(graph_map, temp, FALSE);
		sprintf(auxi, "%d", ((i_index+1)*columns));
		edon = agnode(graph_map, auxi, FALSE);
		strcat(temp, auxi);
		edge = agedge(graph_map, node, edon, temp, TRUE);
	}

	// Canto inferior direito
	sprintf(temp, "%d", lines*columns);
	node = agnode(graph_map, temp, FALSE);
	sprintf(auxi, "%d", (lines*columns)-1);
	edon = agnode(graph_map, auxi, FALSE);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(auxi, "%d", ((lines-1)*columns));
	edon = agnode(graph_map, auxi, FALSE);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);
	sprintf(temp, "%d", ((lines-1)*columns));
	node = agnode(graph_map, temp, FALSE);
	sprintf(auxi, "%d", (lines*columns)-1);
	edon = agnode(graph_map, auxi, FALSE);
	strcat(temp, auxi);
	edge = agedge(graph_map, node, edon, temp, TRUE);
	
	// Inferior
	for (int i_index = 2; i_index < columns - 1; i_index++) {
		sprintf(temp, "%d", ((lines-1)*columns)+i_index);
		node = agnode(graph_map, temp, FALSE);
		sprintf(auxi, "%d", ((lines-1)*columns)+i_index+1);
		edon = agnode(graph_map, auxi, FALSE);
		strcat(temp, auxi);
		edge = agedge(graph_map, node, edon, temp, TRUE);
	}

	// Meio
	for (int i_index = 1; i_index < lines - 1; i_index++) {
		for (int j_index = 2; j_index < columns; j_index++) {
			sprintf(temp, "%d", (i_index*columns)+j_index);
			node = agnode(graph_map, temp, FALSE);
			sprintf(auxi, "%d", (i_index*columns)+j_index+1);
			edon = agnode(graph_map, auxi, FALSE);
			strcat(temp, auxi);
			edge = agedge(graph_map, node, edon, temp, TRUE);
			sprintf(auxi, "%d", (i_index*columns)+j_index-1);
			edon = agnode(graph_map, auxi, FALSE);
			sprintf(temp, "%d", (i_index*columns)+j_index);
			strcat(temp, auxi);
			edge = agedge(graph_map, node, edon, temp, TRUE);
			sprintf(auxi, "%d", ((i_index-1)*columns)+j_index);
			edon = agnode(graph_map, auxi, FALSE);
			sprintf(temp, "%d", (i_index*columns)+j_index);
			strcat(temp, auxi);
			edge = agedge(graph_map, node, edon, temp, TRUE);
			sprintf(auxi, "%d", ((i_index+1)*columns)+j_index);
			edon = agnode(graph_map, auxi, FALSE);
			sprintf(temp, "%d", (i_index*columns)+j_index);
			strcat(temp, auxi);
			edge = agedge(graph_map, node, edon, temp, TRUE);
			sprintf(auxi, "%d", ((i_index-1)*columns)+j_index+1);
			edon = agnode(graph_map, auxi, FALSE);
			sprintf(temp, "%d", (i_index*columns)+j_index);
			strcat(temp, auxi);
			edge = agedge(graph_map, node, edon, temp, TRUE);
			sprintf(auxi, "%d", ((i_index-1)*columns)+j_index-1);
			edon = agnode(graph_map, auxi, FALSE);
			sprintf(temp, "%d", (i_index*columns)+j_index);
			strcat(temp, auxi);
			edge = agedge(graph_map, node, edon, temp, TRUE);
			sprintf(auxi, "%d", ((i_index+1)*columns)+j_index+1);
			edon = agnode(graph_map, auxi, FALSE);
			sprintf(temp, "%d", (i_index*columns)+j_index);
			strcat(temp, auxi);
			edge = agedge(graph_map, node, edon, temp, TRUE);
			sprintf(auxi, "%d", ((i_index+1)*columns)+j_index-1);
			edon = agnode(graph_map, auxi, FALSE);
			sprintf(temp, "%d", (i_index*columns)+j_index);
			strcat(temp, auxi);
			edge = agedge(graph_map, node, edon, temp, TRUE);
		}
	}

	// Printa tabela
	int lc = lines*columns;
	for (int counter = 1; counter <= lc; counter++) {
		sprintf(temp, "%d", counter);
		node = agnode(graph_map, temp, FALSE);
		data = (node_data_t*)aggetrec(node, temp, TRUE);
		std::cout << data->color << " ";
		if (counter % columns == 0) std::cout << "\n";
	}

	// Junta nodos
	count = 0;
	int del;
	for (int counter = 1; counter <= lc; counter++) {
		sprintf(temp, "%d", counter);
		node = agnode(graph_map, temp, FALSE);
		data = (node_data_t*)aggetrec(node, temp, TRUE);
		for (edge = agfstedge(graph_map, node); edge; edge = agnxtedge(graph_map, edge, node)) {
			std::cout << "T\n";
			if (del) agdelnode(graph_map, edon);
			std::cout << "TT\n";
			del = 0;
			if (strcmp(agnameof(node), agnameof(aghead(edge))) != 0) {
				edon = aghead(edge);
				data_cp = (node_data_t*)aggetrec(edon, agnameof(edon), TRUE);
				if (data->color == data_cp->color) {
					data->qtd++;
					std::cout << "E\n";
					for (egde = agfstedge(graph_map, edon); egde; egde = agnxtedge(graph_map, egde, edon)) {
						sprintf(temp, "%s", agnameof(node));
						strcat(temp, agnameof(aghead(egde)));
						agedge(graph_map, node, aghead(egde), temp, FALSE);
					}
					del++;
					std::cout << "DD\n";
					std::cout << agnameof(node) << ":" << agnameof(edon) << "\n";
				}
				std::cout << "END\n";
			}
		}
	}

	std::cout << "Nodos: " << agnnodes(graph_map) << "\n";
	std::cout << "Iguais: " << count << "\n";

	
	return 0;
}

int main()
{
	solveMap();

	return 0;
}

//------------------------------------------------------------------------------

