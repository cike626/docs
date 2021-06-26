#include"json_doc.h"

static int json_init(void)
{
	printf("%s\n",__FUNCTION__);
	//json_para.object = NULL;
	return 0;
}

static int json_exit(void *json_para)
{
    printf("%s\n",__FUNCTION__);
	if(json_para != NULL)
	{
		if(((json_object_t*)json_para)->object != NULL)
		{
			json_object_put(((json_object_t*)json_para)->object);
			((json_object_t*)json_para)->object=NULL;
		}
		P_FREE(json_para);
		//json_para = NULL;
	}	
    return 0;
}
static void *json_open(const char *filename)
{
	json_object_t *json_para=NULL;
	json_para = calloc(1,sizeof(json_object_t));
    if(NULL == json_para)
        return NULL;
    
	json_para->object = json_object_from_file(filename);
	//const char *object_string=json_object_to_json_string(json_para.object);
	//printf("object_string=%s\n",object_string);
	return (void*)json_para;

    

}
static void *json_get_next_node(void* object,const char *key)
{
    if((object == NULL)||(key ==NULL))
           return NULL;
    json_object_t *node = NULL;
    node = (json_object_t *)calloc(1,sizeof(json_object_t));
    if(NULL == node)
        return NULL;
    json_object* tmp_object = ((json_object_t*)object)->object;
	node->object = json_object_object_get(tmp_object,key);
	return (void*)node;

}
static void json_free_node(void* node)
{
    if(node == NULL)
        return;
    P_FREE(node);

}

static char *json_get_string(void* object,const char *key)
{
    if((object == NULL)||(key ==NULL))
        return NULL;
    char *tmp_result = NULL;
    
	json_object* tmp_object = ((json_object_t*)object)->object;
	tmp_result = (char *)json_object_get_string(json_object_object_get(tmp_object,key));
    if(NULL == tmp_result)
       return NULL;
    
    __STR_COPY(tmp_result);

}
static int json_get_int(void* object,const char *key)
{
	json_object* tmp_object = ((json_object_t*)object)->object;
	return  json_object_get_int(json_object_object_get(tmp_object,key));
}
static int json_get_bool(void* object,const char *key)
{
    if((object == NULL)||(key ==NULL))
            return -1;
	json_object* tmp_object = ((json_object_t*)object)->object;
	return  json_object_get_boolean(json_object_object_get(tmp_object,key));
}
static double json_get_float(void* object,const char *key)
{
    if((object == NULL)||(key ==NULL))
        return -1;

	json_object* tmp_object = ((json_object_t*)object)->object;
	return  json_object_get_double(json_object_object_get(tmp_object,key));
}
static int json_array_get_size(void* object,const char *key)
{
    if((object == NULL)||(key ==NULL))
            return -1;
    json_object* tmp_object = ((json_object_t*)object)->object;
	struct json_object* array = json_object_object_get(tmp_object,key);
    return (int)json_object_array_length(array);

}
static int json_array_get_int(void* object,const char *key,int index)
{
    if((object == NULL)||(key ==NULL))
        return -1;

	json_object* tmp_object = ((json_object_t*)object)->object;
	struct json_object* array = json_object_object_get(tmp_object,key);
	return  json_object_get_int(json_object_array_get_idx(array,index));
}
static int json_array_get_bool(void* object,const char *key,int index)
{
    if((object == NULL)||(key ==NULL))
        return -1;

	json_object* tmp_object = ((json_object_t*)object)->object;
	struct json_object* array = json_object_object_get(tmp_object,key);
	return  json_object_get_boolean(json_object_array_get_idx(array,index));
}
static double json_array_get_float(void* object,const char *key,int index)
{
    if((object == NULL)||(key ==NULL))
        return -1;

	json_object* tmp_object = ((json_object_t*)object)->object;
	struct json_object* array = json_object_object_get(tmp_object,key);
	return  json_object_get_double(json_object_array_get_idx(array,index));
}

static char *json_array_get_string(void* object,const char *key,int index)
{
    if((object == NULL)||(key ==NULL))
            return NULL;
    char *tmp_result = NULL;

	json_object* tmp_object = ((json_object_t*)object)->object;
	struct json_object* array = json_object_object_get(tmp_object,key);
	tmp_result = (char *)json_object_get_string(json_object_array_get_idx(array,index));
    
    __STR_COPY(tmp_result);

}
static int json_sec_get_int(void* object,const char *key,const char *sec_key)
{
	json_object* tmp_object = ((json_object_t*)object)->object;
	struct json_object* sec_object = json_object_object_get(tmp_object,key);
	return  json_object_get_int(json_object_object_get(sec_object,sec_key));
}
static char *json_sec_get_string(void* object,const char *key,const char *sec_key)
{
    if((object == NULL)||(key ==NULL))
        return NULL;
    char *tmp_result = NULL;

	json_object* tmp_object = ((json_object_t*)object)->object;
	struct json_object* sec_object = json_object_object_get(tmp_object,key);
	tmp_result = (char *)json_object_get_string(json_object_object_get(sec_object,sec_key));
    
    __STR_COPY(tmp_result);

}
static int json_sec_get_bool(void* object,const char *key,const char *sec_key)
{
    if((object == NULL)||(key ==NULL)||(sec_key == NULL))
        return -1;

	json_object* tmp_object = ((json_object_t*)object)->object;
	struct json_object* sec_object = json_object_object_get(tmp_object,key);
	return  json_object_get_boolean(json_object_object_get(sec_object,sec_key));
}
static double json_sec_get_float(void* object,const char *key,const char *sec_key)
{
    if((object == NULL)||(key ==NULL)||(sec_key == NULL))
        return -1;

	json_object* tmp_object = ((json_object_t*)object)->object;
	struct json_object* sec_object = json_object_object_get(tmp_object,key);
	return  json_object_get_double(json_object_object_get(sec_object,sec_key));
}
static void json_string_free(char *str)
{
    P_FREE(str);
}
static struct doc_operation_struct json_operation = {
	.init = json_init,
	.open = json_open,
	.get_next_node = json_get_next_node,
	.free_node = json_free_node,
	.get_int = json_get_int,
	.get_string = json_get_string,
	.get_bool = json_get_bool,
	.get_float = json_get_float,
	.array_get_size = json_array_get_size,
	.array_get_int = json_array_get_int,
	.array_get_bool = json_array_get_bool,
	.array_get_float = json_array_get_float,
	.array_get_string = json_array_get_string,
	.sec_get_int = json_sec_get_int,
	.sec_get_string = json_sec_get_string,
	.sec_get_bool = json_sec_get_bool,
	.sec_get_float = json_sec_get_float,
	.string_free = json_string_free,
	.exit = json_exit,
};
static struct doc_struct json_file = {
	.name = "json file",
	.doc_operation = &json_operation,
};

static void json_doc_init(void) __attribute__((constructor));
static void json_doc_init(void)
{
	register_doc(&json_file);
}
