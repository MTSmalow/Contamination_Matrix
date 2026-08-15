#include "matrix.h"

void	display_matrix(t_grid *grid)
{
	int	i;
	int	j;

	printf("\nCurrent population state:\n");
	i = 0;
	while (i < grid->size)
	{
		j = 0;
		while (j < grid->size)
		{
			printf("%d ", grid->cells[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	count_contaminated(t_grid *grid)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < grid->size)
	{
		j = 0;
		while (j < grid->size)
		{
			if (grid->cells[i][j] == 1)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	is_fully_contaminated(t_grid *grid)
{
	int	i;
	int	j;

	i = 0;
	while (i < grid->size)
	{
		j = 0;
		while (j < grid->size)
		{
			if (grid->cells[i][j] == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
