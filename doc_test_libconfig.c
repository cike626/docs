#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#include "doc_manage.h"
#include"debug.h"
int main(int argc,char *argv[])
{
	struct doc_struct *file_operation=NULL;
	file_operation = get_doc_operation(LIBCONFIG_FILE);
    char *file_path;
	if(file_operation !=NULL)
	{
		doc_open(file_operation,"example.cfg");

		int id = doc_get_int(file_operation,NULL,"id");
		DEBUG("id = %d\n",id);
		
        char *name = doc_get_string(file_operation,NULL,"name");
		DEBUG("config read char = %s\n",name);
        doc_free_string(file_operation,name);
        file_path = doc_get_string(file_operation,NULL,"sec_file");
		DEBUG("sec file_path = %s\n",file_path);

		int is_bool = doc_get_bool(file_operation,NULL,"is_bool");
		DEBUG("is_bool = %d\n",is_bool);
        
		float is_float = doc_get_float(file_operation,NULL,"is_double");
		DEBUG("is_float = %f\n",is_float);
        DEBUG("\t--------------------\n");
        int array_size = doc_array_get_size(file_operation, NULL, "sectags_arrary");
        DEBUG("TEST first array_size = %d\n",array_size);

        int i;
        char *array_string;
        for(i=0;i<array_size;i++)
        {   
            int ret = doc_array_get_int(file_operation,NULL, "sectags_arrary", i);
            is_bool = doc_array_get_bool(file_operation, NULL ,"bool_array",i);
            is_float = doc_array_get_float(file_operation, NULL ,"double_array",i);
            array_string = doc_array_get_string(file_operation, NULL ,"st_array",i);
            DEBUG("array[%d] = (%d)-(%d)-(%f)-(%s)\n",i,ret,is_bool,is_float,array_string);
            doc_free_string(file_operation,array_string);
        }
        int comboH;
        /*
        DEBUG("-------SEC NODE READ-------------\n");
        comboH = doc_sec_get_int(file_operation, NULL,"timeFormatComb", "comboH");
        DEBUG("TEST SEC GET int  = %d\n",comboH);
        
        char sec_type[50];
        ret =doc_sec_get_string(file_operation,NULL,"timeFormatComb","type",sec_type);
        DEBUG("TEST SEC GET string = %s----------%d\n",sec_type,ret);

        is_bool = doc_sec_get_bool(file_operation,NULL,"timeFormatComb","sec_bool");
        DEBUG("TEST SEC GET is_bool = %d\n",is_bool);
        is_float = doc_sec_get_float(file_operation,NULL,"timeFormatComb","sec_float");
        DEBUG("TEST SEC GET is_float = %f\n",is_float);
        */


        node next_node = doc_get_next_node(file_operation, NULL, "timeFormatComb");
        if(NULL != next_node)
        {
            comboH = doc_get_int(file_operation,next_node,"comboH");
    		DEBUG("comboH = %d\n",comboH);
            DEBUG("--------------------\n");
            array_size = doc_array_get_size(file_operation, next_node, "sectags_arrary");
            DEBUG("TEST sec array_size = %d\n",array_size);
            int ret;
            for(i=0;i<array_size;i++)
            {   
                ret = doc_array_get_int(file_operation,next_node, "sectags_arrary", i);
                is_bool = doc_array_get_bool(file_operation, next_node ,"bool_array",i);
                is_float = doc_array_get_float(file_operation, next_node ,"double_array",i);
                array_string = doc_array_get_string(file_operation, next_node ,"st_array",i);
                DEBUG("array[%d] = (%d)-(%d)-(%f)-(%s)\n",i,ret,is_bool,is_float,array_string);
                doc_free_string(file_operation,array_string);
            }
            DEBUG("--------------------\n");
    		char *type = doc_get_string(file_operation,next_node,"type");
    		DEBUG("type = %s\n",type);
            doc_free_string(file_operation,type);
            
    		is_bool = doc_get_bool(file_operation,next_node,"sec_bool");
    		DEBUG("is_bool = %d\n",is_bool);
    		is_float = doc_get_float(file_operation,next_node,"sec_float");
    		DEBUG("is_float = %f\n",is_float);
            DEBUG("-------SEC NODE READ-------------\n");
            is_bool = doc_sec_get_bool(file_operation, next_node,"books", "third_bool");
            DEBUG("TEST SEC READ bool = %d\n",is_bool);
            char *name1 = doc_sec_get_string(file_operation, next_node,"books", "author");
            DEBUG("SEC READ STR = %s\n",name1);
            doc_free_string(file_operation,name1);
            DEBUG("-------SEC NODE READ END-------------\n");

            
            node third_node = doc_get_next_node(file_operation, next_node, "books");
            if(NULL != third_node)
            {
                char *author = doc_get_string(file_operation,third_node,"author");
    		    DEBUG("author = %s\n",author);
                doc_free_string(file_operation,author);
                
                double third_float = doc_get_float(file_operation,third_node,"third_float");
    		    DEBUG("third_float = %f\n",third_float);
                is_bool = doc_get_bool(file_operation,third_node,"third_bool");
    		    DEBUG("is_bool = %d\n",is_bool);
                int third_id = doc_get_int(file_operation,third_node,"third_id");
    		    DEBUG("third_id = %d\n",third_id);
            }
            doc_free_node(file_operation,third_node);
            //list test
            int list_size = doc_list_get_size(file_operation, next_node, "list");
            DEBUG("TEST list count = %d\n",list_size);
            node list_node = doc_get_next_node(file_operation, next_node,"list");
            if(NULL != list_node)
            {
                DEBUG("get list node success\n");
                for(i=0;i<list_size;i++)
                {
                    DEBUG("get list one %d\n",i);
                    node list_one = doc_list_get_list(file_operation, list_node, i);
                    if(NULL != list_one)
                    {
                        char *title = doc_get_string(file_operation, list_one, "title");
                        DEBUG("LIST TEST title = %s\n",title);
                        doc_free_string(file_operation, title);
                        char *author = doc_get_string(file_operation, list_one, "author");
                        DEBUG("LIST TEST author = %s\n",author);
                        doc_free_string(file_operation, author);
                        float price = doc_get_float(file_operation,list_one, "price");
                        DEBUG("LIST TEST price = %f\n",price);
                        int qty = doc_get_int(file_operation,list_one, "qty");
                        DEBUG("LIST TEST qty = %d\n",qty);

                    }
                    doc_free_node(file_operation, list_one);

                }
            }
            doc_free_node(file_operation, list_node);
        }
        doc_free_node(file_operation,next_node);
        

        //一个文件解析完成后，需要释放exit，否则会出现内存泄露
		doc_close(file_operation);
	}
	DEBUG("-----------TEST SEC FILE READ （%s）------------\n",file_path);
    if(NULL != file_operation)
    {
        
        int ret = doc_open(file_operation,file_path);
        doc_free_string(file_operation,file_path);
        if(ret <0)
            DEBUG("open fail\n");
        int id = doc_get_int(file_operation,NULL,"comboH");
        DEBUG("id = %d\n",id);
        
        char *test_hello = doc_get_string(file_operation,NULL,"type");
        DEBUG("json read char = %s\n",test_hello);
        doc_free_string(file_operation,test_hello);
        int is_bool = doc_get_bool(file_operation,NULL,"is_bool");
        DEBUG("is_bool = %d\n",is_bool);
        
        float is_float = doc_get_float(file_operation,NULL,"nums");
        DEBUG("is_float = %f\n",is_float);
        doc_close(file_operation);

    }


}

