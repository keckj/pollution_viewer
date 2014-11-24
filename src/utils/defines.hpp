
#ifndef DEFINES_H
#define DEFINES_H

//tout passe en DEBUG avec make debug
//tout passe en WARN avec make release
//par defaut la console est en INFO et le fichier en DEBUG
#ifndef _CONSOLE_LOG_LEVEL
#define _CONSOLE_LOG_LEVEL INFO
#endif

#ifndef _FILE_LOG_LEVEL
#define _FILE_LOG_LEVEL DEBUG
#endif

#if defined(__CUDACC__) // NVCC
   #define ALIGN(n) __align__(n)
#elif defined(__GNUC__) // GCC
  #define ALIGN(n) __attribute__((aligned(n)))
#elif defined(_MSC_VER) // MSVC
  #define ALIGN(n) __declspec(align(n))
#else
  #error "Please provide a definition for ALIGN macro for your host compiler (in utils/defines.hpp) !"
#endif

#endif /* end of include guard: DEFINES_H */
