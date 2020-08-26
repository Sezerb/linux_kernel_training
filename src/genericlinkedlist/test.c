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

