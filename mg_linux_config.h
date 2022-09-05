/*================================================================
*  
*  文件名称：mg_linux_config.h
*  创 建 者: mongia
*  创建日期：2022年09月05日
*  邮    箱：mongiaK@outlook.com
*  
================================================================*/

#ifndef __MG_LINUX_CONFIG_H__
#define __MG_LINUX_CONFIG_H__

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>             /* offsetof() */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <glob.h>
// #include <sys/vfs.h>            /* statfs() */

#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sched.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>        /* TCP_NODELAY, TCP_CORK */
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>

#include <time.h>               /* tzset() */
// #include <malloc.h>             /* memalign() */
#include <limits.h>             /* IOV_MAX */
#include <sys/ioctl.h>
// #include <crypt.h>
#include <sys/utsname.h>        /* uname() */

#include <dlfcn.h>

#endif
