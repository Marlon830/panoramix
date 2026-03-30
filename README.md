# Panoramix

> Made by **Marlon PEGAHI**

A multi-threaded producer-consumer simulation in C, based on the Asterix universe. Panoramix the druid brews magic potion for Gaulish villagers who need strength to fight Romans, implemented with POSIX threads and semaphores.

---

## Concept

The simulation models a classic **producer-consumer** problem:

- **Panoramix (producer)** — sleeps until the pot is empty, then wakes up and refills it
- **Villagers (consumers)** — each runs on its own thread, fights Romans, drinks potion to regain strength, and repeats until it has won enough fights
- When the pot runs dry, the first villager to notice wakes up the druid; if there are no refills left, every villager goes home

---

## Requirements

- GCC
- POSIX threads (`pthreads`)

---

## Build

```sh
make        # Build the panoramix binary
make re     # Full rebuild
make fclean # Remove all build artifacts and binaries
```

---

## Usage

```sh
./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>
```

| Argument | Description |
|---|---|
| `nb_villagers` | Number of villager threads |
| `pot_size` | Number of servings the pot holds per brew |
| `nb_fights` | Number of fights each villager must win |
| `nb_refills` | Number of times Panoramix can refill the pot |

All arguments must be strictly positive integers.

### Example

```sh
./panoramix 3 5 4 2
```

Three villagers, each needing to win 4 fights. The pot holds 5 servings and can be refilled twice.

Sample output:
```
Druid: I'm ready... but sleepy...
Villager 0: Going into battle!
Villager 1: Going into battle!
Villager 2: Going into battle!
Villager 0: I need a drink... I see 5 servings left.
Villager 0: Take that roman scum! Only 3 left.
...
Villager 2: I'm going to sleep now.
```

---

## Architecture

```
panoramix/
├── include/
│   ├── panoramix.h       # Core structs and thread function declarations
│   ├── displays.h
│   └── error_gestion.h
├── src/
│   ├── main.c
│   ├── p_panoramix/
│   │   ├── panoramix.c   # Thread initialization and lifecycle management
│   │   ├── villager.c    # Villager thread logic
│   │   └── druid.c       # Druid thread logic
│   ├── displays/
│   └── error_gestion/
└── tests/
    └── tests_main.c
```

**Synchronization primitives:**
- `pthread_mutex_t` — protects the shared pot state (servings count, refill count, cooking flag)
- `sem_t sem1` — villager → druid signal (pot is empty)
- `sem_t sem2` — druid → villagers signal (pot is refilled)
