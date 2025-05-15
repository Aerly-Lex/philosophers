
---

# 🍝 Philosophers

Welcome to the Philosophers project repository! This project is part of the 42 curriculum and explores the classic concurrency problem known as the Dining Philosophers. The objective is to prevent deadlocks and ensure that each philosopher can eat without conflicts, using threads and mutexes for synchronization.

## Features

- **Thread-based simulation**: Each philosopher is represented by a separate thread.
- **Mutex synchronization**: Forks are represented by mutexes to prevent simultaneous access.
- **Deadlock prevention**: Implements strategies to avoid deadlocks and starvation.
- **Customizable parameters**: Allows configuration of the number of philosophers and timing constraints.

## Technologies Used

- **C**: Core programming language for simulation logic.
- **POSIX Threads (pthreads)**: Manages concurrent execution of philosopher threads.
- **Mutexes**: Ensures synchronized access to shared resources (forks).

## Getting Started

To compile and run the simulation:

```bash
make
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

Replace the arguments with appropriate values to configure the simulation.  
The argument in square brackets is optional.

i.e.  
./philosophers 5 800 200 200 5  
./philosophers 40 800 200 200
