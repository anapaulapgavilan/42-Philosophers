# Philosophers

![42](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42&logoColor=white) ![Language](https://img.shields.io/badge/lang-C%20%2B%20pthreads-blue?style=flat-square) ![Status](https://img.shields.io/badge/status-completed-success?style=flat-square)

Concurrency project based on threads and synchronization in C.

## About This Project

### What It Does

Philosophers simulates the classic dining philosophers problem: a configurable number of philosophers sit at a round table, alternating between thinking, eating (which requires picking up the two forks/mutexes next to them), and sleeping, for as long as the simulation parameters allow.

A supervising loop continuously checks whether any philosopher has gone too long without eating (which would mean they starved) or whether all philosophers have eaten enough times, and stops the simulation as soon as either condition is met, printing a timestamped log of every philosopher's state changes along the way.

### Purpose

It evaluates multithreading and synchronization in C: creating and coordinating threads, protecting shared resources (the forks) with mutexes to avoid data races, and preventing deadlock/starvation in a classic concurrency problem, all while keeping timing precise enough to detect starvation correctly.

## Stack

- School: 42
- Primary language: C + pthreads
- Scope: one repository per project

## Skills Demonstrated

`Multithreading` | `Mutex synchronization` | `Deadlock/starvation avoidance` | `Precise timing`

## Features

- Configurable dining-philosophers simulation with per-philosopher threads
- Fork access protected by mutexes to avoid data races
- Starvation/deadlock avoidance with precise, timestamped state logging

## Review Focus

- Look for synchronized access to shared forks and shared simulation state.
- Review starvation detection timing and whether logging remains consistent under concurrency.
- Notice how deadlock avoidance is designed instead of patched after the fact.

## Project Deep Dive

Philosophers is a concurrency project where correctness depends on timing and synchronization. Each philosopher acts independently, but shared forks and shared simulation state require careful locking to avoid races, deadlocks, and inconsistent logs.

The project is small enough to inspect but hard enough to reveal real concurrency thinking. A reviewer can evaluate whether starvation detection is reliable, whether locks are held for the minimum necessary time, and whether the simulation exits cleanly.

## Implementation Notes

- Represents philosophers as concurrent workers coordinated by shared timing rules.
- Protects shared fork access and simulation state with mutexes.
- Uses timestamped logging and monitor logic to stop on death or completion conditions.

## How to Run

Prerequisites: `make`, a C compiler, and POSIX threads (`pthread`, available by default on Linux/macOS).

~~~bash
cd philo
make
./philo 4 410 200 200
~~~

Format: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_count]

## Testing

No dedicated testing scripts were detected at the project root.

## Notes

- This repository is part of the 42 portfolio.
- Commands are intended for local execution for review and evaluation.

## Author

anapaulapgavilan
