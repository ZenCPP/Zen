#ifndef ZEN_CONFIG_H
#define ZEN_CONFIG_H

#include <stdio.h>
#include <stdlib.h>

#if !defined(ZEN_ENABLE_ASSERTIONS) && !defined(NDEBUG)
# define ZEN_ENABLE_ASSERTIONS 1
#endif

#if !defined(ZEN_NAMESPACE_START)
#define ZEN_NAMESPACE_START namespace zen {
#endif

#if !defined(ZEN_NAMESPACE_END)
#define ZEN_NAMESPACE_END }
#endif

#define ZEN_AUTO_SIZE (-1)

// TODO use an enumeration
#define ZEN_COULD_NOT_OPEN_FILE 1

#define ZEN_NODISCARD [[nodiscard]]

#define ZEN_CONCATENATE(s1, s2)     s1##s2
#define ZEN_EXPAND_THEN_CONCATENATE(s1, s2) ZEN_CONCATENATE(s1, s2)

/// \brief Generate an unique identifier upon expansion
///
/// A call to this macro will be replaced with an identifier containing the
/// given prefix and a 'randomly' generated index. To avoid collisions, never
/// declare an identifier with the same prefix as the one given to this macro.
#ifdef __COUNTER__
#define ZEN_UNIQUE_IDENTIFIER(prefix) ZEN_EXPAND_THEN_CONCATENATE(prefix, __COUNTER__)
#else
#define ZEN_UNIQUE_IDENTIFIER(prefix) ZEN_EXPAND_THEN_CONCATENATE(prefix, __LINE__)
#endif
#else

/// \brief Add some initialization code that will be run before main()
///
/// The implementation is quite hackish but should not contain any non-standard
/// behavior. The implementation should be thread-safe, but the order in which
/// different blocks are run is undefined. Never assume initialization of a
/// specific structure inside another `ZEN_STATIC_BLOCK`. There are other
/// facilities for that, such as a factory functions or an extended `main()`.
///
/// ```
/// ZEN_STATIC {
///   fprintf(stderr, "Starting application ...\n");
/// }
/// ```
#define ZEN_STATIC_BLOCK ZEN_STATIC_BLOCK_IMPL1(ZEN_UNIQUE_IDENTIFIER(_static_block_))

#define ZEN_STATIC_BLOCK_IMPL1(prefix) \
  ZEN_STATIC_BLOCK_IMPL2(ZEN_CONCATENATE(prefix,_fn),ZEN_CONCATENATE(prefix,_var))

#define ZEN_STATIC_BLOCK_IMPL2(function_name,var_name) \
  static void function_name(); \
  static int var_name __attribute((unused)) = (function_name(), 0) ; \
  static void function_name()

#endif // #ifndef ZEN_CONFIG_H
