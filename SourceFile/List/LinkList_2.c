/*
    线性表的链式存储结构实现之双向链表
*/

#include <stdio.h>
#include <stdlib.h>



/* 一些类型的定义与说明 */
#define OK  1
#define ERROR  0
#define TRUE  1
#define FAULS  0

typedef int Status; // Status用作函数的返回值类型，实际上是返回整型值
typedef int ElemType; // 操作的数据类型为整型
typedef struct Node{ // 双向链表
    ElemType data;
    struct Node *prior;
    struct Node *next;
} DuLNode, *DuLinkList;

/* 函数原型 */
Status InitListHead(DuLinkList *L, int n);
Status ListEmpty(DuLinkList L);
Status ClearList(DuLinkList *L);
/* 用e返回线性表L中第i个元素的值 */
Status GetElem(DuLinkList L, int i, ElemType *e);
/* 在线性表L中第i个元素之前插入元素e */
Status ListInsert(DuLinkList *L, int i, ElemType e);
/* 删除线性表L中第i个元素，并用e返回其值 */
Status ListDelete(DuLinkList *L, int i, ElemType *e);
/* 在线性表L中查找与给元素e相等的第一个元素的位置，若元素e不在线性表中则返回0 */
int LocateElem(DuLinkList L, ElemType e);
int ListLength(DuLinkList L);
void PrintList(DuLinkList L);

int main(void)
{
    DuLinkList L = NULL;
    int val = 0;
    int list_init_len = 0;
    int pos = 0;
    ElemType elem = 0;
    ElemType temp = 0;
    int flag = 0; // 循环结束标记

    while (1) {
        printf("Please select the operate by entering matching number:\n");
        printf("1.Initialize  2.Insert  3.Delete  4.GetElem  5.Print  6.exit\n");
        scanf("%d", &val);
        switch (val) {
            case 1: {
                printf("Please enter the length of list to be initialized:");
                scanf("%d", &list_init_len);
                InitListHead(&L, list_init_len);
                break;
            }
            case 2: {
                printf("Insert (elem pos):");
                scanf("%d %d", &elem, &pos);
                ListInsert(&L, pos, elem);
                break;
            }
            case 3: {
                printf("Delete (pos):");
                scanf("%d", &pos);
                ListDelete(&L, pos, &temp);
                break;
            }
            case 4: {
                printf("GetElem (pos):");
                scanf("%d", &pos);
                if (GetElem(L, pos, &temp) == OK) {
                    printf("%-5d\n", temp);
                }              
                break;
            }
            case 5: {
                PrintList(L);
                break;
            }
            case 6: {
                flag = 1;
                break;
            }
            default : {
                printf("Input is invalid!\n");
            }           
        }
        if (flag == 1) {
            break;
        }
    }

    return 0;
}

// 带头结点的链表处理起来方便一点
Status InitListHead(DuLinkList *L, int n)
{
    int i;
    DuLinkList p = NULL;

    *L = (DuLinkList )malloc(sizeof(DuLNode));
    if (*L == NULL) {
        printf("Allocating failed!\n");
        return ERROR;
    }
    (*L)->prior = NULL;
    (*L)->next = NULL;
    for (i=0; i<n; i++) { // 头插法
        p = (DuLinkList )malloc(sizeof(DuLNode));
        if (p == NULL) {
            printf("Allocating failed!\n");
            return ERROR;
        }
        // 插入结点时一般先把新节点的指针域处理好
        p->data = i; // 这个数据值是随便给的，没实际意义
        p->next = (*L)->next;
        p->prior = *L;
        if ((*L)->next != NULL) {
            (*L)->next->prior = p; // 初始化时(*L)->next == NULL，这里有非法操作
        }
        (*L)->next = p;
    }
    return OK;
}

Status ListEmpty(DuLinkList L)
{
    return (L->next==NULL)?TRUE:FAULS; // 运算符优先级问题，*L->next是会报错的，需要给*L加上括号(*L)->next
}

Status ClearList(DuLinkList *L)
{
    DuLinkList p = NULL;
    DuLinkList q = NULL;

    p = (*L)->next;
    while (p != NULL) {
        q = p->next; // 先把p->next存到q中，因为后面free(p)后再取p->next是非法操作
        free(p);
        p = q;
    }
    return OK;
}

Status GetElem(DuLinkList L, int i, ElemType *e)
{
    int k=1;
    DuLinkList p = L->next;

    while (p!=NULL && k<i) {
        p = p->next;
        k++;
    }
    if (p==NULL || k>i) {
        printf("Position is invalid\n");
        return ERROR;
    } else { // k == i
        *e = (p->data);
        return OK;
    }
}

/* 在线性表L中第i个元素之前插入元素e */
Status ListInsert(DuLinkList *L, int i, ElemType e)
{
    int k = 1;
    DuLinkList p = *L;
    DuLinkList q = NULL;

    while (p!=NULL && k<i) { // 找到第i-1个结点
        p = p->next;
        k++;
    }
    if (p==NULL || k>i) { // 只有当i<1时才会出现k>i的情况。该判断用于排除i不在1 <= i <= Length(L)+1的情况
        printf("Position is invalid\n");
        return ERROR;
    } else { 
        q = (DuLinkList )malloc(sizeof(DuLNode));
        q->data = e;
        q->next = NULL;
        q->next = p->next;
        q->prior = p;
        if (p->next != NULL) {
            p->next->prior = q;
        }      
        p->next = q;
    }
    return OK;
}

/* 删除线性表L中第i个元素，并用e返回其值 */
Status ListDelete(DuLinkList *L, int i, ElemType *e)
{
    int k = 1;
    DuLinkList p = (*L);
    DuLinkList q = NULL; 

    while (p->next!=NULL && k<i) { // 先找到第i个元素，并用p指向它的前驱结点
        p = p->next;
        k++;
    }
    if (p->next==NULL || k>i) {
        printf("Position is invalid\n");
        return ERROR;
    } else {
        q = p->next; // q指向将要删除的那个节点
        *e = q->data;
        if (q->next != NULL) {
            q->next->prior = p;
        }      
        p->next = q->next;
        free(q);
        return OK;
    }
}

/* 在线性表L中查找与给元素e相等的第一个元素的位置，若元素e不在线性表中则返回0 */
int LocateElem(DuLinkList L, ElemType e)
{
    int pos = 0;
    DuLinkList p = L->next;

    while (p != NULL) {
        pos++;
        if (e == p->data) {
            return pos;
        }
        p = p->next;
    }
    return 0;
}

int ListLength(DuLinkList L)
{
    int cnt = 0;
    
    L = L->next;
    while (L != NULL) {
        cnt++;
        L = L->next;
    }
    return cnt;
}

void PrintList(DuLinkList L)
{
    L = L->next;
    while (L != NULL) {
        printf("%-5d", L->data);
        L = L->next;
    }
    printf("\n");
    return;
}