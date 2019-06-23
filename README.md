# Meadow simulation
Multithreaded meadow simulation using C++17 and CLion IDE. The was project created for a university course on operating systems (Wrocław University of Science and Technology).

In this simulation there are animals that can eat, drink water and think. It is done in a loop until an animal is alive. Conditional variables were used to synchronize threads.

**Threads**:
- Cow (eats grass),
- Rabbit (eats grass and can be eaten by a wolf),
- Wolf (hunts only at night),
- Sun (day and night cycle).

**Resources**:
- Pond (animals can drink water),
- Rabbit Hole (rabbits try to escape there when hunted by a wolf),
- Grass (eaten by cows and rabbits).

## Images
An example of a simulation state at the beginning:
![Beginning of the simulation](https://raw.githubusercontent.com/jastka4/meadow-simulation/assets/1.png)

An example of a simulation state at night:
![Simulation at night](https://raw.githubusercontent.com/jastka4/meadow-simulation/assets/2.png)