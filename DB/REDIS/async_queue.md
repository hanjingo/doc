English | [中文版](ansys_queue_zh.md)

# Building an Asynchronous Queue with Redis

[TOC]


## Summary

You can implement an asynchronous queue using Redis primitives such as `zset`, `list` and Pub/Sub.

- Use a `zset` as a delayed/scheduled queue (score = scheduled timestamp).
- Use a `list` to store queue payloads (actual messages or IDs).
- Use Pub/Sub to notify workers when new messages are available.

This combination provides delayed delivery, durable storage (depending on persistence), and push notifications for consumers.
