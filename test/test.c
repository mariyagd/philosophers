#include "philo.h"

int main(int ac, char **av)
{
	t_game game;


	printf("philo id %d\n", game.philo_id);
	printf("philo adress: %p\n", game.philo);
	printf("philo adress: %d\n", game.philo->id);
	game = (t_game){};

	printf("philo id %d\n", game.philo_id);
	printf("philo adress: %p\n", game.philo);
	game.philo = &(t_philo){};
	printf("philo id: %d\n", game.philo->id);

}
