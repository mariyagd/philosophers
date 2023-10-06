# philosophers2

Each philo is represented with a structure `t_philo philo`. All philos are in a circular linked list.
Each fork is repreented with a `pthread_mutex_t mx_fork`.
Each philo has it left fork `philo->mx_fork` and his rigth fork is in `philo->next->mx_fork`

<img width="1141" alt="Screen Shot 2023-10-06 at 12 20 28 PM" src="https://github.com/mariyagd/philosophers2/assets/109855801/09339537-2269-44d7-a385-846d5b533cc3">

