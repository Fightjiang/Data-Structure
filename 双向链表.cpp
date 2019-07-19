#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;
int n;

// --------- 双向链表的存储结构---------
typedef struct Dulnode{
    int data; // 数据域
    struct Dulnode *prior; // 指向直接前驱
    struct Dulnode *next; // 指向直接后继
}Dulnode;

// 后插法建立双向链表，不再写有详细注释了
Dulnode *Createdullist(Dulnode *head,int n){
    head = new Dulnode ;
    head->next = NULL;
    head->prior = NULL;
    Dulnode *r = head;
    for(int i=0;i<n;i++)
    {
        Dulnode *p = new Dulnode ;
        cin>>p->data;
        p->next = NULL;
        p->prior = r;
        r->next = p; r=p;
    }
    return head;
}

// 插入
void Insert_dul(Dulnode *head,int i,int x)
{ // 在 i 位置，插入值为 x 的结点
    Dulnode *p = head->next;int j =0; // 这个过程跟单链表一样
    while(p&&j<i-1){// 查找第 i-1 个结点，p 指向该结点
        p = p->next;++j;// 看不懂的话，可以用 i 等于 1，进行检查程序。
    }
    if(!p||j>i-1) cout<<"ERROR"<<endl;// 没有找到指定的位置
    Dulnode *s = new Dulnode ; // 生成新结点 *s ；
    s->data = x;    // 将结点 *s 的数据域值置为 x;
    s->prior = p->prior; // 图操作 1
    p->prior->next = s;// 图操作 2
    s->next = p;// 图操作 3
    p->prior = s;// 图操作 4
    n++; cout<< "Insert success" <<endl; // 总数增加一 ，成功
}

// 删除
void Delete_dul(Dulnode *head,int i)
{
    if(head->next == NULL) // 空表
    {
        printf("empty list!\n");
        return;
    }
    Dulnode *p = head->next;int j =0;
    while(p&&j<i-1){// 查找第 i-1 个结点，p 指向该结点
        p = p->next;++j;
    }
    if(!p||j>i-1) cout<<"Delete ERROR"<<endl;// 没有找到指定的位置
    p->prior->next = p->next;// 图操作 1
    p->next->prior = p->prior;// 图操作 2
    delete p;// 释放内存。
    n--; cout<< "Delete success" <<endl; // 总数减少一 ，成功
}

int main()
{
    cin>>n;
    Dulnode *head ;
    head = Createdullist(head,n);
    Insert_dul(head,2,2);
    Delete_dul(head,2);
    for(int i=0;i<n;i++)
    {
        printf("%d ",head->next->data);
        head = head->next;
    }
    printf("\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",head->data);
        head = head->prior;
    }
    return 0;
}

/*
5
3 5 6 8 7
*/
