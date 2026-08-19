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

static int	check_flag(int argc, char **argv, char *flag)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!strcmp(argv[i], flag))
			return (1);
		i++;
	}
	return (0);
}

static void	print_help(void)
{
	printf("\n╔════════════════════════════════════════════╗\n");
	printf("║   Contamination Matrix Simulator - Help    ║\n");
	printf("╚════════════════════════════════════════════╝\n\n");
	printf("USAGE:\n");
	printf("  ./programa [OPTIONS]\n\n");
	printf("OPTIONS:\n");
	printf("  --color      Enable colored output (red for contaminated, green for safe)\n");
	printf("  --text       Show only text output (no grid display)\n");
	printf("  --final      Show only the final state\n");
	printf("  --help       Show this help message\n\n");
	printf("COMBINATIONS:\n");
	printf("  ./programa --final --color      (final state with colors)\n");
	printf("  ./programa --final --text       (final state text only)\n");
	printf("  ./programa --final              (final state default)\n\n");
}

int	main(int argc, char **argv)
{
	t_sim	sim;
	int		n;
	int		colored;
	int		text_only;
	int		final_only;

	if (check_flag(argc, argv, "--help"))
	{
		print_help();
		return (0);
	}
	srand(time(NULL));
	colored = check_flag(argc, argv, "--color");
	text_only = check_flag(argc, argv, "--text");
	final_only = check_flag(argc, argv, "--final");
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
	if (!final_only)
	{
		printf("\nCycle 0 (Initial):\n");
		display_matrix(&sim.grid, colored, text_only);
	}
	run_simulation(&sim, colored, text_only, final_only);
	cleanup_grids(&sim);
	return (0);
}
