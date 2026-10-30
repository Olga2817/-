#pragma once
#include <cstdio>
#include <ctime>

inline void print_current_time() {
    std::time_t now = std::time(nullptr);
    char buf[20];
    if (std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now))) {
        std::fprintf(stderr, "[%s] ", buf);
    }
}

#define LOG_INF(fmt, ...) do { \
    print_current_time(); \
    std::fprintf(stderr, "[INF] | [%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
} while(0)

#define LOG_ERR(fmt, ...) do { \
    print_current_time(); \
    std::fprintf(stderr, "[ERR] | [%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
} while(0)