//
// Created by 吴革 on 2021/2/15.
//

#ifndef NGINX_NGX_GLOBAL_H
#define NGINX_NGX_GLOBAL_H


typedef struct {
    char ItemName[50];
    char ItemContent[500];
}CConfItem, *LPCConfItem;

extern char **g_os_argv;// 原始命令行参数数组，在main中会被赋值
extern char *gp_envmem;// 指向自己分配的env环境变量的内存
extern int g_environlen;

#endif //NGINX_NGX_GLOBAL_H
