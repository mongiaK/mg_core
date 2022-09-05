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

#include "os/linux/mg_linux_config.h"

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
