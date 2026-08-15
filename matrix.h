#ifndef MATRIX_H
# define MATRIX_H

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct s_grid
{
	int	**cells;
	int	size;
}	t_grid;

typedef struct s_sim
{
	t_grid	grid;
	t_grid	new_grid;
	float	rate;
	int		max_cycles;
}	t_sim;

t_grid	grid_create(int n);
void	grid_free(t_grid *grid);
void	grid_init(t_grid *grid);
void	grid_copy(t_grid *dest, t_grid *src);

void	display_matrix(t_grid *grid);
int		count_contaminated(t_grid *grid);
int		is_fully_contaminated(t_grid *grid);

void	insert_patient_zero(t_grid *grid);
int		count_infected_neighbors(t_grid *grid, int i, int j);
void	update_cell(t_sim *sim, int i, int j);
void	spread_contamination(t_sim *sim);

void	run_simulation(t_sim *sim);

int		get_params(t_sim *sim, int *n);

#endif
