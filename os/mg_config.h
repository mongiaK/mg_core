/*================================================================
*  
*  文件名称：mg_config.h
*  创 建 者: mongia
*  创建日期：2022年09月05日
*  邮    箱：mongiaK@outlook.com
*  
================================================================*/

#ifndef __MG_CONFIG_H__
#define __MG_CONFIG_H__

#include "mg_linux_config.h"

typedef int mg_int_t;
typedef int32_t mg_int32_t;
typedef uint32_t mg_uint32_t;
typedef int64_t mg_int64_t;
typedef uint64_t mg_uint64_t;
typedef double mg_double_t;
typedef float mg_float_t;
typedef int8_t mg_int8_t;
typedef uint8_t mg_uint8_t;
typedef int16_t mg_int16_t;
typedef uint16_t mg_uint16_t;
typedef uint8_t mg_bool_t;
typedef char mg_char_t;
typedef unsigned long long mg_time_t;
typedef struct tm mg_tm_t;

typedef int32_t mg_atomic_int_t;
typedef uint32_t mg_atomic_uint_t;
typedef volatile mg_atomic_uint_t mg_atomic_t;


#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#define mg_assert(x) assert(x)
#define mg_posix_memalign posix_memalign
#define mg_malloc malloc
#define mg_free free
#define mg_mprotect mprotect

#ifndef offsetof
#define offsetof(x, member) ((mg_uint32_t) & (((x*)0)->member))
#endif

#ifndef MG_STRUCT_POINT
#define MG_STRUCT_POINT(s, p, member) \
    ((s*)((mg_char_t*)(p)-offsetof(s, member)))
#endif

#ifndef nullptr
#define nullptr NULL
#endif

#define mg_gettimeofday(x) gettimeofday(x, nullptr)

//static int set_nonblock(int fd)
//{
//    int flag;
//    if ((flag = fcntl(fd, F_GETFL)) < 0 ) {
//        return -1;
//    }
//
//    if (fcntl(fd, F_SETFL, flag | O_NONBLOCK) < 0) {
//        return -1;
//    }
//    return 0;
//}
//
//static int set_block(int fd)
//{
//    int flag;
//    if ( (flag = fcntl(fd, F_GETFL)) < 0 ) {
//        return -1;
//    }
//
//    if (fcntl(fd, F_SETFL, flag & (~O_NONBLOCK)) < 0) {
//        return -1;
//    }
//    return 0;
//}


#endif
