#include <sys/time.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef  LOG_TRACE
#define LOG_TRACE printf
#define LOG_INFO(msg)  \
	do{ \
		LOG_TRACE msg; \
		LOG_TRACE("[%s %d] \n",__FUNCTION__,__LINE__);\
	}while(0)

#define LOG_ERROR(err_info)  \
	do{ \
		LOG_TRACE("\033[1;40;31m ");\
		LOG_TRACE err_info; \
		LOG_TRACE("[%s %d] \033[0m \n",__FUNCTION__,__LINE__);\
	}while(0)
#endif


typedef struct  list_node_s
{	
	void *pData;
	int nDataLen;
	struct list_node_s *pNext; 
} list_node_t;

typedef struct list_s
{	
	list_node_t *pNodeHead;
	int nCountNum;
	int nMaxCountNum;
}list_t;

int  list_create( list_t *pList,int nMaxCount);

int  list_destroy( list_t *pList);

int list_get_data(list_t *pList,const void *pKeyData,void *pDesData,int nDataLen,int (*compare)(void *A,void *B));

int list_get_node_address(list_t *pList,list_node_t ** ppListNode,
								const void *pKeyData,int (*compare)(void *A,void *B));

int list_exist_node(list_t *pList,const void *pKeyData,int (*compare)(void *A,void *B));

int list_is_empty(list_t *pList);

int list_append( list_t *pList,void *pData,int nDataLen);

int list_delete_node(list_t *pList,const void *pKeyData,int (*compare)(void *A,void *B));

int list_delete_all(list_t *pList);

