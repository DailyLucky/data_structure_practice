/*
    线性表的顺序存储结构实现
*/

#include <stdio.h>
#include <stdlib.h>

/* 一些类型的定义与说明 */
#define OK  1
#define ERROR  0
#define TRUE  1
#define FAULS  0

#define LIST_MAXSIZE  100 // 线性表最大存储容量，有需要时可以再继续分配
typedef int Status; // Status用作函数的返回值类型，实际上是返回整型值
typedef int ElemType; // 操作的数据类型为整型
typedef struct {
    ElemType data[LIST_MAXSIZE];
    int length; // 线性表当前长度
} SqList;

/* 函数原型 */
/* 用e返回线性表L中第i个元素的值 */
Status GetElem(const SqList *L, int i, ElemType *e);
/* 在线性表L中第i个元素之前插入元素e */
Status ListInsert(SqList *L, int i, ElemType e);
/* 删除线性表L中第i个元素，并用e返回其值 */
Status ListDelete(SqList *L, int i, ElemType *e);
/* 在线性表L中查找与给元素e相等的第一个元素的位置，若元素e不在线性表中则返回0 */
int LocateElem(const SqList *L, ElemType e);


int main(void)
{
    int i;
    ElemType val = 0;
    ElemType temp = 0;
    SqList L = {{0}, 0};

    for (i=0; i<4; i++) { // 插入测试
        scanf("%d", &val);
        ListInsert(&L, i+1, val);
    }
    for (i=0; i<3; i++) { // 删除测试
        ListDelete(&L, i+2, &temp);
    }
    GetElem(&L, 1, &temp);
    GetElem(&L, 2, &temp);
    return 0;
}

Status GetElem(const SqList *L, int i, ElemType *e)
{
    if (i<1 || i>L->length || L->length==0) { // 输入位置无效或线性表为空
        printf("Position is invalid!\n");
        return ERROR;
    }
    *e = L->data[i-1];
    return OK;
}

Status ListInsert(SqList *L, int i, ElemType e)
{
    int j;

    if (L->length == LIST_MAXSIZE) {
        printf("Space is full! Inserting failed!\n");
        return ERROR;
    }
    if (i<1 || i>L->length+1) {
        return ERROR;
    }
    for (j=L->length-1; j>=i-1; j--) { // 待插入位置后的元素向右移一位
        L->data[j+1] = L->data[j];
    }
    L->data[i-1] = e;
    L->length++;
    return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e)
{
    int j;

    if (i<1 || i>L->length) {
        return ERROR;
    }
    *e = L->data[i-1];
    for (j=i; j<=L->length-1; j++) { // 待删除位置后的元素向左移一位
        L->data[j-1] = L->data[j];
    }  
    L->length--;
    return OK;
}

int LocateElem(const SqList *L, ElemType e)
{
    int i;

    for (i=0; i<L->length; i++) {
        if (e == L->data[i]) {
            return (i+1);
        }
    }
    return 0; // 没有找到元素e
}