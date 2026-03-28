# ROS Summary

[TOC]



## CLI

### Nodes

A node is a fundamental ROS2 element that serves a single, modular purpose in a robotics system.

### Topics

Nodes publish information over topics, which allows any number of other nodes to subscribe to an access that information.

### Services

Nodes can communicate using services in ROS2. Unlike a topic - a one way communication pattern where a node publishes information that can be consumed by one or more subscribers - a service is a request/response pattern where a client makes a request to a node providing the service and the service processes the request and generates a response.

### Parameters

Nodes have parameters to define their default configuration values.

### Actions

Actions are like services that allow you to execute long running tasks, provide regular feedback, and are cancelable.

A robot system would likely use actions for navigation. An action goal could tell a robot to travel to a position. While the robot navigates to the position, it can send updates along the way, and then a final result message once it's reached its destination.

### rqt_console

`rqt_console` can be very helpful if you need to closely examine the log messages from your system. You might want to examine log messages for any number of reasons, usually to find out where something went wrong and the series of events leading up to that.

### bag

You can record data passed on topics in your ROS2 using the ros2 bag command.



## Reference

[1] [Understanding nodes](https://docs.ros.org/en/humble/Tutorials/Beginner-CLI-Tools/Understanding-ROS2-Nodes/Understanding-ROS2-Nodes.html#understanding-nodes)

[2] [Understanding topics](https://docs.ros.org/en/humble/Tutorials/Beginner-CLI-Tools/Understanding-ROS2-Topics/Understanding-ROS2-Topics.html)

[3] [Understanding actions](https://docs.ros.org/en/humble/Tutorials/Beginner-CLI-Tools/Understanding-ROS2-Actions/Understanding-ROS2-Actions.html#understanding-actions)