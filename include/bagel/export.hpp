
#ifndef BAGEL_EXPORT_H
#define BAGEL_EXPORT_H

#ifdef BAGEL_STATIC_DEFINE
#  define BAGEL_EXPORT
#  define BAGEL_NO_EXPORT
#else
#  ifndef BAGEL_EXPORT
#    ifdef bagel_EXPORTS
        /* We are building this library */
#      define BAGEL_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define BAGEL_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef BAGEL_NO_EXPORT
#    define BAGEL_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef BAGEL_DEPRECATED
#  define BAGEL_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef BAGEL_DEPRECATED_EXPORT
#  define BAGEL_DEPRECATED_EXPORT BAGEL_EXPORT BAGEL_DEPRECATED
#endif

#ifndef BAGEL_DEPRECATED_NO_EXPORT
#  define BAGEL_DEPRECATED_NO_EXPORT BAGEL_NO_EXPORT BAGEL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef BAGEL_NO_DEPRECATED
#    define BAGEL_NO_DEPRECATED
#  endif
#endif

#endif /* BAGEL_EXPORT_H */
