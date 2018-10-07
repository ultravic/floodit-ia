// Victor Picussa - GRR20163068
#include <iostream>
#include <stdlib.h>
#include <strings.h>
#include <graphviz/cgraph.h>

//=============================Estruturas=====================================//
// Estrutura para armazenar a cor e peso dos nodos.                            //
//============================================================================//
typedef struct {
	Agrec_t header;
	int color, weight;
} node_data_t;
//============================================================================//

//==========================reorganizeNodes===================================//
// Agrupa nodos de cores iguais em um único node, criando arestas entre os    //
// nodos filhos e nodo pai do nodo sendo analisado. No fim, o nodo analisado  //
// é deletado.
//============================================================================//
void reorganizeNodes(Agraph_t *graph_map, Agnode_t *node, node_data_t *data, int flag)
{
	Agnode_t *edon;
	Agedge_t *edge, *egde, *nxt_edge;
	node_data_t *data_cp;

	char *temp = (char*)malloc(sizeof(char)*42);

	if (flag) {
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
				data->weight += data_cp->weight;
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
	} else {
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
				data->weight++;
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

	free(temp);
}
//============================================================================//

//=============================solveMap=======================================//
// Resolve um mapa de cores, retorna uma sequência de ações para que o mapa   //
// seja pintado até ter somente uma cor. O mapa deve ser passado como stdin.  //
// O algoritmo tem o objetivo de juntar nodos iguais em um único e resolver,  //
// começando pelo canto esquerdo, buscando o caminho de mair coloração,       //
// verificando até uma profundidade 2.                                        //
//============================================================================//
int solveMap()
{
	Agraph_t *graph_map;
	Agnode_t *node, *edon, *heavier_node, *sec;
	Agedge_t *edge, *egde;
	node_data_t *data, *data_cp, *sec_data;

	int greater, sec_greater;
	int lines, columns, colors;

	std::cin >> lines >> columns >> colors;

	int *coloring = (int*)malloc(sizeof(int)*(lines*(columns/4)));

	char *temp = (char*)malloc(sizeof(char)*42);
	char *auxi = (char*)malloc(sizeof(char)*42);
	char *fm = (char*)malloc(sizeof(char)*9);


	sprintf(fm, "%s", "floodmap");
	graph_map = agopen(fm, Agundirected, NULL);

	// Cria nodos com a cor
	int count = 1;
	for (int i_index = 0; i_index < lines; i_index++) {
		for (int j_index = 0; j_index < columns; j_index++) {
			sprintf(temp, "%d", count);
			node = agnode(graph_map, temp, TRUE);
			data = (node_data_t*)agbindrec(node, temp, sizeof(node_data_t), TRUE);
			std::cin >> data->color;
			data->weight = 1;
			count++;
		}
	}

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

	free(auxi);

	// Junta os nodos
	int lc = lines*columns;
	for (int counter = 1; counter <= lc; counter++) {
		sprintf(temp, "%d", counter);
		node = agnode(graph_map, temp, FALSE);
		if (node) {
			data = (node_data_t*)aggetrec(node, temp, TRUE);
			reorganizeNodes(graph_map, node, data, 0);
		}
	}

	// Resolução do mapa
	sprintf(temp, "%d", 1);
	node = agnode(graph_map, temp, FALSE);
	data = (node_data_t*)aggetrec(node, temp, TRUE);
	heavier_node = aghead(agfstedge(graph_map, node));

	coloring[0] = 0;
	while (agnnodes(graph_map) > 1) {
		greater = 0;
		for (edge = agfstedge(graph_map, node); edge; edge = agnxtedge(graph_map, edge, node)) {
			if (strcmp(agnameof(node), agnameof(aghead(edge))))
				edon = aghead(edge);
			else if (strcmp(agnameof(node), agnameof(agtail(edge))))
				edon = agtail(edge);
			else
				continue;
			sec_greater = 0;
			for (egde = agfstedge(graph_map, edon); egde; egde = agnxtedge(graph_map, egde, edon)) {
				if (strcmp(agnameof(node), agnameof(aghead(egde))) && strcmp(agnameof(egde), agnameof(edon)))
					sec = aghead(egde);
				else if (strcmp(agnameof(node), agnameof(agtail(egde))) && strcmp(agnameof(egde), agnameof(edon)))
					sec = agtail(egde);
				else
					continue;
				sec_data = (node_data_t*)aggetrec(sec, agnameof(sec), TRUE);
				if ((sec_data->weight) > sec_greater)
					sec_greater = sec_data->weight;
			}
			data_cp = (node_data_t*)aggetrec(edon, agnameof(edon), TRUE);
			if ((data_cp->weight + sec_greater) > greater) {
				greater = data_cp->weight + sec_greater;
				heavier_node = edon;
			}
		}
		data_cp = (node_data_t*)aggetrec(heavier_node, agnameof(heavier_node), TRUE);
		data->color = data_cp->color;
		data->weight += data_cp->weight;
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
		reorganizeNodes(graph_map, node, data, 1);
		coloring[++coloring[0]] = data->color;
	}

	// Printa a quantidade e a sequência de coloração
	std::cout << coloring[0] << "\n";
	for (int i_index = 1; i_index <= coloring[0]; i_index++)
		std::cout << coloring[i_index] << " ";
	std::cout << "\n";

	agclose(graph_map);
	free(coloring);
	free(temp);
	free(auxi);
	free(fm);

	return 0;
}
//============================================================================//

int main()
{
	solveMap();

	return 0;
}
//============================================================================//
