#!/usr/bin/env python3
"""Build and verify the virtual-memory manager with generated test data."""

from __future__ import annotations

import os
from pathlib import Path
import re
import subprocess
import tempfile


ADDRESSES = [0, 257, 514, 0, 771, 257, 65535, 514]
TRANSLATION_PATTERN = re.compile(
    r"Logical address: (\d+), Physical address: (\d+), Value: (-?\d+)"
)


def backing_value(page: int, offset: int) -> int:
    return (page * 37 + offset * 13 + 17) % 256


def signed_byte(value: int) -> int:
    return value if value < 128 else value - 256


def expected_translations() -> list[tuple[int, int, int]]:
    frames: dict[int, int] = {}
    expected = []

    for logical_address in ADDRESSES:
        page, offset = divmod(logical_address, 256)
        frame = frames.setdefault(page, len(frames))
        physical_address = frame * 256 + offset
        expected.append(
            (logical_address, physical_address, signed_byte(backing_value(page, offset)))
        )

    return expected


def main() -> None:
    project_dir = Path(__file__).resolve().parent
    compiler = os.environ.get("CC", "cc")

    with tempfile.TemporaryDirectory(prefix="os-vmm-test-") as temporary:
        test_dir = Path(temporary)
        executable = test_dir / "virtual_memory_manager"

        subprocess.run(
            [
                compiler,
                "-std=c11",
                "-Wall",
                "-Wextra",
                "-pedantic",
                str(project_dir / "virtual_memory_manager.c"),
                "-o",
                str(executable),
            ],
            check=True,
        )

        backing_store = bytes(
            backing_value(page, offset)
            for page in range(256)
            for offset in range(256)
        )
        (test_dir / "BACKING_STORE.bin").write_bytes(backing_store)
        (test_dir / "addresses.txt").write_text(
            "".join(f"{address}\n" for address in ADDRESSES), encoding="ascii"
        )

        result = subprocess.run(
            [str(executable), "addresses.txt"],
            cwd=test_dir,
            check=True,
            capture_output=True,
            text=True,
        )

    actual = [
        tuple(map(int, match.groups()))
        for match in TRANSLATION_PATTERN.finditer(result.stdout)
    ]
    assert actual == expected_translations(), (actual, expected_translations())
    assert "Page fault rate: 62.50%" in result.stdout
    assert "TLB hit rate: 37.50%" in result.stdout

    print("HW4 verification passed: 8 translations, 5 page faults, 3 TLB hits")


if __name__ == "__main__":
    main()
