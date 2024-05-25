#include <bagel/dynamic_library.hpp>

#include <dlfcn.h>

#include <stdexcept>
#include <string>

namespace bagel {

DynamicLibrary::DynamicLibrary(const char* lib_path, int flags) {
    lib_handle_ = dlopen(lib_path, flags);
    if (!lib_handle_) {
        // ok to convert const char* to bulkier std::string since this is an error path
        throw std::invalid_argument("Unable to load library " + std::string(lib_path) + ": " + std::string(dlerror()));
    }
}
DynamicLibrary::~DynamicLibrary() {
    dlclose(lib_handle_);
}

}
