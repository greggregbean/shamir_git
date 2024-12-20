#include <cerrno>
#include <cstring>
#include <iostream>

namespace shagit {
[[noreturn]] void AssertionFail(const char* expr, const char* file, unsigned line,
                                const char* function) {
    int errnum = errno;
    std::cerr << "ASSERTION FAILED: " << expr << std::endl;
    std::cerr << "IN " << file << ":" << std::dec << line << ": " << function << std::endl;
    if (errnum != 0) {
        std::cerr << "ERRNO: " << errnum << " (" << std::strerror(errnum) << ")" << std::endl;
    }
    std::abort();
}

} // namespace shagit