#include "matrix.h"

static void	print_progress(t_sim *sim, int cycle)
{
	int	total;
	int	infected;

	total = sim->grid.size * sim->grid.size;
	infected = count_contaminated(&sim->grid);
	printf("\nCycle %d:\n", cycle);
	display_matrix(&sim->grid);
	printf("Contaminated people: %d of %d (%.2f%%)\n",
		infected, total, (float)infected / total * 100);
}

static void	print_final_report(t_sim *sim, int cycle, int done)
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
		printf("Contaminated people: %d of %d (%.2f%%)\n",
			infected, total, (float)infected / total * 100);
	}
}

void	run_simulation(t_sim *sim)
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
		if (!done)
			print_progress(sim, cycle);
	}
	print_final_report(sim, cycle, done);
}
