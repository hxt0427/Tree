#pragma once
#include<iostream>
using namespace std;
static char screen[40][80];

struct BinTree
{
	char data;
	BinTree *lchild, *rchild;
	BinTree(char d)
	{
		data = d;
		lchild = NULL;
		rchild = NULL;
	}
	~BinTree()
	{
		if (lchild)
			delete lchild;
		if (rchild)
			delete rchild;
	}
	static BinTree * create(const char * str, int & index)	//	输入含叶子结点空指针标记的方式创建二叉树
	{		//先序遍历创建二叉树
		char ch = str[index++];
		if (ch == '#')
			return NULL;
		BinTree * node = new BinTree(ch);
		node ->lchild = create(str, index);
		node ->rchild = create(str, index);
		return node;
	}
	int deep()
	{
		int ldeep = (lchild == NULL) ? 0 : lchild->deep();
		int rdeep = (rchild == NULL) ? 0 : rchild->deep();
		return 1 + (ldeep > rdeep ? ldeep : rdeep);
	}
/*	BinTree *create()		//输入含叶子结点空指针标记的方式创建二叉树
	{
		char ch;
		scanf("%c", &ch);
		if (ch == '#')
			return NULL;
		BinTree * node = new BinTree(ch);
		node->lchild = create();
		node->rchild = create();
		return node;
	}*/
	void output()
	{
		memset(screen, ' ', sizeof(screen));		//不打印的地方空格占位
		draw(0, 0, NULL);							//绘制树到缓存区
		int height = deep() * 2;
		for (int i = 0; i < height; i++)
		{
			screen[i][40] = '\0';
			printf("%s\n", screen[i]);
		}
	}
	int draw(int startx, int y, BinTree * parent)		//利用中序 在缓冲区绘制二叉树图形
	{	//startx 表示当前树最左端的起始x坐标
		int endx = startx; //endx表示当前子树最右端的x坐标
		if (lchild)
			endx = lchild->draw(startx, y + 2, this) + 1;//先左子树
		int centerx = endx;//左子树结束的x坐标。就是根节点的x坐标
		screen[y][endx++] = data;
		if(rchild)
			endx = rchild->draw(endx, y + 2, this) + 1;
		
		if(parent != NULL)
			if (parent->lchild == this)
			{
				for (int x = centerx; x <= endx; x++)
					screen[y - 1][x] = '-';
				screen[y - 1][centerx] = '/';
			}
			else
			{
				for (int x = startx; x <= centerx; x++)
					screen[y - 1][x] = '-';
				screen[y - 1][centerx] = '\\';
			}
		return endx;
	}
	void preOrder()
	{
		//先序遍历
		printf("%c", data);
		if (lchild)
			lchild->postOrder();
		if (rchild)
			rchild->postOrder();
	}
	void postOrder()
	{
		//后序遍历
		if (lchild)
			lchild->postOrder();
		if (rchild)
			rchild->postOrder();
		printf("%c", data);
	}
	static BinTree * rebuildByPreIn(const char * PreOrder,const char *InOrder, int Len)
	{
		if (Len == 0)
			return NULL;
		char r = PreOrder[0];
		BinTree * R = new BinTree(r);
		//查找r在InOrder中出现的位置pos
		int pos = 0;
		while (pos < Len)
		{
			if (InOrder[pos] == r)
				break;
			pos++;
		}
		R->lchild = rebuildByPreIn(PreOrder + 1,InOrder, pos);
		pos++;
		R->rchild = rebuildByPreIn(PreOrder + pos, InOrder + pos, Len - pos);
		return R;
	}
};