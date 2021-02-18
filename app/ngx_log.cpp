//
// Created by 吴革 on 2021/2/16.
//

#include <cstdarg>
#include <complex>
#include "../_include/ngx_log.h"

/**
 * 如果err不为0，表示有错误，会将该错误编号以及对应的错误信息一并放到组合出得字符串中一起显示
 * @param err
 * @param fmt
 * @param ...
 */
void ngx_log_stderr(int err, const char *fmt, ...){
    va_list args;
    u_char errstr[NGX_MAX_ERROR_STR + 1];
    u_char *p, *last;

    memset(errstr, 0, sizeof(errstr));
    //last指向整个buffer最后【指向最后一个有效位置的后面，也就是非有效位】
    last = errstr + NGX_MAX_ERROR_STR;

    // p指向"nginx: "之后
    p = ngx_cpymem(errstr, "nginx: ", 7);

    // 使args指向起始的参数
    va_start(args, fmt);
    p = ngx_vslprintf();
}