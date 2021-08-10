/*
    线性表的链式存储结构实现之单链表
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
typedef struct Node{ // 单链表
    ElemType data;
    struct Node *next;
} LNode, *LinkList;

/* 函数原型 */
Status InitListHead(LinkList *L, int n); // 头插法初始化
Status InitListTail(LinkList *L, int n); // 尾插法初始化
Status ListEmpty(LinkList L);
Status ClearList(LinkList *L);
/* 用e返回线性表L中第i个元素的值 */
Status GetElem(LinkList L, int i, ElemType *e);
/* 在线性表L中第i个元素之前插入元素e */
Status ListInsert(LinkList *L, int i, ElemType e);
/* 删除线性表L中第i个元素，并用e返回其值 */
Status ListDelete(LinkList *L, int i, ElemType *e);
/* 在线性表L中查找与给元素e相等的第一个元素的位置，若元素e不在线性表中则返回0 */
int LocateElem(LinkList L, ElemType e);
int ListLength(LinkList L);
void PrintList(LinkList L);

int main(void)
{
    LinkList L = NULL;
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
                InitListTail(&L, list_init_len);
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
                GetElem(L, pos, &temp);
                printf("%-5d\n", temp);
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
Status InitListHead(LinkList *L, int n)
{
    int i;
    LinkList p = NULL;

    *L = (LinkList )malloc(sizeof(LNode));
    if (*L == NULL) {
        printf("Allocating failed!\n");
        return ERROR;
    }
    (*L)->next = NULL;
    for (i=0; i<n; i++) { // 头插法
        p = (LinkList )malloc(sizeof(LNode));
        if (p == NULL) {
            printf("Allocating failed!\n");
            return ERROR;
        }
        p->data = i; // 这个数据值是随便给的，没实际意义
        p->next = (*L)->next;
        (*L)->next = p;
    }
    return OK;
}

// 带头结点的链表处理起来方便一点
Status InitListTail(LinkList *L, int n)
{
    int i;
    LinkList p = NULL;
    LinkList tail = NULL; // 尾指针

    *L = (LinkList )malloc(sizeof(LNode));
    if (*L == NULL) {
        printf("Allocating failed!\n");
        return ERROR;
    }
    (*L)->next = NULL;
    tail = *L;
    for (i=0; i<n; i++) { // 尾插法
        p = (LinkList )malloc(sizeof(LNode));
        if (p == NULL) {
            printf("Allocating failed!\n");
            return ERROR;
        }
        p->data = i; // 这个数据值是随便给的，没实际意义
        tail->next = p;
        tail = p; // 尾指针后移
    }
    tail->next = NULL;
    return OK;
}


Status ListEmpty(LinkList L)
{
    return (L->next==NULL)?TRUE:FAULS; // 运算符优先级问题，*L->next是会报错的，需要给*L加上括号(*L)->next
}

Status ClearList(LinkList *L)
{
    LinkList p = NULL;
    LinkList q = NULL;

    p = (*L)->next;
    while (p != NULL) {
        q = p->next; // 先把p->next存到q中，因为后面free(p)后再取p->next是非法操作
        free(p);
        p = q;
    }
    return OK;
}

Status GetElem(LinkList L, int i, ElemType *e)
{
    int k=1;
    LinkList p = L->next;

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
Status ListInsert(LinkList *L, int i, ElemType e)
{
    int k = 1;
    LinkList p = *L;
    LinkList q = NULL;

    while (p!=NULL && k<i) {
        p = p->next;
        k++;
    }
    if (p==NULL || k>i) { // 只有当i<1时才会出现k>i的情况，该判断用于排除i不在1 <= i <= Length(L)+1的情况
        printf("Position is invalid\n");
        return ERROR;
    } else { 
        q = (LinkList )malloc(sizeof(LNode));
        q->data = e;
        q->next = p->next;
        p->next = q;
    }
    return OK;
}

/* 删除线性表L中第i个元素，并用e返回其值 */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
    int k = 1;
    LinkList p = (*L);
    LinkList q = NULL; 

    while (p->next!=NULL && k<i) { // 先找到第i个元素，p指向第i个结点的前驱
        p = p->next;
        k++;
    }
    if (p->next==NULL || k>i) {
        printf("Position is invalid\n");
        return ERROR;
    } else {
        q = p->next; // q指向待删除的结点
        *e = q->data;
        p->next = q->next;
        free(q);
        return OK;
    }
}

/* 在线性表L中查找与给元素e相等的第一个元素的位置，若元素e不在线性表中则返回0 */
int LocateElem(LinkList L, ElemType e)
{
    int pos = 0;
    LinkList p = L->next;

    while (p != NULL) {
        pos++;
        if (e == p->data) {
            return pos;
        }
        p = p->next;
    }
    return 0;
}

int ListLength(LinkList L)
{
    int cnt = 0;
    
    L = L->next;
    while (L != NULL) {
        cnt++;
        L = L->next;
    }
    return cnt;
}

void PrintList(LinkList L)
{
    L = L->next;
    while (L != NULL) {
        printf("%-5d", L->data);
        L = L->next;
    }
    printf("\n");
    return;
}