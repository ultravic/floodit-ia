#include <iostream>

struct fi_table {
	int lines, columns, colors;
	int* table;
};

int tableCreate(fi_table *fi_table_td)
{
	std::cin >> (*fi_table_td).lines >> (*fi_table_td).columns >> (*fi_table_td).colors;

	(*fi_table_td).table = (int*)malloc(sizeof(int)*((*fi_table_td).lines*(*fi_table_td).columns));

	for (int i_index = 0; i_index < (*fi_table_td).lines; i_index++)
		for (int j_index = 0; j_index < (*fi_table_td).columns; j_index++)
			std::cin >> (*fi_table_td).table[(i_index*(*fi_table_td).columns)+j_index];
	
	return 0;
}

int tablePrint(fi_table *fi_table_td)
{

	std::cout << "Lines: " << (*fi_table_td).lines << "\n";
	std::cout << "Columns: " << (*fi_table_td).columns << "\n";
	std::cout << "Colors: " << (*fi_table_td).colors << "\n";

	for (int i_index = 0; i_index < (*fi_table_td).lines; i_index++) {
		for (int j_index = 0; j_index < (*fi_table_td).columns; j_index++)
			std::cout << (*fi_table_td).table[(i_index*(*fi_table_td).columns)+j_index] << " ";
		std::cout << "\n";
	}

	return 0;
}

int floodSolver(fi_table *fi_table_td)
{
	int *solution;
	solution = (int*)malloc(sizeof(int)*100);

	int positon[2] = {0, 0};

	

	return 0;
}

int main() 
{
	fi_table fi_table_td;

	tableCreate(&fi_table_td);
	tablePrint(&fi_table_td);

	return 0;
}
