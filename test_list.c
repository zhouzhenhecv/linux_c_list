
#include "list.h"

const char chData[10][100]={"123","124","125","126","666",
                            "234","345","456","567","678"};

int compare(void *A,void *B)
{
	return strcmp((char *)A,(char*)B);
}

int print_list_dump(void *arg)
{
	printf("\n [%s]\n",(char *)arg);
	return 0;
}
int example()
{
	static list_t s_List;
	int MaxCountListNode = 30;
	int ret = -1;
	int i = 0;
	char chTmp[255]={0};

	//list_create(list_t * pList,int nMaxCount)
	ret = list_create(&s_List,MaxCountListNode);
	if(0 != ret)
	{
		LOG_ERROR(("list_create error"));
		return -1;
	}

	LOG_ERROR(("list_create success"));

	ret = list_is_empty(&s_List);
	LOG_ERROR(("list_is_empty  ret[%d]",ret));
	
	for(i = 0; i< 10; i++)
	{
		//list_append(list_t * pList,void * pData,int nDataLen)
		ret = list_append(&s_List,chData[i],sizeof(chData[i]));
		if(0 != ret)
		{
			LOG_ERROR(("list_append error"));
			list_destroy(&s_List);
			return -1;
		}

		LOG_ERROR(("list_append  [%s] success",chData[i]));
		
	}

	//int list_get_data(list_t *pList,const void *pKeyData,void *pDesData,int nDataLen,int (*compare)(void *A,void *B))
	ret = list_get_data(&s_List,"666",chTmp,sizeof(chData[0]),compare);

	if(0 == ret )
	{
		LOG_ERROR(("list_get_data  chTmp [%s]",chTmp));
	}
	else
	{	
		LOG_ERROR(("list_get_data  failed"));
	}

	{
		list_node_t * pListNode = NULL;
		//list_get_node_address(list_t *pList,list_node_t ** ppListNode,const void *pKeyData,int (*compare)(void *A,void *B))

		ret = list_get_node_address(&s_List,&pListNode,"456",compare);

		if(0 == ret)
		{
			LOG_ERROR(("list_get_node_address  pListNode->pData [%s]",(char *)(pListNode->pData)));

			strncpy(pListNode->pData,"111",sizeof("111"));
		}
		else
		{
			LOG_ERROR(("list_get_node_address  failed"));
		}
		
	}

	ret = list_exist_node(&s_List,"111",compare);
	if(0 == ret)
	{
		LOG_ERROR(("list_exist_node  ret[%d]",ret));
	}

    // int list_is_empty(list_t *pList)

	ret = list_is_empty(&s_List);
	LOG_ERROR(("list_is_empty  ret[%d]",ret));
	
	list_dump(&s_List,print_list_dump);

	#if 1
	{
		//int list_delete_node(list_t *pList,const void *pKeyData,int (*compare)(void *A,void *B))
		list_delete_node(&s_List,"21xd",compare);

		list_dump(&s_List,print_list_dump);
	}
	#endif

	#if 1
	{
		 list_delete_all(&s_List);
		 list_dump(&s_List,print_list_dump);
	}
	#endif

	ret = list_destroy(&s_List);

	if(0 != ret)
	{
		LOG_ERROR(("list_destroy error"));
		return -1;
	}
	
	return 0;
}

int main()
{
	example();
	return 0;
}


