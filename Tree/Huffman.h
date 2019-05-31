#pragma once
#include"string.h"
#include"float.h"
#include"stdio.h"
#include<memory>

struct HuffmanNode
{
	char data;
	float weight;
	char *code;//编码
	int lchild, rchild;
	int parent;//父节点下标，为0 表示根节点

	HuffmanNode()
	{
		lchild = rchild = parent = 0;
		code = NULL;
	}
	~HuffmanNode()
	{
		if (code)
			delete[] code;
	}
	void output()
	{
		printf("%.f\t%d\t%d\t%d\t", weight, lchild, rchild, parent);
		if (code)
		{
			printf("%c\t%s", data, code);
		}
		printf("\n");
	}
	bool isLeaf()//判断是否为叶子结点
	{
		if (lchild == 0 && rchild == 0)
			return true;
		return false;
	}
};

struct HuffmanTree
{
	int n;//编码数量
	HuffmanNode* nodes;
	char table[128];//ASCII索引表
	int biaoji[10];
	HuffmanTree(int n)
	{
		this->n = n;
		nodes = new HuffmanNode[n * 2 + 2];
	}
	~HuffmanTree()
	{
		delete[]nodes;
	}
	void create(const char * charset, int weight[])
	{
		int idx1, idx2;
		for (int i = 0; i < n; i++)
		{
			table[charset[i]] = i + 1;
			nodes[i + 1].data = charset[i];
			nodes[i + 1].weight = weight[i];
		//	cout << nodes[i + 1].data << " " << nodes[i + 1].weight << endl;
		}
		int b = 0;
		for (int i = n+1; i < n*2; i++)
		{
			findMinima12(i, idx1, idx2);
			biaoji[b++] = idx1;
			biaoji[b++] = idx2;
			nodes[idx1].parent = i;
			nodes[idx2].parent = i;
			nodes[i].lchild = idx1;
			nodes[i].rchild = idx2;
			nodes[i].weight = nodes[idx1].weight + nodes[idx2].weight;
		}	

		char code[10] = { 0 };
		fillCode(2 * n - 1,code, 0);
	}
	bool isCunzai(int b)
	{
		for (int i = 0; i < 10; i++)
			if (biaoji[i] == b)
				return true;
		return false;
	}
	void fillCode(int i,  char* code, int len)
	{
		HuffmanNode &node = nodes[i];
		if (node.lchild)
		{
			code[len] = '0';
			fillCode(node.lchild, code, len+1);
		}
		if (node.rchild)
		{
			code[len] = '1';
			fillCode(node.rchild, code, len+1);
		}
		if (node.isLeaf())
		{
			node.code = new char(len);
			for (int i = 0; i < len; i++)
				node.code[i] = code[i];
			node.code[len]='\0';
			len--;
			return;
		}
			

	}
	void findMinima12(int i, int &idx1, int &idx2)
	{
		if (i < 2)
			return;
		int w1 = 100;
		int w2 = 100;
		for (int j = 1; j < i; j++)
		{
			if (nodes[j].weight < w1 && !isCunzai(j))
			{
				idx2 = idx1;
				idx1 = j;
				w2 = w1;
				w1 = nodes[j].weight;
			}
			else if (nodes[j].weight < w2 && !isCunzai(j))
			{
				idx2 = j;
				w2 = nodes[j].weight;
			}
		}
	}
	void output()
	{
		printf("序号\t权重\t左结点\t右结点\t父结点\t字符\t编码\n");
		for (int i = 1; i <= 2 * n - 1; i++)
		{
			printf("%d\t", i);
			nodes[i].output();
		}
	}
	void append(char* c1, char*c2,int &hl)
	{
		int len2 = strlen(c2);
		for (int i = 0; i < len2; i++)
			c1[hl + i] = c2[i];
		hl += len2;
	}
	void encode(const char* src,  char *dst)
	{
		int hl = 0;
		for(int i = 0 ; i < strlen(src) ; i++)
			for (int j = 1; j <= n; j++)
				if (src[i] == nodes[j].data)
				{
					append(dst, nodes[j].code,hl);
					break;
				}
		dst[hl] = '\0';
	}
	void decode(const char* src,  char *dst)
	{
		int hl = 0;
		int j = 0;
		HuffmanNode &node = nodes[0];
		for (int i = 0; i < strlen(src);)
		{
			node = nodes[7];
			j = 0;
			while (1)
			{
				if (node.lchild == 0)
				{
					dst[hl++] = node.data;
					i += j;
					break;
				}
				if (src[i] == '0')
				{
					j++;
					node = nodes[node.lchild];
				}
				if (src[i] == '1')
				{
					j++;
					node = nodes[node.rchild];
				}
			}

		}
		dst[hl] = '\0';
	}
};