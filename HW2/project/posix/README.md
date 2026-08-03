# CPU scheduling

This directory contains implementations of five CPU-scheduling algorithms:

- first-come, first-served (`fcfs`)
- shortest job first (`sjf`)
- round robin (`rr`)
- priority (`priority`)
- priority with round robin (`priority_rr`)

Build every scheduler with `make`, or build one target such as `make fcfs`.
Each executable accepts a CSV workload containing a task name, priority, and
CPU burst:

```sh
./fcfs sample_tasks.txt
./rr sample_tasks.txt
```

`sample_tasks.txt` is an original workload created for this public repository.
The driver, list, virtual CPU, headers, and build file are an original harness
that replaces the course-provided scaffold.
