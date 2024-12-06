# **Philosophers Project**

This project is an implementation of the classic **Dining Philosophers** problem using threads and mutexes. The simulation involves multiple philosophers sitting around a table with a shared bowl of spaghetti and a set of forks, demonstrating concurrency control, thread synchronization, and resource sharing.

---

## **Table of Contents**

- [Overview](#overview)
- [Key Features](#key-features)
- [Requirements](#requirements)
- [Compilation and Execution](#compilation-and-execution)
- [Program Arguments](#program-arguments)
- [How It Works](#how-it-works)
- [Data Structures and Concurrency](#data-structures-and-concurrency)
- [Logging](#logging)
- [Stopping Conditions](#stopping-conditions)
- [Example](#example)
- [Testing and Debugging](#testing-and-debugging)
- [Notes](#notes)
- [Authors](#authors)

---

## **Overview**

The **Dining Philosophers** is a well-known problem in concurrency and synchronization. Philosophers alternate between three states: eating, sleeping, and thinking. They must use two forks (one to their left and one to their right) to eat. This project simulates these philosophers as threads, coordinating their actions with mutexes to prevent data races, resource conflicts, and deadlocks.

---

## **Key Features**

- **Thread-Based Simulation**: Each philosopher is represented by a thread.
- **Mutex Synchronization**: Forks are protected by mutexes to prevent race conditions.
- **Accurate Timing**: Millisecond precision for eating, sleeping, and timing out.
- **Health Monitoring**: A separate thread monitors philosophers to detect starvation (death).
- **Optional Stopping Condition**: Support for an optional number of meals each philosopher must eat before stopping.

---

## **Requirements**

- A C compiler supporting `pthread`.
- The following external functions are allowed:
  - `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`
  - `pthread_create`, `pthread_detach`, `pthread_join`
  - `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`
  
No global variables are allowed, and all necessary data must be properly passed through structures and function arguments.

---

## **Compilation and Execution**

To compile, navigate to the project directory and run:

```bash
make
```

This will produce an executable named `philo`.

To recompile cleanly:
```bash
make re
```

To remove object files and the executable:
```bash
make fclean
```

---

## **Program Arguments**

**Usage:**
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
- `number_of_philosophers`: The number of philosophers and also the number of forks.
- `time_to_die` (ms): Maximum time a philosopher can remain without eating before dying.
- `time_to_eat` (ms): Time a philosopher spends eating once they have both forks.
- `time_to_sleep` (ms): Time a philosopher spends sleeping after eating.
- `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation ends when each philosopher has eaten at least this many times. If not provided, the simulation ends when a philosopher dies.

**Example:**
```bash
./philo 5 800 200 200 3
```
This sets up:
- 5 philosophers
- Philosophers die if they don’t eat within 800 ms
- Each eating action takes 200 ms
- Each sleeping action takes 200 ms
- The simulation stops once every philosopher has eaten at least 3 times.

If the last argument is omitted, the simulation continues until a philosopher starves.

---

## **How It Works**

1. **Initialization**:
   - The program parses and validates command-line arguments.
   - It initializes all philosophers, their forks (mutexes), and shared resources.
   - A separate health monitor is initialized to track philosophers’ meals and detect starvation.

2. **Thread Creation**:
   - One thread per philosopher is created, each running the philosopher lifecycle:
     - **Thinking**: The philosopher thinks before attempting to take forks.
     - **Taking Forks**: The philosopher tries to pick up the two forks. Mutexes ensure no two philosophers use the same fork simultaneously.
     - **Eating**: Once both forks are acquired, the philosopher eats, updating their last meal time.
     - **Sleeping**: After eating, the philosopher puts down forks and sleeps.
     - The cycle repeats.
   
   - A separate thread runs the **health monitor**:
     - Continuously checks if any philosopher has exceeded `time_to_die` since last eating.
     - If a philosopher dies, the simulation stops.
     - If `number_of_times_each_philosopher_must_eat` is specified, the monitor also checks if all philosophers have eaten enough.

3. **Synchronization**:
   - Forks are protected by mutexes to prevent simultaneous use.
   - A single state mutex protects the shared data (like printing and meal counts).
   
---

## **Data Structures and Concurrency**

- **Philosopher Structure**: Holds individual philosopher data (ID, meal count, timestamps, etc.).
- **Shared Arrays**: Track meals eaten and last meal timestamps for all philosophers.
- **Fork Mutexes**: An array of mutexes, one per fork.
- **State Mutex**: A mutex to protect shared state changes and console printing.

---

## **Logging**

The simulation logs state changes with timestamps (in ms since simulation start) and philosopher IDs:

- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

No two messages intermingle because of synchronization with the state mutex. The death message is printed within at most 10 ms of the philosopher’s actual death.

---

## **Stopping Conditions**

1. **Starvation (Death)**: If any philosopher fails to eat within `time_to_die` ms, they die. The simulation ends immediately.
2. **All Philosophers Well-Fed (Optional)**: If `number_of_times_each_philosopher_must_eat` is provided and all philosophers have eaten at least that many times, the simulation ends gracefully.

---

## **Example**

**Run**:
```bash
./philo 5 800 200 200
```

**Possible Log Output (partial)**:
```
0   1 is thinking
0   2 is thinking
0   3 is thinking
0   4 is thinking
0   5 is thinking
10  2 has taken a fork
10  2 is eating
...
```

The actual output will vary due to concurrency and timing. If a philosopher does not get a fork in time and starves, you might see:
```
...
1000 3 died
```

---

## **Testing and Debugging**

- **Run multiple scenarios**: Test with different numbers of philosophers and timing parameters.
- **Check edge cases**:
  - 1 philosopher scenario.
  - Very short `time_to_die` relative to `time_to_eat` (ensures death occurs).
  - Provide `number_of_times_each_philosopher_must_eat` and verify simulation stops correctly.
- **Debugging**:
  - Use print statements or logs to track philosopher states and timing.
  - Review thread synchronization carefully if you encounter deadlocks.

---

## **Notes**

- No global variables are used; all data is passed through structures and pointers.
- Proper cleanup ensures that mutexes are destroyed, and memory is freed before exiting.
- The solution aims to avoid deadlocks and starvation through timing and careful synchronization.

---

**Enjoy simulating the Dining Philosophers Problem!**