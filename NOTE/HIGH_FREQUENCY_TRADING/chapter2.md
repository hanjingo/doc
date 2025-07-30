# CHAPTER 2 Technological Innovations, Systems, and HFT

[TOC]



![architecture_of_a_sample_multicore_cpu](res/architecture_of_a_sample_multicore_cpu.png)

![architecture_of_a_sample_gpu](res/architecture_of_a_sample_gpu.png)

![architecture_of_a_sample_fpga_chip](res/architecture_of_a_sample_fpga_chip.png)

Performance-wise, FPGAs tend to be superior to GPUs and CPUs, particularly when used to simultaneously process a limited number of time series.

The transmission speed of communication messages depends on several factors:

- Size of message.
- Connection bandwidth.
- TCP/IP and UDP "window" sizes, specifying how many bytes market participants are willing to send and receive at a message "slice".

![core_message_architecture_in_trading](res/core_message_architecture_in_trading.png)

Every stream of quote and trade communication includes the following key messages:

1. `Session start` is the message sent in the beginning of every communication session, sometimes only once a day.
2. `Heartbeat` is a recurrent message that notifies the participant's communication parties that the participant is online, in a state of good technological health, and open for business.
3. `Quote` message is a message carrying quote information, such as best bid and ask prices and sizes.
4. `Order` message is used to transmit actual order information.
5. `Order cancellation` message includes the unique identifier of the previously placed order that now needs to be canceled.
6. `Order acknowledgment` and `order cancellation acknowledgment` messages include confirmations of order placement or order cancellation, respectively.
7. `Execution acknowledgment` messages specify the details of execution: time of excution, obtained price, and execute quantity.
8. `Session end` message informs parties that a given trading entity has stopped trading and quoting for the day.