# 1Q

# Clone https://github.com/FastCGI-Archives/fcgi2
# Set FASTCGI environment variable to its root directory (In VS Code this is "Cmake: Environment / Environment variables to set when running CMake commands." in cmake-tools settings.)
# Copy  `libfcgi++.0.dylib` and `libfcgi.0.dylib` to `lib`
# Build with CMake
# Run with `utils/start.sh`
# Web UI at http://localhost:8080/?pretty
# Enqueue with http://localhost:8080/?enqueue=### where ### is any unsigned 64-bit integer
# Dequeue with http://localhost:8080/?dequeue