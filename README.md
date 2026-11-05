# Mini libc for Linux x86-64

A minimal implementation of selected **C standard library and POSIX-style functionality** for **Linux x86-64**, written mainly in C with a small amount of x86-64 assembly.

The project explores what normally happens underneath common C library functions such as `malloc`, `read`, `write`, `strlen`, `mmap`, or `stat`. Instead of relying on the system's existing C standard library for these operations, the implementation builds a small library directly on top of the Linux system call interface.

The project also contains its own process startup code, custom header files, memory allocation logic, file operations, string and memory functions, error handling through `errno`, and a static library build process.

The main purpose of the project is to better understand the lower-level mechanisms that make familiar C library functionality possible and the relationship between user-space code, the C runtime, and the Linux kernel.

## System Call Interface

At the lowest level of the project is a generic system call wrapper.

The library defines its own `syscall` function, which receives a system call number followed by its arguments and forwards them to an architecture-specific x86-64 implementation.

This layer is then used by the higher-level library functions instead of calling implementations from an existing libc.

Operations such as file reading, file writing, memory mapping, process termination, file positioning, and filesystem metadata access eventually reach the Linux kernel through this interface.

This creates a clear separation between the public libc-like functions and the kernel services that actually perform the requested work.

The project also includes its own internal definitions for system call numbers and architecture-specific functionality under the `include/internal/arch/x86_64` directory.

Working at this level provides a better understanding of the boundary between user-space programs and the operating system and of the role a standard C library normally plays between the two.

## Process Startup and Runtime Initialization

The project includes a custom application startup path rather than depending entirely on the startup code normally supplied by the host C runtime.

Execution begins in the `_start` symbol, which is implemented in x86-64 assembly.

The startup routine passes the address of `main` to the custom `__libc_start_main` implementation. Before the application enters `main`, the library initializes its internal memory-allocation tracking structure.

After `main` finishes, the runtime performs cleanup and returns the resulting exit code to the startup code. The process is then terminated using the library's own `exit` implementation, which invokes the Linux exit system call directly.

This part of the project demonstrates that `main` is not actually the first instruction executed by a native program. There is a small runtime layer responsible for preparing the environment before the application's main function begins and for handling the final stage of execution when it ends.

The startup code is written in NASM assembly and assembled for the ELF64 format.

## Dynamic Memory and Virtual Memory

The library implements a small set of dynamic memory allocation functions, including `malloc`, `calloc`, `realloc`, `reallocarray`, and `free`.

Memory is obtained from the operating system through Linux virtual-memory operations instead of using an allocator provided by another C library.

The implementation uses `mmap` to obtain memory regions, `mremap` when resizing an existing allocation, and `munmap` when releasing memory.

The project also provides its own wrappers for these virtual-memory operations. These wrappers invoke the corresponding Linux system calls and translate negative kernel return values into libc-style error behavior by updating `errno`.

Allocated regions are tracked internally using a circular doubly linked list.

Each entry stores the starting address of an allocation, its size, and links to the previous and next allocation records. This metadata allows functions such as `free` and `realloc` to locate information associated with a previously allocated address.

The allocation list itself also uses memory mappings for its metadata and is initialized as part of the custom runtime startup process.

This allocator is intentionally simple and focuses on demonstrating how common allocation functions can be constructed using lower-level virtual-memory mechanisms supplied by the operating system.

## File I/O and File Descriptors

A significant part of the library provides familiar file operations directly on top of Linux system calls.

The project includes implementations for functions such as `open`, `close`, `read`, `write`, `lseek`, `truncate`, and `ftruncate`.

These functions operate directly with Linux file descriptors and follow the usual libc-style convention in which successful operations return their result while kernel errors are converted into `-1` and stored in `errno`.

The `read` and `write` functions, for example, invoke their respective system calls and translate negative kernel return values into the conventional user-space interface.

`lseek` provides file-position manipulation, while `truncate` and `ftruncate` expose file-size modification through either a pathname or an existing file descriptor.

A small `puts` implementation is also included. Instead of using a higher-level buffered output system, it determines the length of the supplied string and writes the contents directly to standard output through the system call interface, followed by a newline.

The library additionally contains `sleep` and `nanosleep` functionality built around the Linux nanosleep system call.

Together, these functions demonstrate how many common C and POSIX-style operations are ultimately relatively small wrappers around kernel functionality.

## String and Memory Operations

The project implements a collection of common string-manipulation functions manually instead of relying on the host system's standard library.

The implemented operations include `strlen`, `strcpy`, `strncpy`, `strcat`, `strncat`, `strcmp`, `strncmp`, `strchr`, `strrchr`, `strstr`, and `strrstr`.

These functions work directly with characters, pointers, array indexes, and null terminators.

For example, string comparison functions traverse the supplied strings until a difference or terminating character is encountered, while the search functions manually inspect the input string for characters or substrings.

The project also provides several raw memory operations: `memcpy`, `memmove`, `memcmp`, and `memset`.

These functions operate on untyped memory regions rather than null-terminated strings.

An important distinction can be seen between `memcpy` and `memmove`. While a simple copy can proceed directly when memory regions do not overlap, `memmove` has to account for overlapping source and destination ranges. The implementation chooses the direction of the copy based on the relative positions of the two buffers.

Implementing these functions manually provides practice with pointer arithmetic, byte-level memory manipulation, boundaries, and the behavior expected from some of the most frequently used functions in C programs.

## Filesystem Metadata and Error Handling

The library contains filesystem metadata functions such as `stat` and `fstat`.

Both functions invoke the corresponding Linux system calls directly and expose their results through the familiar `struct stat` interface.

The repository also contains the infrastructure for `fstatat` and `statx`-based metadata conversion. That part is present as a scaffold in the current implementation and is not completed.

Error handling throughout the library follows the traditional libc model.

A custom `errno` value is provided, and wrappers check whether a Linux system call returned a negative error code. When that happens, the positive error number is stored in `errno` and the function returns the conventional error value expected by its public interface.

This translation is important because the raw Linux system call convention and the interface normally presented by libc are not identical.

## Custom Headers and Library Independence

The repository contains its own `include` directory with public and internal header files.

These headers define the types, constants, function declarations, system call information, memory-management structures, and architecture-specific functionality needed by the implementation.

The build uses the `-nostdinc` compiler option and explicitly points GCC to the project's own include directory. As a result, the source files do not simply use the host system's standard include path as their primary interface.

The project is also compiled with `-fno-builtin`, preventing the compiler from automatically replacing calls with built-in assumptions about standard libc functions.

This is particularly important in a project that is trying to implement functions such as `strlen`, `memcpy`, and `malloc` itself.

Stack-protector support is also disabled by the build configuration so that the generated code does not silently depend on runtime functionality that the minimal library does not provide.

Together, these choices make the project much closer to a self-contained runtime exercise than a normal application that simply calls the operating system through an existing C library.

## Project Structure

- `crt/` — x86-64 startup code and the custom `__libc_start_main` implementation
- `include/` — public and internal headers used by the library
- `include/internal/arch/x86_64/` — architecture-specific system call definitions
- `mm/` — dynamic memory allocation, allocation tracking, and virtual-memory wrappers
- `io/` — file I/O, file positioning, truncation, output, and sleep-related functionality
- `string/` — string and raw memory manipulation functions
- `stat/` — filesystem metadata functionality
- `process/` — process-related operations such as `exit`
- `syscall.c` — generic interface used to invoke Linux system calls
- `errno.c` — custom `errno` storage
- `Makefile` — compilation and static-library build configuration

The source code is separated according to the area of libc functionality being implemented, which keeps low-level memory, I/O, string, process, and runtime code logically organized.

## Build

The project is designed for **Linux x86-64** and uses **GCC**, **NASM**, **GNU Make**, and the GNU archiver.

Running `make` compiles the C sources, assembles the custom startup file, and packages the resulting object files into the static library `libc.a`.

The C sources are compiled with options including `-nostdinc`, `-fno-builtin`, `-fno-PIC`, and `-fno-stack-protector`.

The `_start` implementation is assembled by NASM using the ELF64 object format.

The resulting `libc.a` contains the runtime startup code together with the implemented system call wrappers and libc-style functions.

## Technologies and Concepts

- C
- x86-64 Assembly
- Linux
- Linux system calls
- C runtime startup
- Static libraries
- Virtual memory
- `mmap`, `mremap`, and `munmap`
- Dynamic memory allocation
- Doubly linked lists
- File descriptors
- Low-level file I/O
- String manipulation
- Raw memory manipulation
- Pointer arithmetic
- `errno` handling
- Kernel and user-space interaction
- ELF64
- GCC
- NASM
- GNU Make
