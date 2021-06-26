#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#include "xml.h"
#include "doc_manage.h"
#include "debug.h"
int main(int argc,char *argv[])
{

	struct doc_struct *file_operation = NULL;
	file_operation = get_doc_operation(XML_FILE);
    char *file_path = NULL;
	if(file_operation !=NULL)
	{
		doc_open(file_operation,"cfg.xml");

		int id = doc_get_int(file_operation,NULL,"Version");
		DEBUG("id = %d\n",id);
		
        char *test_hello = doc_get_string(file_operation,NULL,"test");
		DEBUG("json read char = %s\n",test_hello);
        doc_free_string(file_operation,test_hello);
		int is_bool = doc_get_bool(file_operation,NULL,"is_bool");
		DEBUG("is_bool = %d\n",is_bool);
        
		float is_float = doc_get_float(file_operation,NULL,"is_float");
		DEBUG("is_float = %f\n",is_float);

        node next_node = doc_get_next_node(file_operation, NULL, "MiscShelf");
        if(NULL != next_node)
        {
            int shutting_Tvalue = doc_get_int(file_operation,next_node,"shutting_Tvalue");
    		DEBUG("shutting_Tvalue = %d\n",shutting_Tvalue);
             
    		char *OthersCfgPath = doc_get_string(file_operation,next_node,"OthersCfgPath");
    		DEBUG("OthersCfgPath = %s\n",OthersCfgPath);
            doc_free_string(file_operation,OthersCfgPath);
            
    		int checking_RFID = doc_get_bool(file_operation,next_node,"checking_RFID");
    		DEBUG("checking_RFID = %d\n",checking_RFID);
    		float warning_Tvalue = doc_get_float(file_operation,next_node,"warning_Tvalue");
    		DEBUG("warning_Tvalue = %f\n",warning_Tvalue);
            node third_node = doc_get_next_node(file_operation, next_node, "MC_BOARD");
            if(NULL != third_node)
            {
                char *third_version = doc_get_string(file_operation,third_node,"third_version");
    		    DEBUG("third_version = %s\n",third_version);
                doc_free_string(file_operation,third_version);
                double third_float = doc_get_float(file_operation,third_node,"third_float");
    		    DEBUG("third_float = %f\n",third_float);
                int checking_module = doc_get_bool(file_operation,third_node,"checking_module");
    		    DEBUG("checking_module = %d\n",checking_module);
            }
            doc_free_node(file_operation,third_node);
            
        }
        doc_free_node(file_operation,next_node);
        
		int shutting_Tvalue = doc_sec_get_int(file_operation,NULL,"MiscShelf","shutting_Tvalue");
		DEBUG("shutting_Tvalue = %d\n",shutting_Tvalue);
         
		char *OthersCfgP = doc_sec_get_string(file_operation,NULL,"MiscShelf","OthersCfgPath");
		DEBUG("OthersCfgP = %s\n",OthersCfgP);
        doc_free_string(file_operation,OthersCfgP);
        
		int checking_RFID = doc_sec_get_bool(file_operation,NULL,"MiscShelf","checking_RFID");
		DEBUG("checking_RFID = %d\n",checking_RFID);
		float warning_Tvalue = doc_sec_get_float(file_operation,NULL,"MiscShelf","warning_Tvalue");
		DEBUG("warning_Tvalue = %f\n",warning_Tvalue);
        
        file_path = doc_get_string(file_operation,NULL,"OthersCfgPath");
		DEBUG("file_path = %s\n",file_path);
        
//一个文件解析完成后，需要释放exit，否则会出现内存泄露
		doc_close(file_operation);
	}

	DEBUG("-----------TEST SEC FILE READ (%s)------------\n",file_path);
    if(NULL != file_operation)
    {
        int ret = doc_open(file_operation,file_path);
        doc_free_string(file_operation,file_path);
        if(ret >= 0)
        {
            int id = doc_get_int(file_operation,NULL,"Version");
            DEBUG("id = %d\n",id);
            
            char *test_hello = doc_get_string(file_operation,NULL,"test");
            DEBUG("json read char = %s\n",test_hello);
            doc_free_string(file_operation,test_hello);
            int is_bool = doc_get_bool(file_operation,NULL,"is_bool");
            DEBUG("is_bool = %d\n",is_bool);
            
            float is_float = doc_get_float(file_operation,NULL,"is_float");
            DEBUG("is_float = %f\n",is_float);
            doc_close(file_operation);
        }else{
            DEBUG("open file fail\n");
        }

    }else{
        DEBUG("file_operation is NULL\n");
    }

}

