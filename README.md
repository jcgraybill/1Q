# 1Q

An absurdly simple distributed message broker. Provides a single in-memory FIFO queue, no persistence (messages are lost if the process ends), no batching, message payloads are 64-bit integers, HTTP GET interface, no implementation of messaging standards, no separate ACK function (messages delete as soon as they're consumed), no exchanges or routing, no configuration options. You put numbers in, you get numbers out.

It's a little bit silly. It's not the right solution for many (well, most) (well, probably almost all) use cases. The goal will be to do a pretty good job at its one use case. 

Transport is via FastCGI, so it can be fronted by any FastCGI-compatible HTTP server, such as Apache httpd, lighttpd, or nginx. Delegates all transport concerns to the HTTP server - encryption, authentication, load balancing, you name it.

How to build this. "It works on my laptop." The next work is removing all those hacks so it builds and runs more universally.

1. Clone, build, and install https://github.com/FastCGI-Archives/fcgi2 and https://github.com/lighttpd/spawn-fcgi
2. **HACK** | Set `FASTCGI` environment variable to its root directory (In VS Code this is "Cmake: Environment / Environment variables to set when running CMake commands." in cmake-tools settings.)
3. **HACK** | Copy  `libfcgi++.0.dylib` and `libfcgi.0.dylib` to `lib`
4. Build with CMake
5. Install `nginx`
6. Run with `utils/start.sh`
7. Web UI at http://localhost:8080/?pretty
8. Enqueue with http://localhost:8080/?enqueue=### 
9. Dequeue with http://localhost:8080/?dequeue