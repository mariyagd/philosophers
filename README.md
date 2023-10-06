# philosophers2

## 1. Create structures

- All the parameters coming from the command line are stored in the 't_params' structure.
The number of philos and the number of times each philo must eat are stored in `int`, the time is stored in `long`.

- Each philo is represented with a structure `t_philo philo`. All philos are in a circular linked list (this is also simpler to free).
Each fork is repreented with a `pthread_mutex_t mx_fork`.
Each philo has it left fork `philo->mx_fork` and his rigth fork is in `philo->next->mx_fork`

<img width="1141" alt="Screen Shot 2023-10-06 at 12 20 28 PM" src="https://github.com/mariyagd/philosophers2/assets/109855801/09339537-2269-44d7-a385-846d5b533cc3">

- The structure `t_game game` contains all the necessary mutexes for performing the checker routine (the one that will set the exit condition for all threads). It also contains a pointer to the head of the philo's circular linked list (where every philo points to the structure `t_game game`).

<img width="1562" alt="Screen Shot 2023-10-06 at 12 45 55 PM" src="https://github.com/mariyagd/philosophers2/assets/109855801/f7d482e6-d4c8-48b0-bb71-270a3009767a">

 

## 2. Parsing

`parse_arguments(int ac, char **av)`
This function checks:

- the number of arguments is 5 or 6
- arguments are digits
- there is no `-` sign (argument can't be negative`)
- arguments can have only one “+” sign (ex. `+200` is correct but `++200` is incorrect)
- arguments can be preceded by “0” (ex. `000200 = 200` this is automatically transformed by `ft_atoi` and `ft_atol` )
- number of philosophers can't be 0 (it is at least 1)
- !!! the time to die, eat and sleep can be 0 milliseconds (the philo will take a fork and then die)
- the number of philosophers and the number of times each philo must eat are within `INT_MAX` and `INT_MIN`
- the time to die, eat and sleep are within `LONG_MAX` and `LONG_MIN`

## 3. Processing

1) All threads are launched with `pthread_create()` and executes `life_routine()`
2) The `checker_routine()` is launched in the main process (the main thread)
3) All threads are joined with `pthread_join()` so that the main process waits for the termination of each thread before its own termination
4) All mutexes are destroyed with `pthread_mutex_destroy()`, and all memory allocated with `malloc` is freed.
