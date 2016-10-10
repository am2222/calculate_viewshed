

double interpolate_elevation_vertical(double row, int col, grid &elevation_grid) {

	// variables and equations below explained..
	//m is the slope of elevation, between the two points containing 'row' inside
	//	calculated by looking at floor(row) and ceiling(row)
	//return value is the slope times the vertical displacement from floor to actual, plus the 'original' elevation
	//   essentially y = mx + b


	double m = elevation_grid.data[int(ceil(row))][col] - elevation_grid.data[int(floor(row))][col];
	return m * (row - floor(row)) + elevation_grid.data[int(floor(row))][col];
}

double interpolate_elevation_horizontal(double col, int row, grid &elevation_grid) {
	double m = elevation_grid.data[row][int(ceil(col))] - elevation_grid.data[row][int(floor(col))];
	return m * (col - floor(col)) + elevation_grid.data[row][int(floor(col))];
}


double compute_angle_of_elevation(double elevation1, double elevation2, double distance) {
	return atan( (elevation2 - elevation1) / distance );
}



int is_visible_right(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col) {

	double distance1 = sqrt( double(ep_row - vp_row) * (ep_row - vp_row) + double(ep_col - vp_col) * (ep_col - vp_col) );
	double angle1 = compute_angle_of_elevation(elevation_grid.data[vp_row][vp_col], elevation_grid.data[ep_row][ep_col], distance1);

	for (int col = vp_col + 1; col < ep_col; col++) {


		//variables and equations below explained...
		// m is the slope from start viewpoint to end viewpoint (2D)
		// intersection_row is the effective decimal row, calculated using y = mx + b
		//
		double m = (ep_row - vp_row) / double(ep_col - vp_col);
		double intersection_row = m * (col - vp_col) + vp_row;
		double elevation = interpolate_elevation_vertical(intersection_row, col, elevation_grid);

		double distance2 = sqrt( (intersection_row - vp_row) * (intersection_row - vp_row) + (col - vp_col) * (col - vp_col) );
		double angle2 = compute_angle_of_elevation(elevation_grid.data[vp_row][vp_col], elevation, distance2);

		if (angle2 > angle1) {
			return 0;
		}
	}

	return 1;
}

int is_visible_left(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col) {

	double distance1 = sqrt( double(ep_row - vp_row) * (ep_row - vp_row) + double(ep_col - vp_col) * (ep_col - vp_col) );
	double angle1 = compute_angle_of_elevation(elevation_grid.data[vp_row][vp_col], elevation_grid.data[ep_row][ep_col], distance1);

	for (int col = vp_col - 1; col > ep_col; col--) {

		double m = (ep_row - vp_row) / double(ep_col - vp_col);
		double intersection_row = m * (col - vp_col) + vp_row;
		double elevation = interpolate_elevation_vertical(intersection_row, col, elevation_grid);

		double distance2 = sqrt( (intersection_row - vp_row) * (intersection_row - vp_row) + (col - vp_col) * (col - vp_col) );
		double angle2 = compute_angle_of_elevation(elevation_grid.data[vp_row][vp_col], elevation, distance2);

		if (angle2 > angle1) {
			return 0;
		}
	}

	return 1;
}


int is_visible_down(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col) {

	double distance1 = sqrt( double(ep_row - vp_row) * (ep_row - vp_row) + double(ep_col - vp_col) * (ep_col - vp_col) );
	double angle1 = compute_angle_of_elevation(elevation_grid.data[vp_row][vp_col], elevation_grid.data[ep_row][ep_col], distance1);
	for (int row = vp_row + 1; row < ep_row; row++) {

		double m = (ep_col - vp_col) / double(ep_row - vp_row);
		double intersection_col = m * (row - vp_row) + vp_col;
		double elevation = interpolate_elevation_horizontal(intersection_col, row, elevation_grid);

		double distance2 = sqrt( (intersection_col - vp_col) * (intersection_col - vp_col) + (row - vp_row) * (row - vp_row) );
		double angle2 = compute_angle_of_elevation(elevation_grid.data[vp_row][vp_col], elevation, distance2);

		if (angle2 > angle1) {
			return 0;
		}


	}

	return 1;
}


int is_visible_up(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col) {
	double distance1 = sqrt( double(ep_row - vp_row) * (ep_row - vp_row) + double(ep_col - vp_col) * (ep_col - vp_col) );
	double angle1 = compute_angle_of_elevation(elevation_grid.data[vp_row][vp_col], elevation_grid.data[ep_row][ep_col], distance1);
	for (int row = vp_row - 1; row > ep_row; row--) {

		double m = (ep_col - vp_col) / double(ep_row - vp_row);
		double intersection_col = m * (row - vp_row) + vp_col;
		double elevation = interpolate_elevation_horizontal(intersection_col, row, elevation_grid);

		double distance2 = sqrt( (intersection_col - vp_col) * (intersection_col - vp_col) + (row - vp_row) * (row - vp_row) );
		double angle2 = compute_angle_of_elevation(elevation_grid.data[vp_row][vp_col], elevation, distance2);

		if (angle2 > angle1) {
			return 0;
		}
	}

	return 1;

}


int is_visible_q1(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col) {

	int check1 = is_visible_right(elevation_grid, vp_row, vp_col, ep_row, ep_col);
	if (check1 == 0) {return check1;}

	int check2 = is_visible_up(elevation_grid, vp_row, vp_col, ep_row, ep_col);
	return check2;
}


//checks all places where LOS intersects vertical grid lines
//quadrant 2
int is_visible_q2(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col) {

	int check1 = is_visible_left(elevation_grid, vp_row, vp_col, ep_row, ep_col);
	if (check1 == 0) {return check1;}

	int check2 = is_visible_up(elevation_grid, vp_row, vp_col, ep_row, ep_col);
	return check2;
}

//checks all places where LOS intersects vertical grid lines
//quadrant 3
int is_visible_q3(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col) {

	int check1 = is_visible_left(elevation_grid, vp_row, vp_col, ep_row, ep_col);
	if (check1 == 0) {return check1;}

	int check2 = is_visible_down(elevation_grid, vp_row, vp_col, ep_row, ep_col);
	return check2;
}

//checks all places where LOS intersects vertical grid lines
//quadrant 4
int is_visible_q4(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col) {

	int check1 = is_visible_right(elevation_grid, vp_row, vp_col, ep_row, ep_col);
	if (check1 == 0) {return 0;}

	int check2 = is_visible_down(elevation_grid, vp_row, vp_col, ep_row, ep_col);
	return check2;
}
