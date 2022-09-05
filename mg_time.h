/*================================================================
*
*  文件名称：mg_time.h
*  创 建 者: mongia
*  创建日期：2022年01月25日
*  邮    箱：mr_pengmj@outlook.com
*
================================================================*/
#ifndef __MG_TIME_INCLUDE_H__
#define __MG_TIME_INCLUDE_H__

#include "mg_config.h"

// 编译器
static inline mg_time_t mg_utime() {
    struct timeval tv;
    mg_gettimeofday(&tv);
    return (tv.tv_sec * 1000000LL + tv.tv_usec);
}

static inline mg_time_t mg_mtime() {
    struct timeval tv;
    mg_gettimeofday(&tv);
    return (tv.tv_sec * 1000LL + tv.tv_usec);
}

static inline mg_time_t mg_time() { return time(nullptr); }

static inline mg_char_t* mg_logtime() {
    static char str[32];

    mg_tm_t* tmp;
    struct timeval tv;

    mg_gettimeofday(&tv);
    tmp = localtime(&tv.tv_sec);

    sprintf(str, "[%02d/%02d/%d:%02d:%02d:%02d] ", tmp->tm_mday, tmp->tm_mon,
            1900 + tmp->tm_year, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
    return str;
}
#endif
