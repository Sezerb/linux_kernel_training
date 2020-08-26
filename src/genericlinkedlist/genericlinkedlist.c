/*----------------------------------------------------------------------------------------------------------------------
    Aşağıda genelleştirilmiş bir bağlı liste örneği verilmiştir
----------------------------------------------------------------------------------------------------------------------*/
#include "genericlinkedlist.h"

NODE *InsertItemPrev(NODE *pNode, NODE *pNewNode)
{
    pNewNode->pNext = pNode;
    pNewNode->pPrev = pNode->pPrev;
    pNode->pPrev->pNext = pNewNode;
    pNode->pPrev = pNewNode;
    
    return pNewNode;
}

NODE *InsertItemNext(NODE *pNode, NODE *pNewNode)
{
    pNewNode->pPrev = pNode;
    pNewNode->pNext = pNode->pNext;
    pNode->pNext->pPrev = pNewNode;
    pNode->pNext = pNewNode;
    
    return pNewNode;    
}

NODE *AddItemHead(NODE *pHead, NODE *pNewNode)
{
    return InsertItemNext(pHead, pNewNode);    
}

NODE *AddItemTail(NODE *pHead, NODE *pNewNode)
{
    return InsertItemNext(pHead, pNewNode);
}

void DeleteItem(NODE *pNode)
{
    pNode->pPrev->pNext = pNode->pNext;
    pNode->pNext->pPrev = pNode->pPrev;
}

BOOL WalkList(NODE *pHead, BOOL (*Proc)(NODE *))
{
    NODE *pNode = pHead->pNext;
    
    while (pNode != pHead) {
        if (!Proc(pNode))
            return FALSE;
        pNode = pNode->pNext;
    }
    
    return TRUE;
}

BOOL WalkListReverse(NODE *pHead, BOOL (*Proc)(NODE *))
{
    NODE *pNode = pHead->pPrev;
    
    while (pNode != pHead) {
        if (!Proc(pNode))
            return FALSE;
        pNode = pNode->pPrev;
    }
    
    return TRUE;
}


#if 0

#include <stdio.h>
#include <stdlib.h>
#include "genericlinkedlist.h"

typedef struct tagDEVICE {
    char name[64];
    char host[16];   
    int port;
    NODE node;
} DEVICE;

NODE g_head = {&g_head, &g_head};

BOOL WalkProc(NODE *pNode);


int main(void)
{
    NODE *pNode;
    int i;
    DEVICE devices[] = {
        {"test", "192.168.2.123", 34500},
        {"weather", "192.168.1.120", 50500},
        {"mest", "192.168.2.18", 44500},
        {"sensor", "192.168.3.123", 60500}
    };
    
    for (i = 0; i < 4; ++i) {
        if (i == 3)
            pNode = AddItemTail(&g_head, &devices[i].node);
        else
            AddItemTail(&g_head, &devices[i].node);                
    }   
    
    WalkList(&g_head, WalkProc);
    DeleteItem(pNode);
    printf("********************\n");
    WalkList(&g_head, WalkProc);
    printf("********************\n");
    WalkListReverse(&g_head, WalkProc);            
}

BOOL WalkProc(NODE *pNode)
{ 
    DEVICE *pDevice;
    
    pDevice = container_of(pNode, DEVICE, node);
    
    printf("%s, %s:%d\n", pDevice->name, pDevice->host, pDevice->port);
    
    return TRUE;
}

#endif
