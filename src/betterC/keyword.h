#ifndef KEYWORD_H
#define KEYWORD_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define null NULL
typedef FILE file;

#define false 0
#define true  (!false)
typedef int bool;

/*
#define and &&
#define or ||
#define not(x) !(x)
#define is ==*/

typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;


typedef int8_t    int8;
typedef int16_t   int16;
typedef int32_t   int32;
typedef int64_t   int64;


typedef uint8_t   uint8;
typedef uint16_t  uint16;
typedef uint32_t  uint32;
typedef uint64_t  uint64;


typedef intptr_t  nint;
typedef intptr_t  isize;
//typedef intptr_t  ptr;


typedef uintptr_t nuint;
typedef uintptr_t usize;
typedef uintptr_t uintptr;


typedef intmax_t  mint;  // Same size as word
typedef uintmax_t muint; // Same size as word

//typedef uintptr_t uptr;
typedef uint8_t byte;

typedef float  f32;
typedef double f64;

#endif