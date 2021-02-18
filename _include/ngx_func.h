//
// Created by 吴革 on 2021/2/15.
//

#ifndef NGINX_NGX_FUNC_H
#define NGINX_NGX_FUNC_H

void Rtrim(char *string);

void Ltrim(char *string);

void ngx_init_setproctitle();

void ngx_setproctitle(const char *title);

#endif //NGINX_NGX_FUNC_H
