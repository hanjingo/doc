# DB Storage

[TOC]



## DB System Structure

![system_structure](res/system_structure.png)



## Storage Device

### Hierarchy

![storage_device_hierarchy](res/storage_device_hierarchy.png)

### Disk

![disk_mechanism](res/disk_mechanism.png)

The main measures of the qualities of a disk are capacity, access time, data-transfer rate, and reliability:

- `Access time` is the time from when a read or write request is issued to when data transfer begins. 
- The `average seek time` is the average of the seek times, measured over a sequence of (uniformly distributed) random requests.
- Once the head has reached the desired track, the time spent waiting for the sector to be accessed to appear under the head is called the `rotational latency time`.
- The `data transfer rate` is the rate at which data can be retrieved from or stored to the disk.
- The final commonly used measure of a disk is the `mean time to failure (MTTF)`, which is a measure of the reliability of the disk. The mean time to failure of a disk (or of any other system) is the amount of time that, on average, we can expect the system to run continuously without any failure.

### Redundant Arrays Of Independent Disks (RAID)

![raid_lvl](res/raid_lvl.png)

- `RAID level 0` refers to disk arrays with striping at the level of blocks, but without any redundancy (such as mirroring or parity bits).
- `RAID level 1` refers to disk mirroring with block striping.
- `RAID level 2`, known as memory-style error-correcting-code (ECC) organization, employs parity bits. 
- `RAID level 3`, bit-interleaved parity organization.
- `RAID level 4`, block-interleaved parity organization.
- `RAID level 5`, block-interleaved distributed parity.
- `RAID level 6`, the $P + Q$ redundancy scheme, is much like RAID level 5, but stores extra redundant information to guard against multiple disk failures.

## Data Abstraction

![data_abstraction](res/data_abstraction.png)

- `Physical level`. The lowest level of abstraction describes `how` the data are actually stored. 
- `Logical level`. The next-higher level of abstraction describes `what` data are stored in the database, and what relationships exist among those data. 
- `View level`. The highest level of abstraction describes only part of the entire database.



## Indexing

![dense_index](res/dense_index.png)

![sparse_index](res/sparse_index.png)



## File Organization

File organization in DBMS refers to the method of storing data records in a file so they can be accessed efficiently. It determines how data is arranged, stored, and retrieved from physical storage.

### Types

Some types of File Organizations are: 

- Sequential File Organization
- Heap File Organization
- Clustered File Organization
- ISAM (Indexed Sequential Access Method)
- Hash File Organization
- B+ Tree File Organization

### Sequential File Organization

In this method, the file is stored one after another in a sequential manner. There are two ways to implement this method:

1. Pile File Method

   ![pile_file_method](res/pile_file_method.png)

   This method is quite simple, in which we store the records in a sequence, i.e., one after the other, in the order in which they are inserted into the tables.

2. Sorted File Method

   ![sorted_file_method](res/sorted_file_method.png)

   In this method, as the name itself suggests, whenever a new record has to be inserted, it is always inserted in a sorted (ascending or descending) manner. The sorting of records may be based on any primary key or any other key. 

### Heap File Organization

![heap_file_org_insert1](res/heap_file_org_insert1.png)

(before insert)

![heap_file_org_insert2](res/heap_file_org_insert2.png)

(after insert)

Heap File Organization works with data blocks. In this method, records are inserted at the end of the file, into the data blocks. No Sorting or Ordering is required in this method. If a data block is full, the new record is stored in some other block, Here the other data block need not be the very next data block, but it can be any block in the memory. It is the responsibility of DBMS to store and manage the new records. 

### Clustered File Organization

TODO

### ISAM (Indexed Sequential Access Method)

TODO

### Hash File Organization

TODO

### B+ Tree File Organization

TODO



## Reference

[1] Abraham Silberschatz; Henry F. Korth; S. Sudarshan . Database System Concepts. 6ED

[2] [File Organization in DBMS](https://www.geeksforgeeks.org/dbms/file-organization-in-dbms-set-1/)

