#ifndef LIST_H_
#define LIST_H_
#include<stdbool.h>

/*特定程序的声明*/
#define TSIZE 45
struct othercar
{
	char carno[10];
	unsigned char nrfaddr[5];
};

/*一般类型定义*/
typedef struct othercar Item;

typedef struct node
{
	Item item;
	struct node * next;
}Node;

typedef Node * List;
/*函数原型*/
/*操作：初始化一个列表*/
/*操作前：plist指向一个列表*/
/*操作后：该列表被初始化为空列表*/
void InitializeList(List * plist);

/*操作：确定列表是否为空列表*/
/*操作前：plist指向一个已初始化的列表*/
/*操作后：如果该列表为空则返回true；否则返回false*/
bool ListIsEmpty(const List * plist);

/*操作：确定列表是否已满*/
/*操作前：plist指向一个已初始化的列表*/
/*操作后：如果该列表为空则返回true；否则返回false*/
bool ListIsFull(const List * plist);

/*操作：确定列表中项目的个数*/
/*操作前：plist指向一个已初始化的列表*/
/*操作后：返回该列表中项目的个数*/
unsigned int ListItemCount(const List * plist);

/*操作：在列表尾部添加一个项目*/
/*操作前：item是要被增加到列表的项目 plist指向一个已初始化的列表*/
/*操作后：如果可能的话，在列表尾部添加一个新项目，函数返回true，否则函数返回false*/
bool AddItem(Item item, List * plist);

/*操作：把一个函数作用于列表中的每个项目*/
/*操作前：plist指向一个已初始化的列表 pfun指向一个函数，该函数接受一个Item参数并且无返回值*/
/*操作后：pfun指向的函数被作用到列表中的每个项目一次*/
void Traverse(const List * plist, void(*pfun)(Item item));

/*操作：释放已分配的内存（如果有）*/
/*操作前：plist指向一个已初始化的列表*/
/*操作后：为该列表分配的内存已被释放并且该列表被置为空列表*/
void EmptyTheList(List * plist);

#endif
