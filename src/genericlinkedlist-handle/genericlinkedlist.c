/*----------------------------------------------------------------------------------------------------------------------
    Aşağıda genelleştirilmiş bir bağlı liste örneği verilmiştir
----------------------------------------------------------------------------------------------------------------------*/

#include "genericlinkedlist.h"

static NODE *insertItemPrev(NODE *pNode, NODE *pNewNode);
static NODE *insertItemNext(NODE *pNode, NODE *pNewNode);
static void deleteItem(NODE *pNode);


HLLIST CreateLList(void *(*falloc)(size_t size))
{
    HLLIST hLList;
    
    if ((hLList = (HLLIST) falloc(sizeof(LLIST))) == NULL)
        return NULL;
    
    hLList->head.pNext = &hLList->head;
    hLList->head.pPrev = &hLList->head;
    hLList->count = 0;    
    
    return hLList;
}

NODE *InsertItemPrev(HLLIST hLList, NODE *pNode, NODE *pNewNode)
{
    ++hLList->count;
    
    return insertItemPrev(pNode, pNewNode);
}

NODE *InsertItemNext(HLLIST hLList, NODE *pNode, NODE *pNewNode)
{
   ++hLList->count;
    
    return insertItemNext(pNode, pNewNode);
}

static NODE *insertItemPrev(NODE *pNode, NODE *pNewNode)
{
    pNewNode->pNext = pNode;
    pNewNode->pPrev = pNode->pPrev;
    pNode->pPrev->pNext = pNewNode;
    pNode->pPrev = pNewNode;
    
    return pNewNode;    
}

static NODE *insertItemNext(NODE *pNode, NODE *pNewNode)
{
    pNewNode->pPrev = pNode;
    pNewNode->pNext = pNode->pNext;
    pNode->pNext->pPrev = pNewNode;
    pNode->pNext = pNewNode;
    
    return pNewNode;    
}


NODE *AddItemHead(HLLIST hLList, NODE *pNewNode)
{
    return InsertItemNext(hLList, &hLList->head, pNewNode);    
}

NODE *AddItemTail(HLLIST hLList, NODE *pNewNode)
{
    return InsertItemPrev(hLList, &hLList->head, pNewNode);    
}

void DeleteItem(HLLIST hLList, NODE *pNode)
{
    --hLList->count;
    deleteItem(pNode);
}

static void deleteItem(NODE *pNode)
{
    pNode->pPrev->pNext = pNode->pNext;
    pNode->pNext->pPrev = pNode->pPrev;
}

BOOL WalkList(HLLIST hLList, BOOL (*Proc)(NODE *))
{
    NODE *pNode = hLList->head.pNext;
    
    while (pNode != &hLList->head) {
        if (!Proc(pNode))
            return FALSE;
        pNode = pNode->pNext;
    }
    
    return TRUE;
}

BOOL WalkListReverse(HLLIST hLList, BOOL (*Proc)(NODE *))
{
    NODE *pNode = hLList->head.pPrev;
    
    while (pNode != &hLList->head) {
        if (!Proc(pNode))
            return FALSE;
        pNode = pNode->pPrev;
    }
    
    return TRUE;
}

void Clear(HLLIST hLList)
{
    hLList->count = 0;
    hLList->head.pNext = &hLList->head;
    hLList->head.pPrev = &hLList->head;
}

void CloseList(HLLIST hLList, void (*ffree)(void *))
{
    ffree(hLList);
}


