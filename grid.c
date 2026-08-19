#include "matrix.h"

t_grid	grid_create(int n)
{
	t_grid	grid;
	int		i;

	grid.size = n;
	grid.cells = (int **)malloc(n * sizeof(int *));
	if (!grid.cells)
		return (grid);
	i = -1;
	while (++i < n)
	{
		grid.cells[i] = (int *)malloc(n * sizeof(int));
		if (!grid.cells[i])
			break ;
	}
	if (i < n)
	{
		while (i >= 0)
		{
			free(grid.cells[i]);
			i--;
		}
		free(grid.cells);
		grid.cells = NULL;
	}
	return (grid);
}

void	grid_free(t_grid *grid)
{
	int	i;

	i = 0;
	while (i < grid->size)
	{
		free(grid->cells[i]);
		i++;
	}
	free(grid->cells);
}

void	grid_init(t_grid *grid)
{
	int	i;
	int	j;

	i = 0;
	while (i < grid->size)
	{
		j = 0;
		while (j < grid->size)
		{
			grid->cells[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	grid_copy(t_grid *dest, t_grid *src)
{
	int	i;
	int	j;

	i = 0;
	while (i < src->size)
	{
		j = 0;
		while (j < src->size)
		{
			dest->cells[i][j] = src->cells[i][j];
			j++;
		}
		i++;
	}
}
