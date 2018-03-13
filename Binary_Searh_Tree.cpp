#include <stdio.h>  
#include <stdlib.h>  
#include <assert.h>  

typedef struct TNode *Position;
typedef Position BinTree; /* 二叉树类型 */
struct TNode { /* 树结点定义 */
	int Data; /* 结点数据 */
	BinTree Left;     /* 指向左子树 */
	BinTree Right;    /* 指向右子树 */
};
static Position root;
/**初始化树*/
void create_tree()
{
	root = NULL;
}

Position Find(int x, BinTree BST)
{
	while (BST)
	{
		if (x > BST->Data)
			BST = BST->Right;
		else if (x < BST->Data)
		{
			BST = BST->Left;
		}
		else
		{
			return BST;
		}
		return NULL;
	}
}

Position FindMax(BinTree BST)
{
	if(BST)
		while (BST->Right)
		{
			BST = BST->Right;
		}
	return BST;
}

Position FindMin(BinTree BST)
{
	if (BST)
		while (BST->Left)
		{
			BST = BST->Left;
		}
	return BST;
}



BinTree Insert(BinTree BST, int X)
{
	if (!BST) { /* 若原树为空，生成并返回一个结点的二叉搜索树 */
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
		if (root == NULL) //如果为根节点  
			root = BST;
	}
	else { /* 开始找要插入元素的位置 */
		if (X < BST->Data)
			BST->Left = Insert(BST->Left, X);   /*递归插入左子树*/
		else  if (X > BST->Data)
			BST->Right = Insert(BST->Right, X); /*递归插入右子树*/
												/* else X已经存在，什么都不做 */
	}
	return BST;
}

BinTree Delete(BinTree BST, int X)
{
	Position Tmp;

	if (!BST)
		printf("要删除的元素未找到");
	else {
		if (X < BST->Data)
			BST->Left = Delete(BST->Left, X);   /* 从左子树递归删除 */
		else if (X > BST->Data)
			BST->Right = Delete(BST->Right, X); /* 从右子树递归删除 */
		else { /* BST就是要删除的结点 */
			   /* 如果被删除结点有左右两个子结点 */
			if (BST->Left && BST->Right) {
				/* 从右子树中找最小的元素填充删除结点 */
				Tmp = FindMin(BST->Right);
				BST->Data = Tmp->Data;
				/* 从右子树中删除最小元素 */
				BST->Right = Delete(BST->Right, BST->Data);
			}
			else { /* 被删除结点有一个或无子结点 */
				Tmp = BST;
				if (!BST->Left)       /* 只有右孩子或无子结点 */
					BST = BST->Right;
				else                   /* 只有左孩子 */
					BST = BST->Left;
				free(Tmp);
			}
		}
	}
	return BST;
}

void show_all(Position node)
{
	if (node)
	{
		show_all(node->Left);
		printf("%d ", node->Data);
		show_all(node->Right);
	}
}

int main()
{
	/**初始化*/
	create_tree();

	/**插入*/
	int list[15] = { 8,4,11,2,6,10,13,1,3,5,7,9,15,14,16 };
	int i;
	for (i = 0; i < 15; i++)
		Insert(root, list[i]);

	/**显示全部*/
	show_all(root);

	Delete(root, 10);
	show_all(root);
	system("pause");
	return 0;
}
