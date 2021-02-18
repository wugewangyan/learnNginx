//
// Created by 吴革 on 2021/2/16.
//

#ifndef _NGX_LOG_H_INCLUDED_
#define _NGX_LOG_H_INCLUDED_

#define NGX_MAX_ERROR_STR   2048

// 类似memcpy，但是常规的memcpy返回的是指向目标dst的指针，而这个ngx_cpymen返回的是目标[拷贝数据后]的终点位置
#define ngx_cpymem(dst, src, n) (((u_char *)memcpy(dst, src, n)) + (n))
// 比较大小，返回小值
#define ngx_min(val1, val2) ((val1 > val2) ? (val2) : (val1))

// 最大的32位无符号数
#define NGX_MAX_UINT32_VALUE    (uint32_t) 0xffffffff
#define NGX_INT64_LEN   (sizeof("-9223372036854775808") - 1)


// 日志相关 日志的八个等级【级别从高到低，数字最小的级别最高，数字大的级别最低】
#define NGX_LOG_STDERR            0     //控制台错误[stderr]：最高级别日志，日志的内容不再写入log参数指定的文件
#define NGX_LOG_EMERG             1     //紧急[emerg]
#define NGX_LOG_ALERT             2     //警戒[alert]
#define NGX_LOG_CRIT              3     //严重[crit]
#define NGX_LOG_ERR               4     //错误[error]
#define NGX_LOG_WARN              5     //警告[warn]
#define NGX_LOG_NOTICE            6     //注意[notice]
#define NGX_LOG_INFO              7     //信息[info]
#define NGX_LOG_DEBUG             8     //调试[debug]: 最低级别

#define NGX_LOG_DEBUG_CORE        0x010
#define NGX_LOG_DEBUG_ALLOC       0x020
#define NGX_LOG_DEBUG_MUTEX       0x040
#define NGX_LOG_DEBUG_EVENT       0x080
#define NGX_LOG_DEBUG_HTTP        0x100
#define NGX_LOG_DEBUG_MAIL        0x200
#define NGX_LOG_DEBUG_STREAM      0x400

/*
 * do not forget to update debug_levels[] in src/core/ngx_log.c
 * after the adding a new debug level
 */

#define NGX_LOG_DEBUG_FIRST       NGX_LOG_DEBUG_CORE
#define NGX_LOG_DEBUG_LAST        NGX_LOG_DEBUG_STREAM
#define NGX_LOG_DEBUG_CONNECTION  0x80000000
#define NGX_LOG_DEBUG_ALL         0x7ffffff0

u_char *ngx_vslprintf(u_char *buf, u_char *last, const char *fmt, va_list args);


#endif /* _NGX_LOG_H_INCLUDED_ */
