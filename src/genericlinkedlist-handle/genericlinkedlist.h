#ifndef GENERICLINKEDLIST_H_
#define GENERICLINKEDLIST_H_

#include <stddef.h>

/* Symbolic constants */
#define TRUE    1
#define FALSE   0

/*Type definitions*/
typedef struct tagNODE {    
    struct tagNODE *pPrev;
    struct tagNODE *pNext;
} NODE;


typedef struct tagLIST {
    NODE head;
    size_t count;
} LLIST, *HLLIST;

typedef int BOOL;

/* Function prototypes */

HLLIST CreateLList(void *(*alloc)(size_t size));
NODE *InsertItemPrev(HLLIST hLList, NODE *pNode, NODE *pNewNode);
NODE *InsertItemNext(HLLIST hLList, NODE *pNode, NODE *pNewNode);
NODE *AddItemHead(HLLIST hLList, NODE *pNewNode);
NODE *AddItemTail(HLLIST hLList, NODE *pNewNode);
void DeleteItem(HLLIST hLList, NODE *pNode);
BOOL WalkList(HLLIST hLList, BOOL (*Proc)(NODE *));
BOOL WalkListReverse(HLLIST hLList, BOOL (*Proc)(NODE *));
void Clear(HLLIST hLList);
void CloseList(HLLIST hLList, void (*ffree)(void *));

/* Macros */

#define GetCount(hLList)                    ((hLList)->count)
#define container_of(ptr, type, member)     ((type *)((char *)(ptr) - offsetof(type, member)))

#endif /* GENERICLINKEDLIST_H_ */



