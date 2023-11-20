# 1Q

An absurdly simple distributed message broker. Provides a single in-memory FIFO queue, no persistence (messages are lost if the process ends), no batching, message payloads are 64-bit integers, HTTP GET interface, no implementation of messaging standards, no separate ACK function (messages delete as soon as they're consumed), no exchanges or routing, no configuration options. You put numbers in, you get numbers out.

It's a little bit silly. It's not the right solution for many (well, most) (well, probably almost all) use cases. The goal will be to do a pretty good job at its one use case. 

Transport is via FastCGI, so it can be fronted by any FastCGI-compatible HTTP server, such as Apache httpd, lighttpd, or nginx. Delegates all transport concerns to the HTTP server - encryption, authentication, load balancing, you name it.

**LIVE DEMO**: https://1q.julesgraybill.com/?pretty

How to build this. *It works on my laptop.* The next work is removing all those hacks so it builds and runs more universally.

1. With your package manager, install `g++ cmake gcc make m4 autoconf automake libtool git nginx`
2. Clone, build, and install https://github.com/FastCGI-Archives/fcgi2 and https://github.com/lighttpd/spawn-fcgi
3. Clone this repo and build it with CMake: `cmake .` then `cmake --build .`
4. Run with `utils/start.sh`
5. The web ui is at http://localhost:8080/?pretty
6. Enqueue with http://localhost:8080/?enqueue=### 
7. Dequeue with http://localhost:8080/?dequeue