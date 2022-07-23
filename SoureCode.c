#include <stdio.h>
#include<malloc.h>
#define  MAXVOLUME 10;//箱子的最大容积

typedef struct{
	int id;//货物id
	int v;//货物体积
}Element;

typedef struct node {
	int id;//货物链的货物id
	struct node *link;//指向下一个货物的指针
}Goods;

typedef struct box {
	int remainvolume;//箱子的剩余体积
	Goods * hgoodlink;//存放货物链的头指针
	struct box *next;//指向下一个箱子的指针
}Boxs;

void Sort(Element *element, int n);//排序
Boxs *InBox(Element *element, int n);//装箱
void Print(Boxs* hbox);//输出

void Sort(Element *element, int n) {//选择排序
	for (int i = 0; i < n-1 ; i++) {
		for (int j = i + 1; j < n; j++) {
			if (element[i].v < element[j].v) {
				Element temp = element[i];
				element[i] = element[j];
				element[j] = temp;
			}
		}
	}
}

Boxs *InBox(Element *element, int n) {
	Boxs *hbox=NULL, *p, *tail=NULL;//指向箱子的头指针，尾指针和遍历箱子的指针
	Goods *qnew,*q;//指向新货物的指针和遍历货物链的指针
	for (int i = 0; i < n; i++) {//遍历每一个货物
		for (p = hbox; p&&p->remainvolume < element[i].v; p = p->next);//寻找可以容下货物的箱子
		if (!p) {//如果没找到，开一个新箱子
			p = (Boxs *)malloc(sizeof(Boxs));
			p->remainvolume = MAXVOLUME;//初始化箱子的容积
			p->hgoodlink = NULL; p->next = NULL;
			if (!hbox)hbox = tail = p;//第一次开箱子
			else tail = tail->next = p;//不是第一次开箱子
		}
		p->remainvolume -= element[i].v;//放置货物并减去相应的体积
		qnew = (Goods *)malloc(sizeof(Goods));//为该货物开辟一个空间以链接到该箱子的货物链上
		qnew->id = element[i].id;
		qnew->link = NULL;
		for (q = p->hgoodlink; q&&q->link; q = q->link);//找到货物链上挂货物的位置
		if (!q)p->hgoodlink = qnew;//该货物链第一次挂货物
		else q->link = qnew;//该货物链不是第一次挂货物
	}
	return hbox;//返回箱子的头指针
}

void Print(Boxs *hbox) {
	int i =1 ;
	for (Boxs *p = hbox;p;p=p->next ) {
		printf("第%d个箱子有：",i++);
		for (Goods *q = p->hgoodlink; q; q = q->link) {
			printf("%d号 ", q->id);
		}
		printf("箱子\n");
	}
	printf("一共有%d个箱子!", i-1);
}

void main(){
	int n;//货物个数
	printf("请输入货物个数:");
	scanf_s("%d", &n);
	Element *element = (Element*)malloc(sizeof(Element)*n);//为n个货物分配内存空间
	for (int i = 0; i < n; i++) {//初始化货物信息
		int value;
		element[i].id = i+1;//货物ID,从1-n
		scanf_s("%d", &value);//初始化每个货物的体积（不超过箱子最大容积）
		element[i].v = value;
	}

	//排序（选择排序）
	Sort(element, n);

	//装箱
	Boxs *hbox=InBox(element, n);

	//输出
	Print(hbox);
}
