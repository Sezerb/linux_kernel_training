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

typedef int BOOL;

/* Function prototypes */

NODE *InsertItemPrev(NODE *pNode, NODE *pNewNode);
NODE *InsertItemNext(NODE *pNode, NODE *pNewNode);
NODE *AddItemHead(NODE *pHead, NODE *pNewNode);
NODE *AddItemTail(NODE *pHead, NODE *pNewNode);
void DeleteItem(NODE *pNode);
BOOL WalkList(NODE *pHead, BOOL (*Proc)(NODE *));
BOOL WalkListReverse(NODE *pHead, BOOL (*Proc)(NODE *));

/* Macros */
#define container_of(ptr, type, member) ((type *)((char *)(ptr) - offsetof(type, member)))

#endif /* GENERICLINKEDLIST_H_ */



