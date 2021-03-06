#include "stdafx.h"
#include "TPSInterpolate.hpp"

extern "C" __declspec(dllexport) double** interpolate_grid_using_tps(unsigned int input_arr_size, unsigned int control_row_values[], unsigned int control_col_values[], double control_values[], unsigned int output_num_rows, unsigned int output_num_cols)
{
	std::vector<boost::array<double, 2>> positions;
	std::vector<boost::array<double, 1>> values;

	double **grid = new double*[output_num_rows];
	for (size_t row = 0; row < output_num_rows; row++)
	{
		grid[row] = new double[output_num_cols];
	}
	for (size_t i = 0; i < input_arr_size; i++)
	{
		boost::array<double, 2> pos;
		pos[0] = control_row_values[i];
		pos[1] = control_col_values[i];
		positions.push_back(pos);

		boost::array<double, 1> val;
		val[0] = (double)control_values[i];
		values.push_back(val);
	}
	ThinPlateSpline<2, 1> spline(positions, values);
	for (size_t r = 0; r < output_num_rows; r++)
	{
		for (size_t c = 0; c < output_num_cols; c++)
		{
			boost::array<double, 2> grid_pos;
			grid_pos[0] = (double)r;
			grid_pos[1] = (double)c;
			grid[r][c] = spline.interpolate(grid_pos)[0];
		}
	}
	return grid;
}
extern "C" __declspec(dllexport) void delete_2d_array(unsigned int arr_size, double **arr)
{
	for (size_t i = 0; i < arr_size; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}



