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
	static BinTree * create(const char * str, int & index)	//	���뺬Ҷ�ӽ���ָ���ǵķ�ʽ����������
	{		//�����������������
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
/*	BinTree *create()		//���뺬Ҷ�ӽ���ָ���ǵķ�ʽ����������
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
		memset(screen, ' ', sizeof(screen));		//����ӡ�ĵط��ո�ռλ
		draw(0, 0, NULL);							//��������������
		int height = deep() * 2;
		for (int i = 0; i < height; i++)
		{
			screen[i][40] = '\0';
			printf("%s\n", screen[i]);
		}
	}
	int draw(int startx, int y, BinTree * parent)		//�������� �ڻ��������ƶ�����ͼ��
	{	//startx ��ʾ��ǰ������˵���ʼx����
		int endx = startx; //endx��ʾ��ǰ�������Ҷ˵�x����
		if (lchild)
			endx = lchild->draw(startx, y + 2, this) + 1;//��������
		int centerx = endx;//������������x���ꡣ���Ǹ��ڵ��x����
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
		//�������
		printf("%c", data);
		if (lchild)
			lchild->postOrder();
		if (rchild)
			rchild->postOrder();
	}
	void postOrder()
	{
		//�������
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
		//����r��InOrder�г��ֵ�λ��pos
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