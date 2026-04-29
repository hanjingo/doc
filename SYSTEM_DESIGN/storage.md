# Storage In System Design

[TOC]



## Storage System

![storage_system](res/storage_system.jpg)



## Object Store

![object_store_use_case](res/object_store_use_case.png)



## Example 1: Dropbox Multimedia Search

### Indexing Pipeline for Metadata

![dropbox_index_pipeline](res/dropbox_index_pipeline.png)

The data flows through the system in the following way:

- Raw files are stored in a blob store
- Riviera extracts features and metadata from these files
- Information flows through third-party connectors
- Kafka message brokers transport the data
- Transformers process and structure the information
- Finally, everything populates the search index

### Geolocation-Aware Retrieval System

![dropbox_retrieval_system](res/dropbox_retrieval_system.png)

During indexing, when a file contains GPS coordinates in its metadata, Dropbox converts those coordinates into a hierarchical chain of location IDs. For example, a photo taken in San Francisco would generate a chain linking San Francisco to California to the United States. This hierarchy is crucial because it enables flexible searching at different geographic levels.

### Just-In-Time Preview Generation

![dropbox_preview](res/dropbox_preview.png)

When a search returns results, the system generates preview URLs that the frontend can fetch. These URLs point to a preview service built on top of Riviera that generates thumbnails and previews in multiple resolutions on the fly. To avoid repeatedly generating the same preview, the system caches them for 30 days, striking a balance between storage costs and performance.



## Reference

[1] [Block, Object, and File Storage in System Design](https://www.geeksforgeeks.org/system-design/block-object-and-file-storage-in-cloud-with-difference/)

[2] [System Design CheatSheet for Interview](https://medium.com/javarevisited/system-design-cheatsheet-4607e716db5a)

[3] [Modern Storage Systems](https://blog.bytebytego.com/i/184819571/modern-storage-systems)

[4] [Dropbox Multimedia Search: Making File Search More Useful](https://blog.bytebytego.com/p/dropbox-multimedia-search-making)