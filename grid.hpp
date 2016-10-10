#ifndef grid_h_DEFINED
#define grid_h_DEFINED

struct grid {
	int rows, cols;
	int ** data;
	string header;
};

void print_2d_array(grid grid_from_file);
void print_header(grid grid_from_file);
void printInfo(grid grid_from_file);
void read_file_into_array(string file_name, grid &grid_from_file);
void calculate_flow_diretion(grid &flow_direction, grid &grid_from_file);
int accumulate(grid &flow_accumulation, grid &flow_direction, int row, int col);
void calculate_flow_accumulation(grid &flow_accumulation, grid &flow_direction);
void allocate_memory_for_grid(grid &grid_to_allocate);
void set_default_accumulation_values(grid &flow_grid);


#endif