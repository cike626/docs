
#ifndef __XML_H__
#define __XML_H__

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include"doc_manage.h"
#define XML_ENCODING	"ISO-8859-1"		/* 编码方式 */
#define XML_ROOT_TAG	"ROOT"			/* 根节点标签 */

typedef struct
{
	xmlDocPtr pxmldoc;			/* XML数据文件文档实例 */
	xmlNodePtr pxmlroot;			/* XML数据文件根节点 */
} XML_ROOT;

#define XML_ENABLE_STR      "y"     /* Enable string */
#define XML_DISABLE_STR     "n"     /* Disable string */
#define XML_ENABLE_VAL      1       /* Enable value */
#define XML_DISABLE_VAL     0       /* Disable value */

#define _XML_GET_INT(tag, xmldoc, node, result)	\
{	\
    xmlChar *key = NULL;	\
	if (!xmlStrcmp((node)->name, BAD_CAST tag)) {	\
		(key) = xmlNodeListGetString((xmldoc), (node)->xmlChildrenNode, 1);	\
		(result) = atoi((const char * __restrict__)(key));	\
		xmlFree(key);	\
		return (result);\
	}	\
}
#define _XML_GET_BOOL(tag, xmldoc, node, result)	\
{	\
    xmlChar *key = NULL;	\
	if (!xmlStrcmp((node)->name, BAD_CAST tag)) {	\
		(key) = xmlNodeListGetString((xmldoc), (node)->xmlChildrenNode, 1);	\
		if (!strcmp(XML_ENABLE_STR, (char *)(key))) {	\
			(result) = XML_ENABLE_VAL;	\
		} else {	\
			(result) = XML_DISABLE_VAL;	\
		}	\
		xmlFree(key);	\
		return (result);\
	}	\
}


#define _XML_GET_DOUBLE(tag, xmldoc, node, result)	\
{	\
    xmlChar *key = NULL;	\
	if (!xmlStrcmp((node)->name, BAD_CAST tag)) {	\
		(key) = xmlNodeListGetString((xmldoc), (node)->xmlChildrenNode, 1);	\
		(result) = atof((const char * __restrict__)(key));	\
		xmlFree(key);	\
		return (result);\
	}	\
}

#define _XML_GET_STRING(tag, xmldoc, node)	\
{	\
    xmlChar *key = NULL;	\
    int len;\
    char *result = NULL;\
	if (!xmlStrcmp((node)->name, BAD_CAST tag)) {	\
		(key) = xmlNodeListGetString((xmldoc), (node)->xmlChildrenNode, 1);	\
		len = strlen((const char *)key);\
		result = calloc(len+1,sizeof(char));\
		if(NULL != result){\
		strncpy(result, (char *)key, len);	 \
		xmlFree(key);	\
		return result;}\
		else{ \
		    return NULL;}\
	}	\
}



#endif
