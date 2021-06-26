#include"libconfig_doc.h"


static int _config_init(void)
{
    printf("%s\n",__FUNCTION__);
	return 0;
}
static void destroy_setting(void *cfgroot)
{
    P_FREE(((config_root_t*)cfgroot)->psetting);
    P_FREE(cfgroot);
}
static int config_exit(void *cfgroot)
{
    if (NULL != cfgroot)
    {
        config_destroy(((config_root_t *)cfgroot)->cfg);
        P_FREE(((config_root_t*)cfgroot)->cfg);
        destroy_setting(cfgroot);
    }
	printf("%s\n",__FUNCTION__);
    return 0;
}
static void *_config_open(const char *filename)
{
    config_t *cfg =NULL;
    config_setting_t *psetting = NULL;
    config_root_t *cfgroot = NULL;
    
    cfg = (config_t *)calloc(1,sizeof(config_t));
    psetting =(config_setting_t *)calloc(1,sizeof(config_setting_t));
    cfgroot = (config_root_t *)calloc(1,sizeof(config_root_t));
    
    if((NULL ==cfg)||(NULL == psetting)||(NULL == cfgroot))
        return NULL;
    cfgroot->cfg = cfg;
    cfgroot->psetting = psetting;

    config_init(cfgroot->cfg);
    
      /* Read the file. If there is an error, report it and exit. */
    if(! config_read_file(cfgroot->cfg, filename))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(cfgroot->cfg),
                config_error_line(cfgroot->cfg), config_error_text(cfgroot->cfg));
        config_destroy(cfgroot->cfg);
        P_FREE(cfgroot);
        return NULL;
    }
    return (void*)cfgroot;


}

static void *config_get_next_node(void* cfgroot,const char *tagkey)
{
    if((cfgroot == NULL)||(tagkey ==NULL))
           return NULL;

    config_root_t *node = NULL;
    node = calloc(1,sizeof(config_root_t));
    if(NULL == node)
        return NULL;

    node->cfg = ((config_root_t*)cfgroot)->cfg;
    node->psetting = ((config_root_t*)cfgroot)->psetting;
    /* 通过文件句柄查找数据 */
    config_setting_t *setting = config_lookup(((config_root_t*)cfgroot)->cfg, tagkey);
    //从一级节点中寻找第二节点
    if(NULL != setting)
    {
        node->psetting = setting;
    }else{
        //从Group中寻找
        setting = config_setting_get_member(node->psetting, tagkey);
        if(NULL != setting)
        {
            node->psetting = setting;
        }else{
            P_FREE(node);
            return NULL;
        }
    }
    
    return (void*)node;
}

static void config_free_node(void *node)
{
    if(node == NULL)
       return;
    P_FREE(node);
}

static int config_get_int(void* cfgroot,const char *tagkey)
{
    if((cfgroot == NULL)||(tagkey ==NULL))
       return -1;
    int result;
    config_t *c_cfg = ((config_root_t*)cfgroot)->cfg;
    config_setting_t *c_psetting = ((config_root_t*)cfgroot)->psetting;
//首先查找一级节点，一级节点查找失败，查找二级节点
    if(config_lookup_int(c_cfg,tagkey, &result))
    {
        return result;
    }else if(config_setting_lookup_int(c_psetting,tagkey, &result)){
        return result;
    }else{
        return -1;
    }
    
}
static double config_get_float(void* cfgroot,const char *tagkey)
{
    if((cfgroot == NULL)||(tagkey ==NULL))
        return -1;
    double result;
    config_t *c_cfg = ((config_root_t*)cfgroot)->cfg;
    config_setting_t *c_psetting = ((config_root_t*)cfgroot)->psetting;

    if(config_lookup_float(c_cfg,tagkey, &result))
    {
        return result;
    }else if(config_setting_lookup_float(c_psetting,tagkey, &result)){
        return result;
    }else{
        return -1.0;
    }
}
static int config_get_bool(void* cfgroot,const char *tagkey)
{

    if((cfgroot == NULL)||(tagkey ==NULL))
        return -1;
    int result;
    config_t *c_cfg = ((config_root_t*)cfgroot)->cfg;
    config_setting_t *c_psetting = ((config_root_t*)cfgroot)->psetting;
    
    if(config_lookup_bool(c_cfg,tagkey, &result))
    {
        return result;
    }else if(config_setting_lookup_bool(c_psetting,tagkey, &result)){
        return result;
    }else{
        return -1;
    }    
}
static char *config_get_string(void* cfgroot,const char *tagkey)
{

    if((cfgroot == NULL)||(tagkey ==NULL))
        return NULL;
    config_t *c_cfg = ((config_root_t*)cfgroot)->cfg;
    config_setting_t *c_psetting = ((config_root_t*)cfgroot)->psetting;
    char *str;
    if(config_lookup_string(c_cfg, tagkey, (const char **)&str))
    {
        __STR_COPY(str);
    }else if(config_setting_lookup_string(c_psetting, tagkey, (const char **)&str)){
        __STR_COPY(str);
    }else{
        return NULL;
    }
}

static int config_array_get_size(void* cfgroot,const char *tagkey)
{
    if((cfgroot == NULL)||(tagkey ==NULL))
            return -1;
    int count = -1;

    config_root_t *node = (config_root_t *)config_get_next_node(cfgroot,tagkey);
    if(NULL != node)
    {
        count = config_setting_length(node->psetting);
        //destroy_setting(node);
        P_FREE(node);
    }
    return count;
}
static int config_array_get_int(void* cfgroot,const char *tagkey,int index)
{
    if((cfgroot == NULL)||(tagkey ==NULL))
        return -1;
    int result = -1;
    config_root_t *node = (config_root_t *)config_get_next_node(cfgroot,tagkey);
    if(NULL != node)
    {
        result = config_setting_get_int_elem(node->psetting,index);
        P_FREE(node);
    }
    return result;
}
static double config_array_get_float(void* cfgroot,const char *tagkey,int index)
{
    if((cfgroot == NULL)||(tagkey ==NULL))
        return -1.0;
    double result = -1.0;
    config_root_t *node = (config_root_t *)config_get_next_node(cfgroot,tagkey);
    if(NULL != node)
    {
        result = config_setting_get_float_elem(node->psetting,index);
        P_FREE(node);
    }
    return result;
}

static int config_array_get_bool(void* cfgroot,const char *tagkey,int index)
{
    if((cfgroot == NULL)||(tagkey ==NULL))
        return -1;
    int result = -1;
    config_root_t *node = (config_root_t *)config_get_next_node(cfgroot,tagkey);
    if(NULL != node)
    {
        result= config_setting_get_bool_elem(node->psetting,index);
        P_FREE(node);
        
    }
    return result;
}

static char *config_array_get_string(void* cfgroot,const char *tagkey,int index)
{
    if((cfgroot == NULL)||(tagkey ==NULL))
        return NULL;
    const char *str;
    config_root_t *node = (config_root_t *)config_get_next_node(cfgroot,tagkey);
    if(NULL != node)
    {
        str = config_setting_get_string_elem(node->psetting,index);
        P_FREE(node);
        
        __STR_COPY(str);
    }
    return NULL;
}
static void *config_list_get_list(void* cfgroot,int index)
{
    if(cfgroot == NULL)
        return NULL;

    config_root_t *node = NULL;
    node = (config_root_t *)calloc(1,sizeof(config_root_t));    
    config_setting_t *setting = ((config_root_t *)cfgroot)->psetting;
    if(NULL != node)
    {   
        node->cfg = ((config_root_t *)cfgroot)->cfg;
        node->psetting = config_setting_get_elem(setting, index);
        return node;
    }
    return NULL;
}




static int config_sec_get_int(void* cfgroot,const char *tagkey,const char *sec_key)
{
    if((cfgroot == NULL)||(tagkey ==NULL)||(sec_key ==NULL))
            return -1;
    int result;
    config_root_t *node = config_get_next_node(cfgroot,tagkey);
    if(NULL != node)
    {
       result = config_get_int(node,sec_key);
       P_FREE(node);
       return result;
    }
    return -1;
}
static int config_sec_get_bool(void* cfgroot,const char *tagkey,const char *sec_key)
{
    if((cfgroot == NULL)||(tagkey ==NULL)||(sec_key ==NULL))
        return -1;
    int result;
    config_root_t *node = config_get_next_node(cfgroot,tagkey);
    if(NULL != node)
    {
       result = config_get_bool(node,sec_key);
       P_FREE(node);
       return result;
    }
    return -1;
}

static double config_sec_get_float(void* cfgroot,const char *tagkey,const char *sec_key)
{
    if((cfgroot == NULL)||(tagkey ==NULL)||(sec_key ==NULL))
        return -1;
    double result;
    config_root_t *node = config_get_next_node(cfgroot,tagkey);
    if(NULL != node)
    {
       result = config_get_float(node,sec_key);
       P_FREE(node);
       return result;
    }
    return -1.0;
}

static char *config_sec_get_string(void* cfgroot,const char *tagkey,const char *sec_key)
{

    if((cfgroot == NULL)||(tagkey ==NULL)||(sec_key ==NULL))
            return NULL;
    char *result;

    config_root_t *node = config_get_next_node(cfgroot,tagkey);
    if(NULL != node)
    {
       result = config_get_string(node,sec_key);
       P_FREE(node);
       return result;

    }
    return NULL;
}

static void config_string_free(char *str)
{
    P_FREE(str);
}

static struct doc_operation_struct config_operation = {
	.init = _config_init,
	.open = _config_open,
	.get_next_node = config_get_next_node,
	.free_node = config_free_node,
	.get_int = config_get_int,
	.get_string = config_get_string,
	.get_bool = config_get_bool,
	.get_float = config_get_float,
	.array_get_size = config_array_get_size,
	.array_get_int = config_array_get_int,
	.array_get_float = config_array_get_float,
	.array_get_bool = config_array_get_bool,
	.array_get_string = config_array_get_string,
	.list_get_size = config_array_get_size,
	.list_get_list = config_list_get_list,
	.sec_get_int = config_sec_get_int,
	.sec_get_string = config_sec_get_string,
	.sec_get_bool = config_sec_get_bool,
	.sec_get_float = config_sec_get_float,
	.string_free = config_string_free,
	.exit = config_exit,
};
static struct doc_struct config_file = {
	.name = LIBCONFIG_FILE,
	.doc_operation = &config_operation,
};

static void config_doc_init(void) __attribute__((constructor));
static void config_doc_init(void)
{
	register_doc(&config_file);
}
