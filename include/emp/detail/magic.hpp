#pragma once

#if defined(__GNUC__) && !defined(__MINGW32__) // GCC on Unix-like systems
# define EMP_PLUGIN_EXPORT __attribute__((visibility("default")))
#elif defined(_MSC_VER)
# define EMP_PLUGIN_EXPORT __declspec(dllexport)
#elif defined(__MINGW32__)
# define EMP_PLUGIN_EXPORT __attribute__((dllexport))
#else
# error No EMP_PLUGIN_EXPORT definition available
#endif

// Visual Studio 2008 x86
#if _MSC_VER == 1500 && defined(_M_IX86)
# define EMP_PLUGIN_MAGIC     0xd63ab7ef
# define EMP_PLUGIN_MAGIC_2   0xd63ab7fe
# define EMP_PLUGIN_MAGIC_QT  0xd63ab7ee
// Visual Studio 2010 x86
#elif _MSC_VER == 1600 && defined(_M_IX86)
# define EMP_PLUGIN_MAGIC    0xd63ab7f0
# define EMP_PLUGIN_MAGIC_2  0xd63ab7ff
# define EMP_PLUGIN_MAGIC_QT 0xd63ab70f
// Visual Studio 2013 x86
#elif _MSC_VER == 1800 && defined(_M_IX86)
# define EMP_PLUGIN_MAGIC    0xd63ab7c0
# define EMP_PLUGIN_MAGIC_2  0xd63ab7cf
# define EMP_PLUGIN_MAGIC_QT 0xd63ab7ca
// Visual Studio 2013 x64
#elif _MSC_VER == 1800 && defined(_M_X64)
# define EMP_PLUGIN_MAGIC    0x9f3ed4c0
# define EMP_PLUGIN_MAGIC_2  0x9f3ed4cf
# define EMP_PLUGIN_MAGIC_QT 0x9f3ed4ca
// Visual Studio (2015 - 2019) x86
#elif _MSC_VER >= 1900 && defined(_M_IX86)
# define EMP_PLUGIN_MAGIC    0xa9b8c7c0
# define EMP_PLUGIN_MAGIC_2  0xa9b8c7cf
# define EMP_PLUGIN_MAGIC_QT 0xa9b8c7ca
// Visual Studio (2015 - 2019) x64
#elif _MSC_VER >= 1900 && defined(_M_X64)
# define EMP_PLUGIN_MAGIC    0x1f2e3dc0
# define EMP_PLUGIN_MAGIC_2  0x1f2e3dcf
# define EMP_PLUGIN_MAGIC_QT 0x1f2e3dca
// Generic plugin magic values for platforms
// where we do not officially plugins other
// than "link".
#else
# define EMP_PLUGIN_MAGIC    0xf4573570
# define EMP_PLUGIN_MAGIC_2  0xf457357f
# define EMP_PLUGIN_MAGIC_QT 0xf457357a
#endif

#define EMP_PLUGIN_VERSION 2
