#include "matrix.h"

void	display_matrix(t_grid *grid, int colored, int text_only)
{
	int	i;
	int	j;

	if (text_only)
		return ;
	printf("\nCurrent population state:\n");
	i = -1;
	while (++i < grid->size)
	{
		j = -1;
		while (++j < grid->size)
		{
			if (colored)
			{
				if (grid->cells[i][j] == 1)
					printf("\x1b[48;2;255;70;70m 1 \x1b[0m");
				else
					printf("\x1b[48;2;100;255;120m 0 \x1b[0m");
			}
			else
				printf("%d ", grid->cells[i][j]);
		}
		printf("\n");
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
