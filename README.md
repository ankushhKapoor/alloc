
# Alloc - Custom Memory Allocator in C

*A minimal educational memory allocator built for learning low-level memory operations in C.*

---

##  Overview

This project is a lightweight memory allocator built from scratch using C. It simulates memory allocation, deallocation, and block management using custom headers. Inspired by operating system fundamentals and low-level programming, the allocator supports **32-bit systems**.

> Think of this like a `malloc`/`free` simulation on a fixed-size memory region—but with your own logic!

---

##  Features

 **Manual Allocation:** `alloc(bytes)` allocates space from a virtual heap  
 **Secure Deallocation:** `destroy(ptr)` frees memory **and zeroes out its content**, making it safer than a plain `free`  
 **Memory Block Management:** Splits, reuses, and zeroes freed blocks efficiently  
 **Compact Header Format:** 32-bit packed headers with `w` (size) and `alloced` flags  
 **Error Handling:** All failures routed via `errno` and custom error codes  
 **Live Debugging:** Use `show()` to print the current memory layout  
 **Custom Unit Macros:** Allocate in KB, MB, or GB using `allock(x)`, `allocm(x)`, and `allocg(x)`

---

##  How It Works

- All memory exists in a **virtual 1 GB region** pointed to by `memspace`
- Memory is managed in **words**, where **1 word = 4 bytes**
- `alloc(bytes)` takes size in **bytes**, but internally allocates in **words**
- Each memory block starts with a **packed header** storing size and allocation status
- Freed blocks are wiped (`zero()`) and marked as reusable
- New allocations scan for suitable free blocks before expanding heap

---

##  Directory Structure

```

.
├── alloc.c         # Core logic
├── alloc.h         # Macros, typedefs, interface
├── heap.asm        # Initializes virtual heap memory
├── Makefile        # Build system

````
---

## Example Usage

# Input in C File

```c
int8 *p1 = alloc(7);
int8 *p2 = alloc(2000);
destroy(p2);
int8 *p3 = alloc(10);
int8 *p4 = alloc(1996);

show();
```

# Output

Using `show();` reveals:

```
0x56611014 Alloc 1 = 2 alloced words
0x56611020 Alloc 2 = 499 alloced words
Empty header at 0x566117ec, moving on
0x566117f4 Alloc 4 = 3 alloced words
```
Note:
The allocator reuses the memory freed by p2 when allocating p4. This demonstrates effective block recycling using your custom header logic.
---

##  Summary

| Function          | Description                                                      |
| ----------------- | ---------------------------------------------------------------- |
| `alloc(int32)`    | Allocates memory from the heap. Returns a `void *` like `malloc` |
| `destroy(void *)` | Frees a block and **zeros** its memory (safer than `free`)       |
| `show()`          | Prints memory layout with size and status of all blocks          |
| `allock(x)`       | Allocates `x` KB of memory (`x * 1024` bytes)                    |
| `allocm(x)`       | Allocates `x` MB of memory (`x * 1024 * 1024` bytes)             |
| `allocg(x)`       | Allocates `x` GB of memory (`x * 1024 * 1024 * 1024` bytes)      |

---

##  Memory Details

*  Maximum virtual memory allowed: **\~1 GB**
*  Allocator supports dynamic allocation until memory runs out
*  Exceeding limits or double freeing will trigger appropriate `errno` values

---

##  Error Codes

| Code         | Meaning                     |
| ------------ | --------------------------- |
| `ErrNoErr`   | Success                     |
| `ErrNoMem`   | Out of memory               |
| `ErrUnknown` | Unknown error               |
| `Err2xFree`  | Double free / Invalid free  |

---

##  Planned Enhancements

*  Fix edge case where a header with size `ZeroWords` is created and wasted

---

##  Credits

This project is inspired by a tutorial by **Dr. Jonas Birch** on [YouTube](https://www.youtube.com/@dr-Jonas-Birch), a phenomenal programmer whose resources deeply shaped this implementation.

Key contributions from his work include:

* Type definitions and casting macros (`$1`, `$v`, `$h`, etc.)
* Foundational heap setup logic in `heap.asm` 

Although inspired by his work, this is **not a copy-paste implementation**.
The entire allocator was **understood, redesigned, and written independently** to ensure full conceptual clarity.

Explore his original resources here: [https://repo.doctorbirch.com/](https://repo.doctorbirch.com/)

---

>  Feedback, suggestions, or improvements? Feel free to open an issue or discussion!
