// Tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"BinTree.h"
#include"Huffman.h"
int main()
{
   //Test   Bintree
	/*BinTree *tree;
	int index = 0;
	tree = BinTree::create("AB##CDF###E##",index);
	tree->output();
	cout << "后序遍历为：";
	tree->postOrder();
	delete tree;
	cout << endl;
	tree = BinTree::rebuildByPreIn("abdgcefh", "dgbaechf", 8);
	tree->output();
	delete tree;*/

	//测试创建的Huffman树
	HuffmanTree hTree(4);
	const char *str = "abcd";
	int weight[] = { 7,5,2,4 };
	hTree.create(str, weight);
	hTree.output();

	//测试编码
	char hcode[100];
	hTree.encode("dad", hcode);
	printf("编码结果为：%s\n", hcode);

	//测试解码
	char code[100];
	hTree.decode(hcode, code);
	printf("解码结果为：%s\n", code);
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
