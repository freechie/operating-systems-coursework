# Operating Systems Coursework

This repository collects student-authored source-code exercises and selected
submitted work from an operating systems course. It is curated for public
source control: standalone course handouts, textbooks, lecture materials,
screenshots, compiled programs, and instructor-provided test data are not
included.

## Contents

- `HW1`: C programs using processes, pipes, and POSIX shared memory, plus the
  submitted work PDF
- `HW2`: CPU-scheduling implementations with an original C harness and sample
  workload, plus the submitted work PDF
- `HW3`: Producer-consumer and page-offset C programs
- `HW4`: Virtual-memory-manager C program with a self-contained regression test

## Quick verification

Each project can be built independently. Two useful checks are:

```sh
make -C HW2/project/posix
python3 HW4/test_virtual_memory_manager.py
```

The HW4 test generates its backing store and logical addresses in a temporary
directory, so no publisher-provided binary fixture is required.

## Provenance

The scheduling algorithms and homework solutions are the student's coursework.
Small build harnesses, sample inputs, documentation, and regression tests were
written for this public version of the repository. The retained submission PDFs
are portfolio artifacts and may contain third-party assignment prompts or
excerpts.

## License

The student-authored code and supporting repository material are available
under the [MIT License](LICENSE). The license does not grant rights to any
third-party prompts, excerpts, or other material embedded in the submitted
work PDFs; those portions remain subject to their respective owners' rights.
