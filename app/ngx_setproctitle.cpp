//
// Created by 吴革 on 2021/2/16.
//
#include <cstring>
#include "../_include/ngx_global.h"
/**
 * 设置可执行程序标题相关函数：分配内存，并把环境变量拷贝到新内存中
 */
extern char** environ;
void ngx_init_setproctitle(){
    int i;
    for(i = 0; environ[i]; i++){
        g_environlen += strlen(environ[i]) + 1;// +1是因为末尾有\0
    }

    gp_envmem = new char[g_environlen];
    memset(gp_envmem, 0, g_environlen);//清空内存
    char* ptmp = gp_envmem;

    for(i = 0; environ[i]; i++){
        size_t size = strlen(environ[i]) + 1;// strlen不包含字符串末尾\0的长度
        strcpy(ptmp, environ[i]);//把原环境变量内容拷贝到新地方
        environ[i] = ptmp;//然后还要让新环境变量指向这段新内存
        ptmp += size;
    }
    return;
}

void ngx_setproctitle(const char* title){
    size_t titleLen = strlen(title);
    size_t e_environlen = 0;
    for(int i = 0; g_os_argv[i]; i++){
        e_environlen += strlen(g_os_argv[i]) + 1;
    }

    size_t esy = e_environlen + g_environlen;
    if(esy <= titleLen){
        return;
    }

    // 设置后续的命令行参数为空，表示只有argv[]中只有一个元素了，这是一个好习惯，防止以后滥用argv
    g_os_argv[1] = NULL;

    char* ptmp = g_os_argv[0];
    strcpy(ptmp, title);

    ptmp += titleLen;
    size_t cha = esy - titleLen;
    memset(ptmp, 0, cha);
    return;
}