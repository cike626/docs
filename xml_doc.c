#include"xml.h"

static int xml_init(void)
{
    DEBUG("%s\n",__FUNCTION__);
	xmlInitParser();
	LIBXML_TEST_VERSION
	return 0;
}

static int xml_exit(void *xmlroot)
{
	DEBUG("%s\n",__FUNCTION__);
    
    if (NULL != ((XML_ROOT*)xmlroot)->pxmldoc)
    {
		/* 清理文档链表资源 */
		xmlFreeDoc(((XML_ROOT*)xmlroot)->pxmldoc);
		((XML_ROOT*)xmlroot)->pxmldoc = NULL;
		((XML_ROOT*)xmlroot)->pxmlroot = NULL;
	}

	P_FREE(xmlroot);
    
	/* 通知XML解析结束 */
	//xmlCleanupParser();
    return 0;
}
static void *xml_open(const char *filename)
{
    //xml_init();

    XML_ROOT *xmlroot =NULL;
    xmlroot = calloc(1,sizeof(XML_ROOT));
    if (NULL == xmlroot)
    {
        printf("%s(%d),calloc fail\n",__FUNCTION__,__LINE__);
        return NULL;
        
    }

	/* 读取XML文件 */
	xmlroot->pxmldoc = xmlReadFile(filename, XML_ENCODING, XML_PARSE_RECOVER);
	if (NULL == xmlroot->pxmldoc)
    {   
        printf("%s(%d),xmlReadFile fail\n",__FUNCTION__,__LINE__);
	    return NULL;
    }

	/* 读取XML文件根元素 */
	xmlroot->pxmlroot = xmlDocGetRootElement(xmlroot->pxmldoc);
	if (NULL == xmlroot->pxmlroot) {
		/* 失败时清理资源 */
		xmlFreeDoc(xmlroot->pxmldoc);
		xmlroot->pxmldoc = NULL;
        printf("%s(%d),xmlDocGetRootElement fail\n",__FUNCTION__,__LINE__);
		return NULL;
	}
    /* 确认文档的正确类型 */
	if (xmlStrcmp(xmlroot->pxmlroot->name, BAD_CAST XML_ROOT_TAG)) {
		printf("Document of the wrong type, root node != %s", XML_ROOT_TAG);
		xmlFreeDoc(xmlroot->pxmldoc);
		return NULL;
	}
	return xmlroot;
}
static void *xml_get_next_node(void* xmlroot,const char *tagkey)
{
    if((xmlroot == NULL)||(tagkey ==NULL))
           return NULL;
    XML_ROOT *next_node = NULL;
    next_node = (XML_ROOT *)calloc(1,sizeof(XML_ROOT));    
    if(NULL == next_node)
        return NULL;
    
    next_node->pxmldoc = ((XML_ROOT*)xmlroot)->pxmldoc;
    
    xmlNodePtr curNode = ((XML_ROOT*)xmlroot)->pxmlroot->xmlChildrenNode;
    while (curNode != NULL) {
        if ((!xmlStrcmp(curNode->name, BAD_CAST tagkey))) {
            next_node->pxmlroot = curNode;
            return (void*)next_node;
        }
        curNode = curNode->next;
    }
    return NULL;
}

static void xml_free_node(void* node)
{
    if(node == NULL)
        return;
    P_FREE(node);

}

static int xml_get_int(void* xmlroot,const char *tagkey)
{
    int result = -1;
    xmlNodePtr curNode = ((XML_ROOT*)xmlroot)->pxmlroot->xmlChildrenNode;
    while (curNode != NULL) {
        _XML_GET_INT(tagkey, ((XML_ROOT*)xmlroot)->pxmldoc, curNode, result);
		curNode = curNode->next;
	}
    return result;
}
static double xml_get_float(void* xmlroot,const char *tagkey)
{
    double result = -1.0;
    xmlNodePtr curNode = ((XML_ROOT*)xmlroot)->pxmlroot->xmlChildrenNode;
    while (curNode != NULL) {
        _XML_GET_DOUBLE(tagkey, ((XML_ROOT*)xmlroot)->pxmldoc, curNode, result)
		curNode = curNode->next;
	}
    return result;
}

static char *xml_get_string(void* xmlroot,const char *tagkey)
{
    xmlNodePtr curNode = ((XML_ROOT*)xmlroot)->pxmlroot->xmlChildrenNode;

    while (curNode != NULL) {
        _XML_GET_STRING(tagkey, ((XML_ROOT*)xmlroot)->pxmldoc, curNode);
		curNode = curNode->next;
	}
    return NULL;
}

static int xml_get_bool(void* xmlroot,const char *tagkey)
{
    int result;
    xmlNodePtr curNode = ((XML_ROOT*)xmlroot)->pxmlroot->xmlChildrenNode;
    while (curNode != NULL) {
        _XML_GET_BOOL(tagkey, ((XML_ROOT*)xmlroot)->pxmldoc, curNode, result);
		curNode = curNode->next;
	}
    return -1;
}
static int xml_sec_get_int(void* xmlroot,const char *tagkey,const char *sec_key)
{
	xmlNodePtr curNode = ((XML_ROOT*)xmlroot)->pxmlroot->xmlChildrenNode;
    int result;
	while (curNode != NULL) {
		if ((!xmlStrcmp(curNode->name, BAD_CAST tagkey))) {
			xmlNodePtr node = curNode->xmlChildrenNode;
			while (node != NULL) {
				_XML_GET_INT(sec_key, ((XML_ROOT*)xmlroot)->pxmldoc, node, result);
				 node = node->next;
            }
        }
        curNode = curNode->next;
	}
    return -1;
}
static int xml_sec_get_bool(void* xmlroot,const char *tagkey,const char *sec_key)
{
	xmlNodePtr curNode = ((XML_ROOT*)xmlroot)->pxmlroot->xmlChildrenNode;
    int result = 0;
	while (curNode != NULL) {
		if ((!xmlStrcmp(curNode->name, BAD_CAST tagkey))) {
			xmlNodePtr node = curNode->xmlChildrenNode;
			while (node != NULL) {
				_XML_GET_INT(sec_key, ((XML_ROOT*)xmlroot)->pxmldoc, node, result);
				 node = node->next;
            }
        }
        curNode = curNode->next;
	}
    return result;
}

static double xml_sec_get_float(void* xmlroot,const char *tagkey,const char *sec_key)
{
	xmlNodePtr curNode = ((XML_ROOT*)xmlroot)->pxmlroot->xmlChildrenNode;
    double result = -1.0;
	while (curNode != NULL) {
		if ((!xmlStrcmp(curNode->name, BAD_CAST tagkey))) {
			xmlNodePtr node = curNode->xmlChildrenNode;
			while (node != NULL) {
				_XML_GET_DOUBLE(sec_key, ((XML_ROOT*)xmlroot)->pxmldoc, node, result);
				 node = node->next;
            }
        }
        curNode = curNode->next;
	}
    return result;
}

static char *xml_sec_get_string(void* xmlroot,const char *tagkey,const char *sec_key)
{
	xmlNodePtr curNode = ((XML_ROOT*)xmlroot)->pxmlroot->xmlChildrenNode;
    
	while (curNode != NULL) {
		if ((!xmlStrcmp(curNode->name, BAD_CAST tagkey))) {
			xmlNodePtr node = curNode->xmlChildrenNode;
			while (node != NULL) {
				_XML_GET_STRING(sec_key, ((XML_ROOT*)xmlroot)->pxmldoc, node);
				 node = node->next;
            }
        }
        curNode = curNode->next;
	}
    return NULL;
}
static void xml_string_free(char *str)
{
    P_FREE(str);
}

static struct doc_operation_struct xml_operation = {
	.init = xml_init,
	.open = xml_open,
	.get_next_node = xml_get_next_node,
	.free_node = xml_free_node,
	.get_int = xml_get_int,
	.get_string = xml_get_string,
	.get_bool = xml_get_bool,
	.get_float = xml_get_float,
	.array_get_int = NULL,
	.array_get_bool = NULL,
	.array_get_string = NULL,
	.sec_get_int = xml_sec_get_int,
	.sec_get_string = xml_sec_get_string,
	.sec_get_bool = xml_sec_get_bool,
	.sec_get_float = xml_sec_get_float,
	.string_free = xml_string_free,
	.exit = xml_exit,
};


static struct doc_struct xml_file = {
	.name = "xml file",
	.doc_operation = &xml_operation,
};

static void xml_doc_init(void) __attribute__((constructor));
static void xml_doc_init(void)
{
	register_doc(&xml_file);
}
