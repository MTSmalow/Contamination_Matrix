#include "matrix.h"

int	get_params(t_sim *sim, int *n)
{
	printf("Enter matrix size (n for an nxn matrix): ");
	if (scanf("%d", n) != 1)
		return (0);
	printf("Enter contamination rate (value between 0 and 1): ");
	if (scanf("%f", &sim->rate) != 1)
		return (0);
	printf("Enter maximum number of cycles: ");
	if (scanf("%d", &sim->max_cycles) != 1)
		return (0);
	if (*n <= 0 || sim->rate < 0 || sim->rate > 1 || sim->max_cycles <= 0)
		return (0);
	return (1);
}

static void	cleanup_grids(t_sim *sim)
{
	if (sim->grid.cells)
		grid_free(&sim->grid);
	if (sim->new_grid.cells)
		grid_free(&sim->new_grid);
}

int	main(void)
{
	t_sim	sim;
	int		n;

	srand(time(NULL));
	if (!get_params(&sim, &n))
	{
		printf("Invalid parameters. Please run the program again.\n");
		return (1);
	}
	sim.grid = grid_create(n);
	sim.new_grid = grid_create(n);
	if (!sim.grid.cells || !sim.new_grid.cells)
	{
		printf("Memory allocation failed.\n");
		cleanup_grids(&sim);
		return (1);
	}
	grid_init(&sim.grid);
	insert_patient_zero(&sim.grid);
	printf("\nCycle 0 (Initial):\n");
	display_matrix(&sim.grid);
	run_simulation(&sim);
	cleanup_grids(&sim);
	return (0);
}
