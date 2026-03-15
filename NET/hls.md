English | [中文版](hls_zh.md)

# HLS (HTTP Live Streaming) Protocol

[TOC]



## References
* [HLS Protocol Analysis](https://www.cnblogs.com/jimodetiantang/p/9133564.html)
* [HTTP Live Streaming draft-pantos-http-live-streaming-18](https://tools.ietf.org/html/draft-pantos-http-live-streaming-18)
* [Detailed Explanation of m3u8 and ts Stream Formats in HLS](https://my.oschina.net/u/727148/blog/666824)

## Components
* Transport Protocol: HTTP
* Index File: M3U8
* Audio/Video Data Container: TS

## Encoding Requirements
* Video: H264
* Audio: AAC, MP3, AC-3
* Audio/Video Data Container: ts
* Index File: m3u8

## Playback
### Apple: Use Safari browser to directly open the m3u8 address, for example:
```
http://demo.srs.com/live/livestream.m3u8
```

### Android: Use the HTML5 video tag, then open this page in the browser
```
<!-- livestream.html -->
<video width="640" height="360"
		autoplay controls autobuffer 
		src="http://demo.srs.com/live/livestream.m3u8"
		type="application/vnd.apple.mpegurl">
</video>
```

## m3u8
An m3u file encoded in UTF-8. This file itself cannot be played; it is just a text file storing playback information. The structure is as follows:
1. #EXTM3U	
    
	> The first line of every m3u8 file must be this tag
    
2. #EXTINF 
	> Specifies the duration of each media segment (ts), affected by GOP. This tag is only valid for the following URI. Each pair of media segment URIs is separated by this tag. The format is:
	```
	#EXTINF:<duration>,<title>
    
	duration: indicates the duration (seconds)
	```
    
3. #EXT-X-BYTERANGE
	> Indicates that the media segment is a segment within a media URI resource, only valid for the following media URI. The format is:
	```
	#EXT-X-BYTERANGE:<n>[@o]
    
	n: indicates the size of this range
	o: indicates the offset in the URI
	```

4. #EXT-X-TARGETDURATION:
	> Specifies the maximum duration (in seconds) of a single slice (i.e., ts) file in the current video stream. Therefore, the time length specified in #EXTINF must be less than or equal to this maximum value. This tag can only appear once in the entire Playlist file (in nested cases, it usually appears in the m3u8 with actual ts URLs). The format is:
	```
	#EXT-X-TARGETDURATION:<s>
    
	s: indicates the maximum number of seconds
	```

5. #EXT-X-MEDIA-SEQUENCE:
	> Each media URI in the Playlist has a unique sequence number, incremented by 1 between adjacent ones. The format is:
	```
	#EXT-X-MEDIA-SEQUENCE:<number>
    
	A media URI is not required to contain this; if not present, the default is 0.
	```

6. #EXT-X-KEY:
	> Indicates how to decode media segments. Its scope is all media URIs until the next occurrence of this tag. The format is:
	```
	#EXT-X-KEY:<attribute-list>
    
	If it is: NONE, then the URI and IV attributes must not exist. If it is AES-128 (Advanced Encryption Standard), then the URI must exist, and IV may be absent.
    
	For AES-128, the keytag and URI attributes together indicate a key file, which can be obtained via the URI. If there is no IV (Initialization Vector), the sequence number is used as the IV for encoding/decoding, assigning the high bits of the sequence number to a 16-byte buffer, left-padded with 0; if there is an IV, it is treated as a 16-byte hexadecimal number.
	```

7. #EXT-X-PROGRAM-DATE-TIME:
	> Associates an absolute time or date with the first sample in a media segment, only valid for the next media URI. The format is:
	```
	#EXT-X-PROGRAM-DATE-TIME:<YYYY-MM-DDThh:mm:ssZ>
    
	Example: #EXT-X-PROGRAM-DATE-TIME:2010-02-19T14:54:23.031+08:00
	```

8. #EXT-X-ALLOW-CACHE:
	> Indicates whether caching is allowed. This can appear anywhere in the Playlist file, but at most once, and affects all media segments. The format is:
	```
	#EXT-X-ALLOW-CACHE:<YES|NO>
	```

9. #EXT-X-PLAYLIST-TYPE:
	> Provides information about the mutability of the Playlist. This applies to the entire Playlist file and is optional. The format is:
	```
	#EXT-X-PLAYLIST-TYPE:<EVENT|VOD>
    
	VOD: Video on demand. The server cannot change the Playlist file; in other words, all ts files for the video have already been generated.
    
	EVENT: Real-time generation of m3u8 and ts files. The server cannot change or delete any part of the Playlist file, but can add new lines. Its index file is always dynamically changing, and playback requires continuously downloading secondary index files.
	```

10. #EXT-X-ENDLIST:
    
	> Indicates the end of the m3u8 file. Live m3u8 does not have this tag. It can appear anywhere in the Playlist, but only once.
    
11. #EXT-X-MEDIA:
	> Used in the Playlist to indicate different language/translation versions of the same content. For example, three of these tags can indicate three different audio languages, or two can indicate different video angles. This tag exists independently in the Playlist. The format is:
	```
	#EXT-X-MEDIA:<attribute-list>
    
	The attribute list includes: URI, TYPE, GROUP-ID, LANGUAGE, NAME, DEFAULT, AUTOSELECT.
    
	URI: If absent, indicates that the selectable version described by this tag exists in the main Playlist's EXT-X-STREAM-INF.
    
	TYPE: AUDIO and VIDEO
    
	GROUP-ID: MEDIA tags with the same ID form a group
    
	LANGUAGE: identifies the primary language used in the rendition
    
	NAME: The value is a quoted-string containing a human-readable description of the rendition. If the LANGUAGE attribute is present, this description SHOULD be in that language
    
	DEFAULT: YES or NO, default is No. If YES, the client will play this option unless the user chooses otherwise
    
	AUTOSELECT: YES or NO, default is No. If YES, the client will select based on the current playback environment (if the user has not chosen a preference)
    
	The EXT-X-MEDIA tag appeared in version 4 of the protocol.
	```

12. #EXT-X-STREAM-INF:
	> Specifies a media URI containing multimedia information as a Playlist, generally used for m3u8 nesting. It is only valid for the immediately following URI. The format is:
	```
	#EXT-X-STREAM-INF:<attribute-list> Common attributes are:
    
	BANDWIDTH: Bandwidth, required
    
	PROGRAM-ID: A decimal integer uniquely identifying a specific description within the Playlist file. A Playlist file may contain multiple such tags with the same ID
    
	CODECS: Specifies the stream's encoding type, not required
    
	RESOLUTION: Resolution
    
	AUDIO: This value must match the GROUP-ID attribute value of the AUDIO category in the "EXT-X-MEDIA" tag
    
	VIDEO: Same as above
	```

13. #EXT-X-DISCONTINUITY:
	> When this tag is encountered, the following properties have changed:
	```
	file format
	number and type of tracks
	encoding parameters
	encoding sequence
	timestamp sequence
	```

14. #ZEN-TOTAL-DURATION:
    
	> Indicates the total duration of ts files contained in this m3u8

### m3u8 Multi-bitrate Support
```
Secondary m3u8 file:
#EXTM3U
#EXT-X-VERSION:3
#EXT-X-ALLOW-CACHE:YES
#EXT-X-MEDIA-SEQUENCE:2
#EXT-X-TARGETDURATION:16
#EXTINF:14.357, no desc
livestream-2.ts
#EXTINF:15.617, no desc
livestream-3.ts
#EXTINF:14.358, no desc
livestream-4.ts
#EXTINF:15.618, no desc
livestream-5.ts
#EXTINF:11.130, no desc
livestream-6.ts

Top-level m3u8 file:
#EXTM3U
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=1280000
http://example.com/low.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=2560000
http://example.com/mid.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=7680000
http://example.com/hi.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=65000,CODECS="mp4a.40.5"
http://example.com/audio-only.m3u8
```
