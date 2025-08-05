### Dining Philosophers on Raspberry Pi

This project implements the [Dining Philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in C++ on a Raspberry Pi, using multithreading and GPIO pins to control LEDs. Each philosopher is represented by a thread, and their states (thinking, eating, sleeping) are visualized by LEDs connected to GPIO pins. The program prevents deadlock using a fork-ordering strategy and supports configurable parameters.

### Features

- **Multithreading**: Uses `std::thread` and `std::mutex` for concurrent philosopher actions.
- **Deadlock Prevention**: Alternates fork pickup order for odd/even philosophers to avoid circular wait.
- **GPIO Integration**: Controls LEDs via `libgpiod` (LED on for thinking, blinking for eating, off for sleeping).
- **Configurable Parameters**: Set number of philosophers, time to die, eat, sleep, and meal limits via command-line arguments.

### Demo

Watch the video rpiDiner.mp4 to see the philosophers in action on a Raspberry Pi, with LEDs indicating their states.

### Prerequisites

#### Hardware
- Raspberry Pi (e.g., Raspberry Pi 4).
- LEDs connected to GPIO pins 22, 16, 18, 19, 26 (for up to 5 philosophers).
- Resistors (220–330 ohms) for each LED.
- Breadboard and jumper wires.

#### Software
- C++17 compiler.
- `libgpiod`: Install with `sudo apt update && sudo apt install libgpiod-dev`.

### Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/yourrepository.git
   cd yourrepository
   ```

2. **Connect LEDs**:
   - Connect an LED (with resistor) to each GPIO pin (22, 16, 18, 19, 26).
   - Ground each LED to a GND pin on the Raspberry Pi.

3. **Compile the Program**:
   ```bash
   make all
   ```

### Usage

Run the program with command-line arguments:
```bash
./diningPhilosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
```

- `<number_of_philosophers>`: 1–5 (limited by GPIO pins).
- `<time_to_die>`: Milliseconds before a philosopher starves (e.g., 800).
- `<time_to_eat>`: Milliseconds spent eating (LED blinks, e.g., 200).
- `<time_to_sleep>`: Milliseconds spent sleeping (LED off, e.g., 200).
- `<number_of_times_each_philosopher_must_eat>`: Meals per philosopher (-1 for unlimited).

**Example**:
```bash
./diningPhilosophers 5 800 300 300 4
