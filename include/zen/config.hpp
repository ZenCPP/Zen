#ifndef ZEN_CONFIG_HPP

#ifndef ZEN_EXCEPTIONS_ENABLED

#ifdef __cpp_exceptions
#define ZEN_EXCEPTIONS_ENABLED 1
#else
#define ZEN_EXCEPTIONS_ENABLED 0
#endif

#endif // #ifdef ZEN_EXCEPTIONS_ENABLED

#endif // ZEN_CONFIG_HPP
