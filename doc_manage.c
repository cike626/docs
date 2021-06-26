#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"doc_manage.h"
/*
定义声明一个链表，头指针为doc_list
*/
static LIST_HEAD(doc_list);

void register_doc(struct doc_struct *file)
{
	doc_s_t *tmp;
	struct list_head *post = NULL;
	list_for_each(post,&doc_list){
		tmp = list_entry(post,struct doc_struct,list);
		if(strcmp(file->name,tmp->name) == 0)
		{  
			printf("%s aready exit\n",tmp->name);	  
			//list_del(&tmp->list);
			//free(tmp);
			return;
		}
	}
	/*链表头插入*/
	list_add(&file->list,&doc_list);
	/*链表尾插入*/
	//list_add_tail(&file->list,&doc_list);
}
//遍历链表，打印节点的name
void list_print()
{
	struct doc_struct *tmp;
	struct list_head *post = NULL;

	list_for_each(post,&doc_list){
		tmp = list_entry(post,struct doc_struct,list);
		printf("name =%s\n",tmp->name);	  
	}
	
}

struct doc_struct *get_doc_operation(const char *name)
{
	struct doc_struct *tmp;
	struct list_head *post = NULL;

	list_for_each(post,&doc_list){
		tmp = list_entry(post,struct doc_struct,list);
		if(strcmp(name ,tmp->name) == 0)
        {
            if(NULL != tmp->doc_operation->init)
                tmp->doc_operation->init();
		  return tmp;
        }
    }
	return NULL;	
}
/*
void doc_init(const char *name)
{
	struct doc_struct *tmp;
	struct list_head *post = NULL;

	list_for_each(post,&doc_list){
		tmp = list_entry(post,struct doc_struct,list);
		if(strcmp(name ,tmp->name) == 0)
		  tmp->doc_operation->init();
		}
	
}
*/
/*
void doc_exit(void)
{
	struct doc_struct *tmp;
	struct list_head *post = NULL;
	list_for_each(post,&doc_list){
    	tmp = list_entry(post,struct doc_struct,list);
    	if(tmp->doc_operation->exit != NULL)
    	  tmp->doc_operation->exit();
    }
	
}*/
int doc_open(struct doc_struct *f, const char *file_path)
{
	if((f == NULL)||(NULL == file_path))
	  return -1;
    void *node =NULL;
	node = f->doc_operation->open(file_path);
    if(NULL != node)
    {
        f->root_node = node; 
        return 0;
    }else{
        //open file node is NULL
        return -1;
    }
}
void doc_close(struct doc_struct *f)
{
	if(f == NULL)
	  return ;
	f->doc_operation->exit(f->root_node);

}
/*
获取下一个节点；
c_node :当前的节点，传入NULL时默认为根节点
key:下一节点的关键字
*/
void *doc_get_next_node(struct doc_struct *f,void *c_node,const char *key)
{
    if((NULL== f)&&(NULL == key))
        return NULL;
    //当c_node为NULL时，使用根节点
    void *node = CALC_NODE(f->root_node,c_node);

    return f->doc_operation->get_next_node(node,key);

}
void doc_free_node(struct doc_struct *f,void *node)
{
    if((NULL== f)&&(NULL == node))
        return;
    return f->doc_operation->free_node(node);
}

/*
获取整数；
c_node：当前节点，传入NULL时默认为根节点；
key:键值，字符串
*/
int doc_get_int(struct doc_struct *f,void *c_node,const char *key)
{
	if((NULL == f)&&(NULL == key))
        return -1;
    void *node = CALC_NODE(f->root_node,c_node);

    return f->doc_operation->get_int(node,key);

}
char *doc_get_string(struct doc_struct *f,void *c_node,const char *key)
{
	if((NULL == f)&&(NULL == key))
        return NULL;
    void *node = CALC_NODE(f->root_node,c_node);

    return f->doc_operation->get_string(node,key);
}
int doc_get_bool(struct doc_struct *f,void *c_node,const char *key)
{
	if((NULL == f)&&(NULL == key))
        return -1;
    void *node = CALC_NODE(f->root_node,c_node);

    return f->doc_operation->get_bool(node,key);

}
double doc_get_float(struct doc_struct *f,void *c_node,const char *key)
{
	if((NULL == f)&&(NULL == key))
        return -1.0;
    void *node = CALC_NODE(f->root_node,c_node);

    return f->doc_operation->get_float(node,key);

}
void doc_free_string(struct doc_struct *f,char *str)
{
    if((NULL == f)&&(NULL == str))
        return ;
    f->doc_operation->string_free(str);
}

int doc_array_get_size(struct doc_struct *f,void *c_node,const char *key)
{
   if((NULL == f)&&(NULL == key))
        return -1;
    void *node = CALC_NODE(f->root_node,c_node);

    return f->doc_operation->array_get_size(node,key);

}
int doc_array_get_int(struct doc_struct *f,void *c_node,const char *key,int index)
{
	if((NULL == f)||(NULL == key)||(index < 0))
        return -1;
    void *node = CALC_NODE(f->root_node,c_node);
    
    return f->doc_operation->array_get_int(node,key,index);

}
int doc_array_get_bool(struct doc_struct *f,void *c_node,const char *key,int index)
{
	if((NULL == f)||(NULL == key)||(index < 0))
        return -1;
    void *node = CALC_NODE(f->root_node,c_node);

    return f->doc_operation->array_get_bool(node,key,index);
}
double doc_array_get_float(struct doc_struct *f,void *c_node,const char *key,int index)
{
	if((NULL == f)||(NULL == key)||(index < 0))
        return -1;
    void *node = CALC_NODE(f->root_node,c_node);
    
    return f->doc_operation->array_get_float(node,key,index);

}
//成功返回字符串长度；
//失败返回 -1
char *doc_array_get_string(struct doc_struct *f,void *c_node,const char *key,int index)
{
	if((NULL == f)||(NULL == key)||(index < 0))
        return NULL;
    void *node = CALC_NODE(f->root_node,c_node);
    
    return f->doc_operation->array_get_string(node,key,index);

}
int doc_sec_get_int(struct doc_struct *f,void *c_node,const char *key,const char *sec_key)
{
	if((NULL == f)||(NULL == key)||(NULL == sec_key))
        return -1;
    void *node = CALC_NODE(f->root_node,c_node);
    
    return f->doc_operation->sec_get_int(node,key,sec_key);
}
char *doc_sec_get_string(struct doc_struct *f,void *c_node,const char *key,const char *sec_key)
{
	if((NULL == f)||(NULL == key)||(NULL == sec_key))
        return NULL;
    void *node = CALC_NODE(f->root_node,c_node);

    return f->doc_operation->sec_get_string(node,key,sec_key);
}
int doc_sec_get_bool(struct doc_struct *f,void *c_node,const char *key,const char *sec_key)
{
	if((NULL == f)||(NULL == key)||(NULL == sec_key))
        return -1;
    void *node = CALC_NODE(f->root_node,c_node);
    
    return f->doc_operation->sec_get_bool(node,key,sec_key);

}
double doc_sec_get_float(struct doc_struct *f,void *c_node,const char *key,const char *sec_key)
{
	if((NULL == f)||(NULL == key)||(NULL == sec_key))
        return -1.0;
    void *node = CALC_NODE(f->root_node,c_node);
    
    return f->doc_operation->sec_get_float(node,key,sec_key);

}
int doc_list_get_size(struct doc_struct *f,void* c_node,const char *key)
{
    if((NULL == f)||(NULL == key))
        return -1;
    void *node = CALC_NODE(f->root_node,c_node);
    
    return f->doc_operation->list_get_size(node,key);

}
void *doc_list_get_list(struct doc_struct *f,void* c_node,int index)
{
    if((NULL == f)||(index < 0))
        return NULL;
    void *node = CALC_NODE(f->root_node,c_node);

    return f->doc_operation->list_get_list(node,index);

}
/*
int doc_list_get_int(struct doc_struct *f,void* c_node,const char *key)
{
    if((NULL == f)||(NULL == key))
        return -1;
    void *node = CALC_NODE(f->root_node,c_node);
    
    return f->doc_operation->list_get_int(node,key);

}
int doc_list_get_bool(struct doc_struct *f,void* c_node,const char *key)
{
    if((NULL == f)||(NULL == key))
        return -1;
    void *node = CALC_NODE(f->root_node,c_node);
    
    return f->doc_operation->list_get_bool(node,key);

}
double doc_list_get_float(struct doc_struct *f,void* c_node,const char *key)
{
    if((NULL == f)||(NULL == key))
        return -1.0;
    void *node = CALC_NODE(f->root_node,c_node);
    
    return f->doc_operation->list_get_float(node,key);

}
char *doc_list_get_string(struct doc_struct *f,void* c_node,const char *key)
{
    if((NULL == f)||(NULL == key))
        return NULL;
    void *node = CALC_NODE(f->root_node,c_node);
    
    return f->doc_operation->list_get_string(node,key);

}
*/

