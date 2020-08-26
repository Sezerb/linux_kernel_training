#include <stdio.h>
#include <stdlib.h>
#include "genericlinkedlist.h"

typedef struct tagDEVICE {
    char name[64];
    char host[16];   
    int port;
    NODE node;
} DEVICE;

BOOL WalkProc(NODE *pNode);


int main(void)
{
    
    int i;
    DEVICE devices[] = {
        {"test", "192.168.2.123", 34500},
        {"weather", "192.168.1.120", 50500},
        {"mest", "192.168.2.18", 44500},
        {"sensor", "192.168.3.123", 60500}
    };
    
    HLLIST hLList;
    NODE *pNode;
    
    if ((hLList = CreateLList(malloc)) == NULL) {
        fprintf(stderr, "Can not allocate memory\n");
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i < 4; ++i) {
        if (i == 3)
            pNode = AddItemTail(hLList, &devices[i].node);
        else
            AddItemTail(hLList, &devices[i].node);                
    }   
    
    WalkList(hLList, WalkProc);
    DeleteItem(hLList, pNode);
    printf("********************\n");
    WalkList(hLList, WalkProc);
    printf("********************\n");
    WalkListReverse(hLList, WalkProc);            
}

BOOL WalkProc(NODE *pNode)
{ 
    DEVICE *pDevice;
    
    pDevice = container_of(pNode, DEVICE, node);
    
    printf("%s, %s:%d\n", pDevice->name, pDevice->host, pDevice->port);
    
    return TRUE;
}

