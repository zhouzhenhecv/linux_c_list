#include "list.h"
#include <sys/time.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int  list_create( list_t *pList,int nMaxCount)
{
	if(NULL == pList ||
		nMaxCount <= 0)
	{
		LOG_ERROR(("param error"));
		return -1;
	}

	pList->nCountNum = 0;
	pList->pNodeHead = NULL; 
	pList->nMaxCountNum = nMaxCount;

	return 0;
}

int  list_destroy( list_t *pList)
{
	list_node_t *pListNode = NULL;
	list_node_t *pCurListNode = NULL;

	LOG_ERROR(("  come in "));
	
	if(NULL == pList)
	{
		LOG_ERROR(("param error"));
		return -1;
	}

	if(NULL == pList->pNodeHead)
	{
		pList->nCountNum = 0;
		return 0;
	}
	
	pListNode = pList->pNodeHead;

	// 1.Node by node release
	while(NULL != pListNode)
	{

		pCurListNode = pListNode;
		pListNode = pListNode->pNext ;
		if(NULL != pCurListNode->pData)
		{
			free(pCurListNode->pData); //free node data
		}

		free(pCurListNode);// free list node 
	}

	pList->pNodeHead = NULL;
	pList->nCountNum = 0;
	pList->nMaxCountNum = 0;
	return 0;

}

int list_get_data(list_t *pList,const void *pKeyData,void *pDesData,int nDataLen,int (*compare)(void *A,void *B))

{
	list_node_t *pListNode = NULL;
	list_node_t *pCurListNode = NULL;
	list_node_t *pListNodeTmp = NULL;

	if((NULL == pList) ||
		(NULL == pList->pNodeHead) ||
		(NULL == pDesData) || 
		(nDataLen <= 0 )||
		(NULL == pKeyData))
	{
		LOG_ERROR(("param error"));
		return -1;
	}
	
	pListNode = pList->pNodeHead;
	pCurListNode = pListNode;
	while(NULL != pListNode)
	{
		if(0 == compare(pKeyData,pListNode->pData))
		{
			break;
		}
		pListNode = pListNode->pNext;
		pCurListNode = pListNode;
	}

	if(NULL == pCurListNode)
	{
		LOG_ERROR(("not found"));
		return -1;
	}

	//find pCurList
	memset(pDesData, 0, nDataLen);
	memcpy(pDesData, pCurListNode->pData,nDataLen);
	
	return 0;
}


int list_get_node_address(list_t *pList,list_node_t ** ppListNode,const void *pKeyData,int (*compare)(void *A,void *B))

{
	list_node_t *pListNode = NULL;
	list_node_t *pCurListNode = NULL;
	list_node_t *pListNodeTmp = NULL;

	if((NULL == pList) ||
		(NULL == pList->pNodeHead) ||
		(NULL == ppListNode)||
		(NULL == pKeyData) )
	{
		LOG_ERROR(("param error"));
		return -1;
	}
	
	pListNode = pList->pNodeHead;
	pCurListNode = pListNode;
	while(NULL != pListNode)
	{
		if(0 == compare(pKeyData,pListNode->pData))
		{
			break;
		}
		pListNode = pListNode->pNext;
		pCurListNode = pListNode;
	}

	if(NULL == pCurListNode)
	{
		LOG_ERROR(("not found"));
		*ppListNode = NULL;
		return -1;
	}

	//find pCurList
	
	*ppListNode = pCurListNode;
	
	return 0;
}

int list_exist_node(list_t *pList,const void *pKeyData,int (*compare)(void *A,void *B))

{
	list_node_t *pListNode = NULL;
	list_node_t *pCurListNode = NULL;
	list_node_t *pListNodeTmp = NULL;

	if((NULL == pList) ||
		(NULL == pKeyData))
	{
		LOG_ERROR(("param error"));
		return -1;
	}

	if((NULL == pList->pNodeHead) && (pList->nCountNum == 0))
	{
		LOG_ERROR(("not found   in  list "));
		return -1;
	}
	
	pListNode = pList->pNodeHead;
	pCurListNode = pListNode;
	while(NULL != pListNode)
	{
		if(0 == compare(pKeyData,pListNode->pData))
		{
			break;
		}
		pListNode = pListNode->pNext;
		pCurListNode = pListNode;
	}

	if(NULL == pCurListNode)
	{
		LOG_ERROR(("not found   in  list "));
		return -1;
	}

	LOG_ERROR(("--------found   in  list "));
	
	return 0;
}

int list_is_empty(list_t *pList)
{
	
	if(NULL == pList)
	{
		LOG_ERROR(("param error"));
		return -1;
	}

	if((NULL == pList->pNodeHead)
		&& (0 == pList->nCountNum) )
	{
		return 1; // 1  is empty
	}
	
	return 0; //0  is  not empty
}

int list_append( list_t *pList,void *pData,int nDataLen)

{
	list_node_t *pListNode = NULL;
	list_node_t *pCurListNode = NULL;
	list_node_t *pListNodeTmp = NULL;

	if((NULL == pList) ||
		(NULL == pData) ||
		(nDataLen <= 0))
	{
		LOG_ERROR(("param error"));
		return -1;
	}

	if(pList->nCountNum >= pList->nMaxCountNum)
	{
		LOG_ERROR(("list is full ,error!"));
		return -1;
	}
	
	pListNode = pList->pNodeHead;
	
	pCurListNode = pListNode;
	if(NULL != pListNode) //无节点，则不进入循环
	{
		while(NULL != pListNode->pNext)
		{
			pListNode = pListNode->pNext;
			pCurListNode = pListNode;
		}
	}

	pListNodeTmp = (list_node_t * )malloc(sizeof(list_node_t));

	if(NULL == pListNodeTmp)
	{
		LOG_ERROR(("no enough memory!"));
		return -1;
	}
	pListNodeTmp->pData= NULL;
	pListNodeTmp->pNext = NULL;
	
	 pListNodeTmp->pData= (void *)malloc(nDataLen);
	if(NULL == pListNodeTmp->pData)
	{
		LOG_ERROR(("no enough memory!"));
		
		free(pListNodeTmp);
		return -1;
	}

	memset(pListNodeTmp->pData, 0,nDataLen);

	memcpy(pListNodeTmp->pData, pData,nDataLen);

	if(NULL != pCurListNode)
	{
		pCurListNode->pNext = pListNodeTmp; //add list node  当前链表大于1个节点 
	}
	else
	{//add list node
		
		pCurListNode = pListNodeTmp;//0个节点的时候
		pList->pNodeHead = pListNodeTmp;;
	}
	pList->nCountNum++;

	return 0;
}

int list_delete_node(list_t *pList,const void *pKeyData,int (*compare)(void *A,void *B))

{
	list_node_t *pListNode = NULL;
	list_node_t *pCurListNode = NULL;
	list_node_t *pPreListNode = NULL;
	list_node_t *pListNodeTmp = NULL;

	if((NULL == pList) ||
		(NULL == pList->pNodeHead) ||
		(NULL == pKeyData))
	{
		LOG_ERROR(("param error"));
		return -1;
	}
	
	pListNode = pList->pNodeHead;
	pCurListNode = pListNode;
	pPreListNode = pListNode;
	while(NULL != pListNode)
	{
		if(0 == compare(pKeyData,pListNode->pData))
		{
			break;
		}
		pPreListNode = pListNode;
		pListNode = pListNode->pNext;
		pCurListNode = pListNode;
	}

	if(NULL == pCurListNode)
	{
		LOG_ERROR(("not found"));
		return -1;
	}
	else
	{
		//(free)
		if(pListNode == pPreListNode) //第一个节点
		{
			pList->pNodeHead = pPreListNode->pNext;
			if(NULL != pPreListNode->pData)
			{
				free(pPreListNode->pData);
			}

			free(pPreListNode);
		}
		else
		{
			pPreListNode->pNext = pCurListNode->pNext;
			if(NULL != pCurListNode->pData)
			{
				free(pCurListNode->pData);
			}

			free(pCurListNode);
		}
		
	}

	pList->nCountNum--;
	if(pList->nCountNum < 0)
	{
		LOG_ERROR((" pList->nCountNum  error"));
		return -1;
	}
	return 0;
}

int list_delete_all(list_t *pList)

{
	list_node_t *pListNode = NULL;
	list_node_t *pCurListNode = NULL;
	
	if((NULL == pList) ||
		((NULL != pList) && (NULL == pList->pNodeHead)))
	{
		LOG_ERROR(("param error"));
		return -1;
	}

	pListNode = pList->pNodeHead;
	pCurListNode = pListNode;	
	while(NULL != pListNode)
	{
		pListNode = pListNode->pNext;
		if(NULL != pCurListNode->pData)
		{
			free(pCurListNode->pData);
		}

		free(pCurListNode);
		pCurListNode = pListNode;
		
	}
	pList->pNodeHead = NULL;
	pList->nCountNum = 0;
	
	return 0;
}

int list_dump(list_t *pList,int (*print_list_dump)(void *))
{
	list_node_t *pListNode = NULL;
	int i = 0;
	if((NULL == pList) ||
		((NULL != pList) && (NULL == pList->pNodeHead)))
	{
		LOG_ERROR(("param error"));
		return -1;
	}

	pListNode = pList->pNodeHead;
	while(NULL != pListNode)
	{
		LOG_ERROR(("list node %d",i));
		i++;
		print_list_dump(pListNode->pData);
		pListNode = pListNode->pNext;
	}

	return 0;
}

