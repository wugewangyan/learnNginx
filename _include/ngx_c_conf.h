//
// Created by 吴革 on 2021/2/15.
//

#ifndef NGINX_NGX_C_CONF_H
#define NGINX_NGX_C_CONF_H

#endif //NGINX_NGX_C_CONF_H


#include <vector>
#include "ngx_global.h"

class CConfig{

    private:
        CConfig();

    public:
        ~CConfig();

    private:
        static CConfig *instance;

    public:
        static CConfig* GetInstance(){
            if(instance == NULL){
                if(instance == NULL){
                    instance = new CConfig();
                    static CGarhuishou cl;
                }
            }
            return instance;
        }

    class CGarhuishou{
        public:
            ~CGarhuishou(){
                if(CConfig::instance){
                    delete CConfig::instance;
                    CConfig::instance = NULL;
                }
            }
    };

    public:
        bool Load(const char *pconfName);
        const char* GetString(const char *p_itemname);
        int GetIntDefault(const char *p_itemname, const int def);

    public:
        std::vector<LPCConfItem> m_ConfigItemList;
};