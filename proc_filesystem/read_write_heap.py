#!/usr/bin/python3
"""read_write_heap: Read and write to the heap of a process"""
import sys
import os
import re

def usage_error():
    """if syntax is incorrect"""
    print("Usage: read_write_heap.py pid search_string replace_string")
    sys.exit(1)

def find_and_replace_in_heap(pid, search_string, replace_string):
    """finds and replaces a string in the heap of a process"""
    try:
        with open(f"/proc/{pid}/maps", "r") as maps_file:
            heap_info = None
            for line in maps_file:
                if "[heap]" in line:
                    heap_info = line
                    break

            if not heap_info:
                print("Heap segment not found.")
                return

            heap_start, heap_end = [int(x, 16) for x in heap_info.split(" ")[0].split("-")]

        with open(f"/proc/{pid}/mem", "rb+") as mem_file:
            mem_file.seek(heap_start)
            heap_data = mem_file.read(heap_end - heap_start)

            search_bytes = search_string.encode('ascii')
            replace_bytes = replace_string.encode('ascii')

            if len(replace_bytes) < len(search_bytes):
                replace_bytes = replace_bytes.ljust(len(search_bytes), b'\x00')
            elif len(replace_bytes) > len(search_bytes):
                print("Replacement string cannot be longer than the search string.")
                return

            offset = heap_data.find(search_bytes)
            if offset == -1:
                print("Search string not found in heap.")
                return

            mem_file.seek(heap_start + offset)
            mem_file.write(replace_bytes)

    except FileNotFoundError:
        print(f"Process with PID {pid} not found.")
    except PermissionError:
        print("Permission denied. Try running as root.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    """initialization"""
    if len(sys.argv) != 4:
        usage_error()

    pid = sys.argv[1]
    search_string = sys.argv[2]
    replace_string = sys.argv[3]

    if not pid.isdigit():
        usage_error()

    find_and_replace_in_heap(pid, search_string, replace_string)