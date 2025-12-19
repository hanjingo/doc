English | [中文版](interview_zh.md)

# Interview

[TOC]



## C/C++

### Base

#### Can you describe what the basic structure of a C++ program is?

TODO

#### What is the purpose of comments in C++?

TODO

#### What is the difference between a declaration and a definition of a variable used in C++?

TODO

#### Can you discuss the difference between a local and global scope of a variable?

TODO



---



## System Design

### Photo-Sharing Service

Refer from: https://www.youtube.com/watch?v=5krUGGe8vA4

Design a photo-sharing service that allows users to:

1. Upload a photo to their profile.
2. See the photos uploaded by other users that the user follows.

Functional Requirements:

- User uploaded photos (assumed authenticated) - photo caption, location where photo was taken
- Users can like photos and comment on photos
- User profiles
- Viewing other user profiles (can only see profiles of user's you follow)
- Users can request to follow another user
- Use can view pending follow requests and accept/deny
- Photo feed ordered by most recent
- Follow recommendations up to 3 suggestions for high-profile accounts, i.e. celebrities
- Search for users
- More than 100k followers; automatically flagged as verified

Non-functional requirements:

- Photo limit size 10MB
- 1B DAU
- No limits writes/reads
- 80: 20 read: writes
- High availability / low latency / eventual consistency for photo viewing, commenting, search

Core Entities

- Users (handled Auth Svc)
- Follow
- Photos
- Comments
- VerifiedUsers

For more information, See: [File Sharing Service](SYSTEM_DESIGN/file_sharing_service.md)

---

