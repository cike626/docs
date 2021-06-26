#ifndef __XML_H__
#define __XML_H__
#include<libconfig.h>
#include"doc_manage.h"

typedef struct{
    config_t *cfg;
    config_setting_t *psetting;
}config_root_t;

#endif

