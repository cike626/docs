#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#include"json_doc.h"
#include "doc_manage.h"
#include "debug.h"
int main(int argc,char *argv[])
{
	struct doc_struct *file_operation=NULL;
	file_operation = get_doc_operation(JSON_FILE);
    char *file_path;
	if(file_operation !=NULL)
	{
		doc_open(file_operation,"test.json");

		int id = doc_get_int(file_operation,NULL,"id");
		DEBUG("id = %d\n",id);
        char *test_hello = doc_get_string(file_operation,NULL,"test");
		DEBUG("json read char = %s\n",test_hello);
        doc_free_string(file_operation,test_hello);
        
		int is_bool = doc_get_bool(file_operation,NULL,"is_bool");
		DEBUG("is_bool = %d\n",is_bool);
		float is_float = doc_get_float(file_operation,NULL,"is_float");
		DEBUG("is_float = %f\n",is_float);
        int array_size = doc_array_get_size(file_operation,NULL,"array");
        DEBUG("int array size = %d\n",array_size);
        array_size = doc_array_get_size(file_operation,NULL,"array_string");
        DEBUG("array_string size = %d\n",array_size);
		int array_int = doc_array_get_int(file_operation,NULL,"array",1);
		DEBUG("array_int = %d\n",array_int);
		char *array_string = doc_array_get_string(file_operation,NULL,"array_string",0);
		DEBUG("array_string = %s\n",array_string);
        doc_free_string(file_operation,array_string);

        node next_node = doc_get_next_node(file_operation, NULL, "sec_object");
        if(NULL != next_node)
        {
            int sec_id = doc_get_int(file_operation,next_node,"id");
    		DEBUG("sec_id = %d\n",sec_id);
            char *sec_str = doc_get_string(file_operation,next_node,"str");
    		DEBUG("sec_str = %s\n",sec_str);
            doc_free_string(file_operation,sec_str);
    		int sec_bool = doc_get_bool(file_operation,next_node,"sec_bool");
    		DEBUG("sec_bool = %d\n",sec_bool);
    		float sec_float = doc_get_float(file_operation,next_node,"sec_float");
    		DEBUG("sec_float = %f\n",sec_float);
    		char *sec_file = doc_get_string(file_operation,NULL,"sec_file");
    		DEBUG("sec_file = %s\n",sec_file);
            doc_free_string(file_operation,sec_file);
            int third_id = doc_sec_get_int(file_operation,next_node,"third_object","third_object_id");
            DEBUG("third_id = %d\n",third_id);
            node third_next_node = doc_get_next_node(file_operation, next_node, "third_object");
            if(NULL != third_next_node)
            {
                third_id = doc_get_int(file_operation,third_next_node,"third_object_id");
                DEBUG("third_id = %d\n",third_id);
                char *third_str = doc_get_string(file_operation,third_next_node,"third_object_st");
                DEBUG("third_str = %s\n",third_str);
                doc_free_string(file_operation,third_str);
            }
            doc_free_node(file_operation,third_next_node);
        }
        doc_free_node(file_operation,next_node);
		
		char *sec_str = doc_sec_get_string(file_operation,NULL,"sec_object","str");
		DEBUG("sec_str = %s\n",sec_str);
        doc_free_string(file_operation,sec_str);
		int sec_bool = doc_sec_get_bool(file_operation,NULL,"sec_object","sec_bool");
		DEBUG("sec_bool = %d\n",sec_bool);
		float sec_float = doc_sec_get_float(file_operation,NULL,"sec_object","sec_float");
		DEBUG("sec_float = %f\n",sec_float);

        file_path = doc_get_string(file_operation,NULL,"sec_file");
		DEBUG("file_path = %s\n",file_path);
        

//一个文件解析完成后，需要释放exit，否则会出现内存泄露
		doc_close(file_operation);
	}
    DEBUG("-----------TEST SEC FILE READ (%s)------------\n",file_path);
    if(NULL != file_operation)
    {
        doc_open(file_operation,file_path);
        doc_free_string(file_operation,file_path);
        int id = doc_get_int(file_operation,NULL,"id");
        DEBUG("id = %d\n",id);
        
        char *test_hello = doc_get_string(file_operation,NULL,"third");
        DEBUG("json read char = %s\n",test_hello);
        doc_free_string(file_operation,test_hello);
        int is_bool = doc_get_bool(file_operation,NULL,"is_bool");
        DEBUG("is_bool = %d\n",is_bool);
        
        float is_float = doc_get_float(file_operation,NULL,"is_float");
        DEBUG("is_float = %f\n",is_float);
        doc_close(file_operation);

    }

}

