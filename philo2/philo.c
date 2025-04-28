#include "philo.h"
// ./philo 5 800 200 200 [5];

int	main(int argc, char **argv)
{
	t_table	table;
	if (argc == 5 || argc == 6)
	{
		if (parse_input(&table, argv) == -1) // TODO
			return EXIT_FAILURE;
		// printf("%lu\n", table.philo_nbr);
		// printf("%lu\n", table.time_to_die);
		// printf("%lu\n", table.time_to_eat);
		// printf("%lu\n", table.time_to_sleep);
		data_init(&table); // TODO
		dinner_start(&table); // TODO
		// clean(&table) // TODO


	}
	else
		return 1;
}