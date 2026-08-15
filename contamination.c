#include "matrix.h"

void	insert_patient_zero(t_grid *grid)
{
	int	row;
	int	col;

	row = rand() % grid->size;
	col = rand() % grid->size;
	grid->cells[row][col] = 1;
	printf("Patient zero inserted at position [%d][%d]\n", row, col);
}

int	count_infected_neighbors(t_grid *grid, int i, int j)
{
	int	count;
	int	n;

	count = 0;
	n = grid->size;
	if (i > 0 && grid->cells[i - 1][j] == 1)
		count++;
	if (i < n - 1 && grid->cells[i + 1][j] == 1)
		count++;
	if (j > 0 && grid->cells[i][j - 1] == 1)
		count++;
	if (j < n - 1 && grid->cells[i][j + 1] == 1)
		count++;
	if (i > 0 && j > 0 && grid->cells[i - 1][j - 1] == 1)
		count++;
	if (i > 0 && j < n - 1 && grid->cells[i - 1][j + 1] == 1)
		count++;
	if (i < n - 1 && j > 0 && grid->cells[i + 1][j - 1] == 1)
		count++;
	if (i < n - 1 && j < n - 1 && grid->cells[i + 1][j + 1] == 1)
		count++;
	return (count);
}

void	update_cell(t_sim *sim, int i, int j)
{
	int		neighbors;
	float	probability;
	float	random_value;

	if (sim->grid.cells[i][j] == 1)
		return ;
	neighbors = count_infected_neighbors(&sim->grid, i, j);
	probability = neighbors * sim->rate;
	random_value = (float)rand() / RAND_MAX;
	if (random_value < probability)
		sim->new_grid.cells[i][j] = 1;
}

void	spread_contamination(t_sim *sim)
{
	int	i;
	int	j;

	grid_copy(&sim->new_grid, &sim->grid);
	i = 0;
	while (i < sim->grid.size)
	{
		j = 0;
		while (j < sim->grid.size)
		{
			update_cell(sim, i, j);
			j++;
		}
		i++;
	}
	grid_copy(&sim->grid, &sim->new_grid);
}
