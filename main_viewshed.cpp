#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <climits>
#include <time.h>
#include <tgmath.h>

using namespace std;
#include "grid.hpp"
#include "grid.cpp"
#include "view_functions.hpp"
#include "view_functions.cpp"





void compute_viewshed(grid &elevation_grid, grid &viewshed_grid, int vp_row, int vp_col) {

	for (int i = 0; i < elevation_grid.rows; i++) {
		for (int j = 0; j < elevation_grid.cols; j++) {

			//handle some special cases:
			if (elevation_grid.data[i][j] == NO_DATA) {
				viewshed_grid.data[i][j] = NO_DATA;
			}
			else if (i == vp_row && j == vp_col) {
				viewshed_grid.data[i][j] = 1;
			}
			else if (i == vp_row) {
				viewshed_grid.data[i][j] = ( (j < vp_col) ? is_visible_left(elevation_grid, vp_row, vp_col, i, j) 
														  : is_visible_right(elevation_grid, vp_row, vp_col, i, j));
			}
			else if (j == vp_col) {
				viewshed_grid.data[i][j] = ( (i < vp_row) ? is_visible_up(elevation_grid, vp_row, vp_col, i, j) 
														  : is_visible_down(elevation_grid, vp_row, vp_col, i, j));
			}

			//now check 4 quadrants
			//quadrant 1
			else if (i < vp_row && j > vp_col) {
				viewshed_grid.data[i][j] = is_visible_q1(elevation_grid, vp_row, vp_col, i, j);
			} 
			//quadrant 2
			else if (i < vp_row && j < vp_col) {
				viewshed_grid.data[i][j] = is_visible_q2(elevation_grid, vp_row, vp_col, i, j);
			}
			//quadrant 3
			else if (i > vp_row && j < vp_col) {
				viewshed_grid.data[i][j] = is_visible_q3(elevation_grid, vp_row, vp_col, i, j);
			}
			//quadrant 4
			else {
				viewshed_grid.data[i][j] = is_visible_q4(elevation_grid, vp_row, vp_col, i, j);
			}
		}
	}

}


int main(int argc, char * argv[]) {

	//read in command line arguments, checking for existence
	if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) {
		cout << "Please enter a grid file name and two indices";
		exit(1);
	} else {
		cout << "You entered file name: " << argv[1] << endl;
	}

	string file_name = argv[1];

	cout << file_name << endl;

	//make a grid and read the file data into it
	grid grid_from_file;
	read_file_into_array(file_name, grid_from_file);

	int vp_row;
	int vp_col;
	// todo BUG! converts a string input to 0
	if (atoi(argv[2]) < 0 || atoi(argv[2]) >= grid_from_file.rows
	 || atoi(argv[3]) < 0 || atoi(argv[3]) >= grid_from_file.cols) {
		cout << "Please enter valid grid point locations";
		exit(1);
	} else {
		vp_row = atoi(argv[2]);
		vp_col = atoi(argv[3]);
		cout << "Computing viewshed for (" << vp_row << "," << vp_col << ")" << endl;
	}
    
	cout << "Here is the original grid:" << endl;
	print_header(grid_from_file);
	//print_2d_array(grid_from_file);

	grid viewshed_grid;
	viewshed_grid.rows = grid_from_file.rows;
	viewshed_grid.cols = grid_from_file.cols;
	allocate_memory_for_grid(viewshed_grid);

	clock_t start = clock();
	compute_viewshed(grid_from_file, viewshed_grid, vp_row, vp_col);
	clock_t end = clock();
	clock_t ticks = end - start;
	double duration = ticks / (double) CLOCKS_PER_SEC;
	cout << "algorithm took: " << duration << " seconds" << endl;


	//print_2d_array(viewshed_grid);

	ofstream viewshed_file("viewshed.asc");
	viewshed_file << grid_from_file.header;
	for(int i = 0; i < viewshed_grid.rows; i++) {
		for (int j = 0; j < viewshed_grid.cols; j++) {
			viewshed_file << viewshed_grid.data[i][j] << " ";
		}
		viewshed_file << "\n";
	}

	free(grid_from_file.data);
	free(viewshed_grid.data);
	return 0;
}


