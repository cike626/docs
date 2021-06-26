#ifndef __DOC_MANAGE__
#define __DOC_MANAGE__
#include "list.h"
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include <linux/limits.h>
#include "debug.h"
#define XML_FILE "xml file"
#define JSON_FILE "json file"
#define LIBCONFIG_FILE "libconfig file"
typedef void * node;
typedef struct doc_operation_struct{

	int (*init)(void);
	void *(*open)(const char *);
    void *(*get_next_node)(void *,const char *);
    void (*free_node)(void *);
	int (*get_int)(void *,const char *);
	char *(*get_string)(void *,const char *);
	int (*get_bool)(void *,const char *);
	double (*get_float)(void *,const char *);
    int (*array_get_size)(void *,const char *);
	int (*array_get_int)(void *,const char *,int );
    double (*array_get_float)(void *,const char *,int );
    int (*array_get_bool)(void *,const char *,int );
	char *(*array_get_string)(void *,const char *,int);
    int (*list_get_size)(void *,const char *);
    void *(*list_get_list)(void *,int);
	int (*sec_get_int)(void *,const char *,const char *);
	char *(*sec_get_string)(void *,const char *,const char *);
	int (*sec_get_bool)(void *,const char *,const char *);
	double (*sec_get_float)(void *,const char *,const char *);
    void (*string_free)(char *);
	int (*exit)(void *);
}doc_operation_struct_t;
typedef struct doc_struct{
	char *name;
	doc_operation_struct_t *doc_operation;
	void *root_node;
	struct list_head list;
}doc_s_t;

void register_doc(struct doc_struct *file);
struct doc_struct *get_doc_operation(const char *name);
//void doc_exit(void);



void list_print(void);
int doc_open(struct doc_struct *f, const char *name);
void doc_close(struct doc_struct *f);
void *doc_get_next_node(struct doc_struct *f,void *c_node,const char *key);
void doc_free_node(struct doc_struct *f,void *node);
int doc_get_int(struct doc_struct *f,void *c_node,const char *key);
char *doc_get_string(struct doc_struct *f,void *c_node,const char *key);
int doc_get_bool(struct doc_struct *f,void *c_node,const char *key);
double doc_get_float(struct doc_struct *f,void *c_node,const char *key);
void doc_free_string(struct doc_struct *f,char *str);
int doc_array_get_size(struct doc_struct *f,void *c_node,const char *key);
int doc_array_get_int(struct doc_struct *f,void *c_node,const char *key,int index);
int doc_array_get_bool(struct doc_struct *f,void *c_node,const char *key,int index);
double doc_array_get_float(struct doc_struct *f,void *c_node,const char *key,int index);
char *doc_array_get_string(struct doc_struct *f,void *c_node,const char *key,int index);

int doc_sec_get_int(struct doc_struct *f,void *c_node,const char *key,const char *sec_key);
char *doc_sec_get_string(struct doc_struct *f,void *c_node,const char *key,const char *sec_key);
int doc_sec_get_bool(struct doc_struct *f,void *c_node,const char *key,const char *sec_key);
double doc_sec_get_float(struct doc_struct *f,void *c_node,const char *key,const char *sec_key);

int doc_list_get_size(struct doc_struct *f,void* c_node,const char *key);
void *doc_list_get_list(struct doc_struct *f,void* c_node,int index);
int doc_list_get_int(struct doc_struct *f,void* c_node,const char *key);
int doc_list_get_bool(struct doc_struct *f,void* c_node,const char *key);
double doc_list_get_float(struct doc_struct *f,void* c_node,const char *key);
char *doc_list_get_string(struct doc_struct *f,void* c_node,const char *key);







#define P_FREE(p)\
do{\
    if((p) !=NULL)\
    {\
        free(p);\
        (p)=NULL;\
    }\
}while(0)


#define __STR_COPY(SRC) \
do{\
    char *result = NULL;\
    int len = strlen((const char *)(SRC));\
    result = calloc(len+1,sizeof(char));\
    if(NULL != result){\
    strncpy(result, (SRC), len);\
    return result;}\
    else {\
        return NULL;}\
}while(0)


#define CALC_NODE(F_NODE,S_NODE)\
    ((NULL == (S_NODE))?(F_NODE):(S_NODE))




#endif
