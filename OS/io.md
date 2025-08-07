# I/O

[TOC]



Every I/O device, including disks, keyboards, displays, and even networks, is modeled as a file. All input and output in the system is performed by reading and writing files, using a small set of system calls known as `Unix I/O`.

![io_bus](res/io_bus.png)

*I/O Bus*

A `multiplexor`(commonly referred to as a "MUX") selects a value from among a set of different data signals, depending on the value of a control input signal. 



## Reference

[1] Randal E. Bryant, David R. O'Hallaron . COMPUTER SYSTEMS: A PROGRAMMER'S PERSPECTIVE . 3ED
