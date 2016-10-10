#ifndef view_functions_h_DEFINED
#define view_functions_h_DEFINED

double compute_angle_of_elevation(double elevation1, double elevation2, double distance);
double interpolate_elevation_horizontal(double col, int row, grid &elevation_grid);
double interpolate_elevation_vertical(double row, int col, grid &elevation_grid);
int is_visible_left(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col);
int is_visible_right(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col);
int is_visible_up(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col);
int is_visible_down(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col);
int is_visible_q1(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col);
int is_visible_q2(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col);
int is_visible_q3(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col);
int is_visible_q4(grid &elevation_grid, int vp_row, int vp_col, int ep_row, int ep_col);
void compute_viewshed(grid &elevation_grid, grid &viewshed_grid, int vp_row, int vp_col);

#endif