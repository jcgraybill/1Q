# 1Q

1. Clone https://github.com/FastCGI-Archives/fcgi2
2. Set FASTCGI environment variable to its root directory (In VS Code this is "Cmake: Environment / Environment variables to set when running CMake commands." in cmake-tools settings.)
3. Copy  `libfcgi++.0.dylib` and `libfcgi.0.dylib` to `lib`
4. Build with CMake
5. Run with `utils/start.sh`
6. Web UI at http://localhost:8080/?pretty
7. Enqueue with http://localhost:8080/?enqueue=### where ### is any unsigned 64-bit integer
8. Dequeue with http://localhost:8080/?dequeue