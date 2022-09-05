/*================================================================
*  
*  文件名称：main.c
*  创 建 者: mongia
*  创建日期：2022年09月03日
*  邮    箱：mongiaK@outlook.com
*  
================================================================*/

#include "mg_config.h"
#include "mg_core.h"

int main(int argc, char * argv[])
{
    mg_uint32_t i = 0;
 
    log_init(NULL, LOG_DEBUG);

    mglog_info("helloworld");

    return 1;
}
