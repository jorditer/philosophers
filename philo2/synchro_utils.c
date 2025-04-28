#include "philo.h"

// while threads not ready don't start
void	wait_all_threads(t_table *table)
{
	while(!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}