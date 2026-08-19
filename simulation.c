#include "matrix.h"

static void	print_progress(t_sim *sim, int cycle, int colored, int text_only)
{
	int	total;
	int	infected;

	total = sim->grid.size * sim->grid.size;
	infected = count_contaminated(&sim->grid);
	printf("\nCycle %d:\n", cycle);
	display_matrix(&sim->grid, colored, text_only);
	printf("Contaminated people: %d of %d (%.2f%%)\n",
		infected, total, (float)infected / total * 100);
}

static void	printfr(t_sim *sim, int cycle, int done, int colored, int text_only)
{
	int	total;
	int	infected;

	total = sim->grid.size * sim->grid.size;
	infected = count_contaminated(&sim->grid);
	if (done)
		printf("\nEntire population contaminated after %d cycles.\n", cycle);
	else
	{
		printf("\nAfter %d cycles, population was not fully contaminated.\n",
			sim->max_cycles);
	}
	if (!text_only)
		printf("\nFinal state:\n");
	display_matrix(&sim->grid, colored, text_only);
	printf("Contaminated people: %d of %d (%.2f%%)\n",
		infected, total, (float)infected / total * 100);
}

void	run_simulation(t_sim *sim, int colored, int text_only, int final_only)
{
	int	cycle;
	int	done;

	cycle = 0;
	done = 0;
	while (cycle < sim->max_cycles && !done)
	{
		cycle++;
		spread_contamination(sim);
		done = is_fully_contaminated(&sim->grid);
		if (!done && !final_only)
			print_progress(sim, cycle, colored, text_only);
	}
	printfr(sim, cycle, done, colored, text_only);
}
