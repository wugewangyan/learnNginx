//
// Created by 吴革 on 2021/2/15.
//
#include "../_include/ngx_c_conf.h"
#include "../_include/ngx_func.h"


CConfig *CConfig::instance = NULL;

CConfig::CConfig() {}

CConfig::~CConfig() {
    std::vector<LPCConfItem>::iterator pos;
    for(pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); ++pos){
        delete (*pos);
    }
    m_ConfigItemList.clear();
}

bool CConfig::Load(const char *pconfName) {
    FILE *fp;
    fp = fopen(pconfName, "r");
    if(fp == NULL){
        return false;
    }

    char linebuf[501];
    while(!feof(fp)){// 检查文件是否结束
        if(fgets(linebuf, 500, fp) == NULL)
            continue;
        if(linebuf[0] == 0)
            continue;
        if(*linebuf == ';' || *linebuf == ' ' || *linebuf == '#' || *linebuf == '\t' || *linebuf == '\n')
            continue;

        lblprocstring:
            if(strlen(linebuf) > 0){
                if(linebuf[strlen(linebuf) - 1] == 10 || linebuf[strlen(linebuf) - 1] == 13 || linebuf[strlen(linebuf) - 1] == 32){
                    linebuf[strlen(linebuf) - 1] = 0;
                    goto lblprocstring;
                }
            }

            if(linebuf[0] == 0)
                continue;
            if(*linebuf == '[')
                continue;

            char *ptmp = strchr(linebuf, '=');
            if(ptmp != NULL){
                LPCConfItem confItem = new CConfItem;
                memset(confItem, 0, sizeof(CConfItem));// 把confItem结构的内容清0
                strncpy(confItem->ItemName, linebuf, (int)(ptmp - linebuf));
                strcpy(confItem->ItemContent, ptmp + 1);
                Rtrim(confItem->ItemName);
                Ltrim(confItem->ItemName);
                Rtrim(confItem->ItemContent);
                Ltrim(confItem->ItemContent);

                m_ConfigItemList.push_back(confItem);
            }
    }

    fclose(fp);
    return true;
}

const char *CConfig::GetString(const char *p_itemname) {
    std::vector<LPCConfItem>::iterator pos;
    for(pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); ++pos){
        if(strcasecmp((*pos)->ItemName, p_itemname) == 0)
            return (*pos)->ItemContent;
    }
    return NULL;
}

int CConfig::GetIntDefault(const char *p_itemname, const int def) {
    std::vector<LPCConfItem>::iterator pos;
    for(pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); ++pos){
        if(strcasecmp((*pos)->ItemName, p_itemname) == 0)
            return atoi((*pos)->ItemContent);
    }
    return def;
}

