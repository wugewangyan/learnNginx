#include <libc.h>
#include "_include/ngx_c_conf.h"
#include "_include/ngx_global.h"
#include "_include/ngx_func.h"


/**
 * 内存泄漏检查
 * valgrind
 *     --tool=memcheck: 使用valgrind工具集中的memcheck工具
 *     --leak-check=full: 指的是完全full检查内存泄漏
 *     --show-reachable=yes: 是显示内存泄漏的地点
 *     --trace-children=yes: 是否跟入子进程
 *     --log-file=log.txt: 将调试信息输出到log.txt，不输出到屏幕
 *  最常用的命令：
 *     valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./nginx
 */

/**
 * main方法中
 *  argc：是命令行参数的个数
 *  argv: 是一个数组，每个数组元素都指向一个字符串的char *, 里面存放的内容是所有命令行的参数
 * 例如：./nginx -v -s 5 中：
 *  argc = 4
 *  argv[0] = ./nginx  他也是指向可执行程序的程序名称(ps命令中的cmd列展示)
 *  argv[1] = -v
 *  argv[2] = -s
 *  argv[3] = 5
 *
 *  在argv内存之后，紧接着的就是环境变量参数信息，可以通过一个全局的environ[char **]可以访问
 */

char ** g_os_argv; // 原始命令行参数数组，在main中会被赋值
char *gp_envmem = NULL;// 指向自己分配的env环境变量的内存
int g_environlen = 0;
extern char** environ;
int main(int argc, char *const *argv) {

    g_os_argv = (char **)argv;

    for(int i = 0; environ[i]; i++){
        printf("environ[%d]地址=%x    ", i, (unsigned int)((unsigned long)environ[i]));
        printf("environ[%d]内容=%s\n    ", i, environ[i]);
    }
    printf("----------------------------------------------------------------------------\n");
    ngx_init_setproctitle();
    for(int i = 0; environ[i]; i++){
        printf("environ[%d]地址=%x    ", i, (unsigned int)((unsigned long)environ[i]));
        printf("environ[%d]内容=%s\n    ", i, environ[i]);
    }

    ngx_setproctitle("nginx:master process");

    CConfig *config = CConfig::GetInstance();
    if(config->Load("../nginx.conf") == false){
        printf("配置文件读取失败,退出！\n");
        exit(1);
    }

    int port = config->GetIntDefault("ListenPort",0);
    printf("port=%d\n", port);
    const char* dbInfo = config->GetString("DBInfo");
    printf("dbInfo=%s\n", dbInfo);

    for(;;){
        sleep(1);
        printf("休眠1秒\n");
    }

    // 对于因为设置可执行程序标题导致的环境变量分配的内存，我们应该释放
    if(gp_envmem){
        delete []gp_envmem;
        gp_envmem = NULL;
    }
    return 0;
}
