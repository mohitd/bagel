#include <dlfcn.h>

#include <bagel/export.hpp>

namespace bagel {

/**
 * @brief RAII wrapper around dynamic loading for shared objects
 * 
 * This class provides an RAII wrapper around the dynamic loader
 * library functions (dlopen, dlclose, dlsym) used to load dynamic
 * libraries at runtime and fetch symbols from them.
 */
class BAGEL_EXPORT DynamicLibrary {
public:
    /**
     * @brief Default constructor
     */
    DynamicLibrary() = default;
    /**
     * @brief Loads the shared object with the specified flags
     * @param lib_path Path to the shared object
     * @param flags Flags to pass to dlopen
     */
    DynamicLibrary(const char* lib_path, int flags);
    /**
     * @brief Copy constructor
     */
    DynamicLibrary(const DynamicLibrary&) = default;
    /**
     * @brief Move constructor
     */
    DynamicLibrary(DynamicLibrary&&) noexcept = default;
    /**
     * @brief Copy assignment
     */
    DynamicLibrary& operator=(const DynamicLibrary&) = default;
    /**
     * @brief Move assignment
     */
    DynamicLibrary& operator=(DynamicLibrary&&) noexcept = default;

    /**
     * @brief Destructor
     * 
     * This closes the dynamic library
     */
    ~DynamicLibrary();

    /**
     * @brief Return a symbol from the library
     * @tparam T type of symbol to return
     * @param symbol_name name of symbol to lookup
     * @return symbol from library
     */
    template<typename T>
    T sym(const char* symbol_name) const noexcept {
        return (T) dlsym(lib_handle_, symbol_name);
    }

private:
    /// Handle for the dynamic library
    void* lib_handle_{nullptr};
};

}
