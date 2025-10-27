# Executable programs — loader and runtime

[TOC]

This note summarizes how executable files (the program image) are organized and how the OS and dynamic loader prepare and run a program. It focuses on practical concepts: executable formats, headers and sections, the dynamic loader (ld.so), symbol resolution and relocation, the program start sequence, and the process memory layout.

## 1. Executable formats (quick overview)

- ELF (Executable and Linkable Format): dominant on Linux/Unix-like systems. Describes both relocatable object files (.o), executables, and shared objects (.so).
- PE (Portable Executable): Windows format.
- Mach-O: macOS format.

This note uses ELF vocabulary (sections, program headers, dynamic section) but the high-level concepts apply across formats.

## 2. File layout: sections vs program headers

- Section headers describe named sections used by linkers and for symbolic information (e.g., `.text`, `.data`, `.bss`, `.symtab`, `.rel.text`). These are useful for link-time tools and debuggers.
- Program headers (PT_ entries) describe segments the loader maps into memory (e.g., loadable segments for code and data). The kernel uses program headers to create the process image.

Key sections you will commonly see:
- `.text` — program code (read-only executable).
- `.rodata` — read-only constants.
- `.data` — initialized writable globals.
- `.bss` — uninitialized globals (zeroed at load).
- `.symtab` / `.strtab` — full symbol table and string table (mainly for linking/debugging).
- `.dynsym` / `.dynstr` — dynamic symbol table used by the dynamic loader.
- `.rela/.rel.*` — relocation records.

## 3. Dynamic loader responsibilities

When the kernel creates a new process from an ELF executable, it maps loadable segments and then transfers control to the program's interpreter (dynamic loader) if one is present (ELF `PT_INTERP` points to e.g. `/lib/ld-linux.so.2`). The dynamic loader (`ld.so`) then:

1. Processes the dynamic section (`.dynamic`) and finds needed shared libraries.
2. Loads shared libraries into memory (if not already mapped).
3. Builds or populates the Global Offset Table (GOT) and Procedure Linkage Table (PLT) structures for lazy/eager binding.
4. Performs relocations that cannot be deferred (e.g., relative relocations or PLT stubs when eager binding is requested).
5. Runs initialization routines (DT_INIT, constructors, `.init_array`) in dependency order.
6. Transfers control to the program start (`_start` / entry point).

On program exit, finalizers (DT_FINI / `.fini_array`) run in reverse order.

## 4. Symbols and relocation

- `.dynsym` contains the symbols the dynamic loader uses to resolve references at runtime.
- Relocations come in two styles: `REL` (without addend) and `RELA` (with explicit addend). ELF on x86-64 uses `RELA`.
- Typical relocation targets:
  - Absolute addresses that must be fixed to runtime load addresses.
  - GOT/PLT entries for inter-library calls (supporting lazy binding).

Lazy vs eager binding:
- Lazy binding: the first time a PLT entry is invoked, the dynamic loader resolves the symbol and patches the PLT/GOT so subsequent calls go directly to the target.
- Eager binding (e.g., `LD_BIND_NOW=1` / link-time flags): resolve all symbols at program startup, which increases startup cost but avoids runtime lookups.

## 5. Program start: crt, `_start`, and libc initialization

Typical startup sequence on Unix-like systems:

1. Kernel maps the ELF segments and sets up the initial stack (argv, envp, auxiliary vector `auxv`).
2. Kernel transfers control to the ELF interpreter (dynamic loader) if present, or directly to the program entry point for statically linked binaries.
3. The loader performs relocations and initialization, then calls the C runtime startup (`crt0`), which:
   - prepares `argc`, `argv`, `envp`, and `auxv` for `main`,
   - calls global constructors (C++ `.init_array`),
   - calls `main`, and
   - on `main` return, runs destructors and exits via `_exit`/`exit`.

Understanding this chain explains where `main` sits and why constructors/destructors run before/after it.

## 6. Process memory layout at runtime

Typical virtual address layout (growing down or up depending on architecture and OS):

- Low addresses: program text (code) and read-only data.
- Middle: heap (grows upward via `brk`/`sbrk` or uses `mmap` allocations).
- High addresses: stack (grows downward); thread stacks for additional threads.
- Shared library mappings are placed by the loader (often in high memory regions).
- Memory-mapped files (mmap) can appear throughout the address space.

See `res/runtime_mem.png` (if present) for a diagram.

## 7. Dynamic linking lifecycle and performance

Startup cost sources:
- Disk I/O to load shared libraries and their pages.
- Relocation work (symbol lookups, writing GOT/PLT entries).
- Constructor execution (C++ static initialization can be expensive).

Performance techniques:
- Use `-fPIC` / `-fPIE` appropriately for shared objects and position-independent executables.
- Reduce exported symbol set (use visibility attributes) so the dynamic loader searches fewer candidates.
- Use prelinking or preloading strategies (platform-specific) to reduce runtime relocation.
- Consider `LD_BIND_NOW` when you prefer deterministic startup cost over runtime resolution overhead.
- Prefer `mmap`-friendly data layouts to reduce page faults during startup.

## 8. Security and reliability features

- ASLR (Address Space Layout Randomization) randomizes base addresses for executable mappings to harden against exploits.
- NX / DEP marks pages non-executable to prevent executing data.
- RELRO and full RELRO strengthen relocation handling (partial RELRO leaves GOT writable; full RELRO makes GOT read-only after relocations).

## 9. Inspecting executables

Useful tools:
- `readelf -h -l -d` — inspect ELF header, program headers, and dynamic section.
- `objdump -x` / `objdump -T` — dump symbols and sections.
- `ldd` — list dynamic dependencies (note: `ldd` may execute the loader; use `readelf` for safer inspection).

## 10. Summary

An executable is more than code bytes: it includes metadata (headers, sections, and dynamic info) that the kernel and loader use to produce a running process. Key runtime steps: map segments, run dynamic loader (if needed), perform relocations, run constructors, and start `main`.

## Reference

[1] Randal E. Bryant, David R. O'Hallaron. Computer Systems: A Programmer's Perspective. 3rd ed.
[2] ELF specification and platform tool documentation (Glibc `ld.so`, binutils/objdump/readelf).
