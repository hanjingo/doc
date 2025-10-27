# File systems — concise guide

[TOC]

This note summarizes core file-system concepts from a programmer's perspective: the file abstraction, directories and inodes, block allocation and free-space management, metadata and consistency (journaling), common system-call APIs, caching and performance trade-offs, and security considerations. It complements the CS:APP material with a practical overview you can use when reading code or designing storage layout.

## 1. The file abstraction

Files present a nameable, byte-addressable view of persistent data. From the programmer's viewpoint a file supports operations such as create, open, read, write, truncate, rename, and delete. The file-system implementation maps these high-level operations to on-disk structures, I/O requests, and kernel data structures.

Key concepts:
- Namespace: directories map human-readable names to file objects.
- Metadata: each file has metadata (size, timestamps, permissions, owner, link count) separate from its content.
- Persistent storage: file contents are stored on devices (disks, SSDs, remote storage) and survive process termination.

## 2. Inodes and directory entries

Many Unix-like file systems use the inode model:

- Inode: an on-disk record that stores metadata and pointers (direct, indirect) to data blocks. Inodes are identified by inode numbers (ino).
- Directory: a special file that contains mappings from filename → inode number. Directory operations (lookup, create, unlink) manipulate directory entries and inode link counts.

Separation of name and object:
- A file can have multiple hard links (multiple directory entries pointing to the same inode). Removing a name decrements the inode link count; the inode is freed only when link count reaches zero and no process has it open.

## 3. Block allocation and addressing

Files are stored in fixed-size blocks (commonly 4 KiB). Typical allocation strategies:

- Contiguous allocation: simple, fast sequential access but leads to fragmentation.
- Linked allocation: blocks linked together in a list (simple but poor random access).
- Indexed allocation (inode-based): inode stores direct pointers to a small number of blocks and indirect pointers to blocks that contain more pointers (common in ext2/ext3).

Block addressing in inodes often mixes direct, single-indirect, double-indirect, and sometimes triple-indirect pointers to handle both small and large files efficiently.

## 4. Free-space management

Common free-space structures:
- Free lists / bitmaps: track which blocks are free; bitmaps are compact and efficient for large devices.
- B-trees or extent trees: record contiguous runs of blocks (extents) for more efficient allocation and less fragmentation (used by modern filesystems like XFS, ext4 extents, Btrfs).

Allocation policies:
- First-fit / best-fit / next-fit for block selection.
- Allocation tries to keep related blocks (same file or directory) close to reduce seek/migration costs.

## 5. Consistency: crashes, journaling, and fsck

File systems must remain consistent after crashes or power failures. Approaches:

- Simple write ordering: carefully order writes so metadata is never left in an inconsistent state; hard to get right and slow.
- Journaling: write intent records to a journal (log) before applying changes. On crash recovery, the filesystem replays or discards incomplete transactions.
	- Metadata journaling: only metadata changes are journaled (fast, safe for structure consistency).
	- Full data journaling: both data and metadata journaled (slower, safer for applications that rely on synchronous semantics).
- Copy-on-write (COW): writing creates new versions of blocks and atomically updates pointers (used by ZFS, Btrfs) which simplifies atomicity and enables snapshots.

After an unclean shutdown, fsck (file-system check) inspects on-disk structures and repairs inconsistencies; journaling reduces the need for long fsck runs.

## 6. Namespaces, links, and special files

- Hard links: multiple directory entries for the same inode; only supported for files, not typically for directories (to avoid cycles).
- Symbolic (soft) links: special files containing a pathname that the kernel resolves at lookup time; they can point across filesystems.
- Special files (device nodes, FIFOs, sockets) provide interfaces to devices and IPC and are represented in the filesystem namespace.

## 7. File-system APIs and semantics

Common system calls and semantics (POSIX): `open`, `read`, `write`, `lseek`, `fsync`, `close`, `unlink`, `rename`, `stat`, `mkdir`, `rmdir`.

Important semantics to be aware of:
- Atomic rename: `rename` is atomic with respect to other pathname operations (helps implement safe updates).
- `fsync` forces dirty data and metadata to persistent storage — required for durability guarantees.
- When files are memory-mapped (`mmap`), writes may be buffered and flushed later; `msync` and `msync(MS_SYNC)` provide control over persistence.

## 8. Caching and performance

Kernel caches dramatically affect performance:

- Page cache / buffer cache: keep recently accessed file data in RAM to serve reads and coalesce writes.
- Metadata caches: name-to-inode caches (dentry/dircache) speed up path lookups.

Performance trade-offs and optimizations:
- Read-ahead: predict and fetch future blocks to reduce latency for sequential reads.
- Write-back vs write-through: write-back delays flushes for efficiency but risks data loss on crash unless combined with journaling.
- Coalescing small writes into larger requests reduces I/O overhead.

Storage-media considerations:
- HDDs: minimize seeks; allocate contiguous blocks and tune layout for locality.
- SSDs: avoid excessive write amplification; prefer large sequential writes and use wear-leveling–aware allocation strategies.

## 9. Security and permissions

- POSIX permissions (rwx for owner/group/other) and ACLs control access.
- File ownership and setuid/setgid bits affect privilege behavior when executing programs.
- Mount options (noexec, nosuid, nodev) restrict executable or device access on mounted filesystems.

## 10. Advanced features (brief)

- Snapshots: point-in-time views implemented via copy-on-write or metadata tricks.
- Quotas: limit space/inode usage per user or group.
- Encryption at rest: filesystem-level or block-level encryption for confidentiality.

## 11. Tools and inspection

Useful tools for inspection and debugging:
- `df`, `du` — usage summaries.
- `stat`, `ls -l` — metadata and permissions.
- `tune2fs`, `dumpe2fs`, `debugfs` (ext filesystems) — low-level inspection.
- `xfs_info`, `btrfs`-specific tools for other filesystems.

## Summary

File systems expose a simple program-facing abstraction built on complex structures: metadata, block allocation, free-space tracking, caching, and consistency mechanisms. Choosing the right filesystem and tuning depends on workload characteristics (large files vs many small files, random vs sequential I/O, SSD vs HDD) and durability requirements.

## Reference

[1] Randal E. Bryant, David R. O'Hallaron. Computer Systems: A Programmer's Perspective. 3rd ed.

---

If you'd like, I can:
- Add a worked example showing inode block addressing for a large file (direct/indirect pointers).
- Provide a short `dd` + `strace` demo showing caching and write-back behavior.
