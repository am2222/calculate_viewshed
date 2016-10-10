
int NO_DATA;

//prints the grid array data
void print_2d_array(grid grid_from_file) {
	for (int row = 0; row < grid_from_file.rows; row ++){
		for (int col = 0; col < grid_from_file.cols; col++) {
			cout << grid_from_file.data[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
 }

//prints the header data of the grid
 void print_header(grid grid_from_file) {
 	cout << grid_from_file.header << endl;
 }

//prints relevant info about the grid
 void printInfo(grid grid_from_file) {
 	int min = INT_MAX;
 	int max = INT_MIN;
 	for (int row = 0; row < grid_from_file.rows; row++) {
 		for (int col = 0; col < grid_from_file.cols; col ++) {
 			if (grid_from_file.data[row][col] < min) { min = grid_from_file.data[row][col]; }
 			if (grid_from_file.data[row][col] > max) { max = grid_from_file.data[row][col]; }
 		}
 	}
 	cout << "This grid has " << grid_from_file.rows << " rows and " << grid_from_file.cols 
 	<< " columns, and has a min elevation of " << min << ", and a max elevation of " << max << endl;
     cout << "No data value is: " << NO_DATA << endl;
 }

//takes a file name and grid struct as parameters
 //reads the data of the file name appropriately into the grid
void read_file_into_array(string file_name, grid &grid_from_file) {

	//check for valid file name
	ifstream file;
	file.open( file_name.c_str());
	if (!file) {
		cout << "Please enter a valid file name..." << endl; 
		exit(1);
	}
	

	//initialize some variables
	int count = 0;
	string str; //will hold lines read from file
	int ** p; //pointer which will store grid data
	grid_from_file.header = ""; //initialize header of grid to blank string. read later

	while (getline(file, str)) {

		//count = 0, first line has column info
		if (count == 0) {
			string col_string;
			for (int i = 0; i < str.length(); i++) {
				if (isdigit(str[i])) {
					col_string.push_back(str[i]);
				}
			}

			grid_from_file.cols = atoi(col_string.c_str());
		}
		//second column has row info
		if (count == 1) {
			string row_string;
			for (int i = 0; i < str.length(); i++) {
				if (isdigit(str[i])) {
					row_string.push_back(str[i]);
				}
			}

			grid_from_file.rows = atoi(row_string.c_str());
		}
		//once columns and rows are read, allocate space for grid data to hold an array of int pointers
		if (count == 2) {
			p = (int **) malloc(grid_from_file.rows*sizeof(int *) );
			if (p == NULL) {exit(1);} //check for successful malloc
		}

		//get no_data value
		if (count == 5) {
			string no_data_string;
			for (int i = 0; i < str.length(); i++) {
				if (str[i] == '-' || isdigit(str[i])) {
					no_data_string.push_back(str[i]);
				}
			}

			NO_DATA = atoi(no_data_string.c_str());
		}
		//whenever count <= 5, the file is still reading header. read it into the grid's header
		if (count <= 5) {
			grid_from_file.header += str;
			grid_from_file.header += "\n";


		} 
		//else, build the array of this row by reading through the columns
		else {
			p[count - 6] = (int *) malloc(grid_from_file.cols * sizeof(int));
			if (p[count - 6] == NULL) {exit(1);} //check for succesfull malloc

			string build = "";
			int col = 0;
			for (int i = 0; i < str.length(); i++) {
				if (str[i] != ' ') {
					build += str[i];
				  } else {
					p[count - 6][col] = atoi(build.c_str());
				 	build = "";
				 	col += 1;
				}
			}
			p[count - 6][col] = atoi(build.c_str());
		}
		count++;
	}

	grid_from_file.data = p; //update the grid with the pointer to the array we created
}

void allocate_memory_for_grid(grid &grid_to_allocate) {

	grid_to_allocate.data = (int **) malloc(grid_to_allocate.rows * sizeof(int *));
	if (grid_to_allocate.data == NULL) {exit(1);}
	for (int i = 0; i < grid_to_allocate.rows; i++) {
		grid_to_allocate.data[i] = (int *) malloc(grid_to_allocate.cols * sizeof(int));
		if (grid_to_allocate.data[i] == NULL) {exit(1);}
	}
}