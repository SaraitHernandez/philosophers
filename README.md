### **Philosophers Project**

This project is a simulation of the classic Dining Philosophers problem, implemented using threads and mutexes to ensure proper synchronization. Philosophers alternate between eating, sleeping, and thinking, ensuring no philosopher starves and no data races occur.

---

### **Features**
- Simulates a number of philosophers sitting at a round table, sharing forks to eat spaghetti.
- Each philosopher alternates between eating, sleeping, and thinking.
- Accurate time tracking and logs for each state change.
- Synchronization using mutexes to avoid race conditions.
- Detection of starvation, ensuring philosophers do not die unnecessarily.
- Optional argument to specify how many times each philosopher must eat.

---

### **Compilation and Usage**

#### **Compilation**
Run the following command to compile the project:
```bash
make
```

This will create an executable named `philo`.

#### **Usage**
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` (int): The number of philosophers (and forks) at the table.
- `time_to_die` (int): Time in milliseconds a philosopher can live without eating.
- `time_to_eat` (int): Time in milliseconds it takes for a philosopher to eat.
- `time_to_sleep` (int): Time in milliseconds a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional, int): The simulation ends when each philosopher eats this many times. If not specified, the simulation runs until a philosopher dies.

#### **Example**
Run a simulation with 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep, and each philosopher eating at least 3 times:
```bash
./philo 5 800 200 200 3
```

---

### **Output Logs**
The program outputs logs for every philosopher's actions:
- **State changes**:
  ```
  timestamp_in_ms X has taken a fork
  timestamp_in_ms X is eating
  timestamp_in_ms X is sleeping
  timestamp_in_ms X is thinking
  ```
  Where `timestamp_in_ms` is the elapsed time since the start of the simulation, and `X` is the philosopher number.

- **Death detection**:
  ```
  timestamp_in_ms X died
  ```

---

### **Requirements**
- C compiler supporting `pthread`.
- Supported external functions:
  - `memset`, `printf`, `malloc`, `free`, `write`
  - `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`
  - `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`
  - `pthread_mutex_lock`, `pthread_mutex_unlock`

---

### **Structure**
#### **Source Code**
- **Main Program (`main.c`)**: Initializes the simulation and manages threads.
- **Philosopher Actions (`philo_actions.c`)**: Handles eating, sleeping, and thinking states.
- **Philosopher States (`philo_states.c`)**: Manages transitions between states.
- **Thread Management (`philo_threads.c`)**: Handles thread creation and lifecycle.
- **Simulation Initialization (`simulation_init.c`)**: Sets up philosopher data and synchronization.
- **Health Monitoring (`health_monitor.c`)**: Detects starvation or simulation-ending conditions.
- **Utility Functions (`utils.c`)**: Time management, argument validation, and helper functions.

#### **Header File**
- `philosopher.h`: Contains function prototypes, macros, and structure definitions.

#### **Makefile**
- Targets:
  - `all`: Compiles the program.
  - `clean`: Removes object files.
  - `fclean`: Removes object files and the executable.
  - `re`: Cleans and recompiles the project.

---

### **Design Highlights**
- **Mutexes**: Ensure proper access control to forks and shared data.
- **Threads**: Each philosopher is represented by a thread, simulating concurrent actions.
- **Dynamic Allocation**: Memory is allocated dynamically for philosophers and their associated resources.

---

### **Notes**
- The program uses color-coded logs for better visualization of philosopher states.
- The optional `number_of_times_each_philosopher_must_eat` ensures the simulation ends gracefully when all philosophers have eaten enough.
- Proper error handling and validation ensure stability even with incorrect arguments.

---

### **Common Issues**
1. **Philosopher Starvation**: Ensure time values (`time_to_die`, `time_to_eat`, `time_to_sleep`) are balanced to avoid starvation.
2. **Incorrect Arguments**: Use the following format to avoid errors:
   ```
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```
3. **Deadlocks**: Mutexes and thread synchronization are implemented to prevent deadlocks. If deadlocks occur, check the time values provided.

---

### **Authors**
- Developed by [sarherna](mailto:sarait.hernandez@novateva.com) and contributors.

Feel free to modify and improve this project as needed!