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
	Agnode_t *node, *edon, *nxt_node;
	Agedge_t *edge, *nxt_edge;
	Agedge_t *egde;
	node_data_t *data;
	node_data_t *data_cp;

	int lines, columns, colors, count;
	int *coloring = (int*)malloc(sizeof(int)*2*lines);
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
	for (int counter = 1; counter <= lc; counter++) {
		sprintf(temp, "%d", counter);
		node = agnode(graph_map, temp, FALSE);
		if (node) {
			data = (node_data_t*)aggetrec(node, temp, TRUE);
			for (edge = agfstedge(graph_map, node); edge; edge = nxt_edge) {
				if (strcmp(agnameof(node), agnameof(aghead(edge))))
					edon = aghead(edge);
				else if (strcmp(agnameof(node), agnameof(agtail(edge))))
					edon = agtail(edge);
				else {
					nxt_edge = agnxtedge(graph_map, edge, node);	
					continue;
				}
				data_cp = (node_data_t*)aggetrec(edon, agnameof(edon), TRUE);
				if (data->color == data_cp->color) {
					data->qtd++;
					for (egde = agfstedge(graph_map, edon); egde; egde = agnxtedge(graph_map, egde, edon)) {
						sprintf(temp, "%s", agnameof(node));
						if (strcmp(agnameof(edon), agnameof(aghead(egde))) && strcmp(agnameof(node), agnameof(aghead(egde)))) {
						       	strcat(temp, agnameof(aghead(egde)));
							agedge(graph_map, node, aghead(egde), temp, TRUE);
						} else if (strcmp(agnameof(edon), agnameof(agtail(egde))) && strcmp(agnameof(node), agnameof(agtail(egde)))) {
						       	strcat(temp, agnameof(agtail(egde)));
							agedge(graph_map, node, agtail(egde), temp, TRUE);
						}
					}
					
					agdelnode(graph_map, edon);
					nxt_edge = agfstedge(graph_map, node);
				} else
					nxt_edge = agnxtedge(graph_map, edge, node);
			}
		}
	}

	std::cout << "\nNodes, edges and weight\n";
	for (int counter = 1; counter <= lc; counter++) {
		sprintf(temp, "%d", counter);
		node = agnode(graph_map, temp, FALSE);
		if (node) {
			data = (node_data_t*)aggetrec(node, temp, TRUE);
			std::cout << agnameof(node) << "=";
			for (edge = agfstedge(graph_map, node); edge; edge = agnxtedge(graph_map, edge, node)) {
				if (strcmp(agnameof(node), agnameof(aghead(edge)))) std::cout << agnameof(aghead(edge)) << ":";
				else std::cout << agnameof(agtail(edge)) << ":";
			}
			std::cout << "=" << data->qtd << "\n";
		}
	}
	std::cout << "\n";

	// Resolve mapa
	
	int greater;
	Agnode_t *heavier_node;
	sprintf(temp, "%d", 1);
	node = agnode(graph_map, temp, FALSE);
	data = (node_data_t*)aggetrec(node, temp, TRUE);
	while (agnnodes(graph_map) > 1) {
		greater = 0;
		for (edge = agfstedge(graph_map, node); edge; edge = nxt_edge) {
			if (strcmp(agnameof(node), agnameof(aghead(edge))))
				edon = aghead(edge);
			else if (strcmp(agnameof(node), agnameof(agtail(edge))))
				edon = agtail(edge);
			else
				continue;
			data_cp = (node_data_t*)aggetrec(edon, agnameof(edon), TRUE);
			if (data_cp->qtd > greater) {
				greater = data_cp->qtd;
				heavier_node = edon;
			}	
		}
		data_cp = (node_data_t*)aggetrec(heavier_node, agnameof(heavier_node), TRUE);
		data->color = data_cp->color;
		data->qtd += data_cp->qtd;
		coloring[0]++;
		coloring[coloring[0]] = data->color;
		for (egde = agfstedge(graph_map, heavier_node); egde; egde = agnxtedge(graph_map, egde, heavier_node)) {
			sprintf(temp, "%s", agnameof(node));
			if (strcmp(agnameof(heavier_node), agnameof(aghead(egde))) && strcmp(agnameof(node), agnameof(aghead(egde)))) {
			       	strcat(temp, agnameof(aghead(egde)));
				agedge(graph_map, node, aghead(egde), temp, TRUE);
			} else if (strcmp(agnameof(heavier_node), agnameof(agtail(egde))) && strcmp(agnameof(node), agnameof(agtail(egde)))) {
			       	strcat(temp, agnameof(agtail(egde)));
				agedge(graph_map, node, agtail(egde), temp, TRUE);
			}
		}
		agdelnode(graph_map, heavier_node);
		for (edge = agfstedge(graph_map, node); edge; edge = nxt_edge) {
			sprintf(temp, "%s", agnameof(node));
			if (strcmp(agnameof(node), agnameof(aghead(edge))))
				edon = aghead(edge);
			else if (strcmp(agnameof(node), agnameof(agtail(edge))))
				edon = agtail(edge);
			else
				continue;
			data_cp = (node_data_t*)aggetrec(edon, agnameof(edon), TRUE);
			if (data_cp->color == data->color) {
				data->qtd += data_cp->qtd;
				for (egde = agfstedge(graph_map, heavier_node); egde; egde = agnxtedge(graph_map, egde, heavier_node)) {
					sprintf(temp, "%s", agnameof(node));
					if (strcmp(agnameof(heavier_node), agnameof(aghead(egde))) && strcmp(agnameof(node), agnameof(aghead(egde)))) {
			       			strcat(temp, agnameof(aghead(egde)));
						agedge(graph_map, node, aghead(egde), temp, TRUE);
					} else if (strcmp(agnameof(heavier_node), agnameof(agtail(egde))) && strcmp(agnameof(node), agnameof(agtail(egde)))) {
			       			strcat(temp, agnameof(agtail(egde)));
						agedge(graph_map, node, agtail(egde), temp, TRUE);
					}
				}
				agdelnode(graph_map, edon);
				nxt_edge = agfstedge(graph_map, node);
			} else
				nxt_edge = agnxtedge(graph_map, edge, node);
		}
	}
	
	std::cout << "\nNodes, edges and weight\n";
	for (int counter = 1; counter <= lc; counter++) {
		sprintf(temp, "%d", counter);
		node = agnode(graph_map, temp, FALSE);
		if (node) {
			data = (node_data_t*)aggetrec(node, temp, TRUE);
			std::cout << agnameof(node) << "=";
			for (edge = agfstedge(graph_map, node); edge; edge = agnxtedge(graph_map, edge, node)) {
				if (strcmp(agnameof(node), agnameof(aghead(edge)))) std::cout << agnameof(aghead(edge)) << ":";
				else std::cout << agnameof(agtail(edge)) << ":";
			}
			std::cout << "=" << data->qtd << "\n";
		}
	}
	std::cout << "\n";

	std::cout << coloring[0] << "\n";
	for (int i_index = 1; i_index <= coloring[0]; i_index++)
		std::cout << coloring[i_index] << " ";
	std::cout << "\n";
	
	return 0;
}

int main()
{
	solveMap();

	return 0;
}

//------------------------------------------------------------------------------

