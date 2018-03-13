#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree; /* AVL树类型 */
struct AVLNode {
	ElementType Data; /* 结点数据 */
	AVLTree Left;     /* 指向左子树 */
	AVLTree Right;    /* 指向右子树 */
	int Height;       /* 树高 */
};
static AVLTree Tree;

int Max(int a, int b)
{
	return a > b ? a : b;
}

int GetHeight(AVLTree A)
{
	int HR, HL, MaxH;
	if (A)
	{
		HL = GetHeight(A->Left);
		HR = GetHeight(A->Right);
		MaxH = (HR > HL) ? HR : HL;
		return (MaxH + 1);
	}
	else return 0;
}

AVLTree SingleLeftRotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B */
  /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */

	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;
	return B;
}

AVLTree SingleRightRotation(AVLTree A)
{
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;
	return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
  /* 将A、B与C做两次单旋，返回新的根结点C */

  /* 将B与C做右单旋，C被返回 */
	A->Left = SingleRightRotation(A->Left);
	/* 将A与C做左单旋，C被返回 */
	return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
	A->Right = SingleLeftRotation(A->Right);
	return SingleRightRotation(A);
}

AVLTree Insert(AVLTree T, ElementType X)
{ /* 将X插入AVL树T中，并且返回调整后的AVL树 */
	if (!T) { /* 若插入空树，则新建包含一个结点的树 */
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	} /* if (插入空树) 结束 */

	else if (X < T->Data) {
		/* 插入T的左子树 */
		T->Left = Insert(T->Left, X);
		/* 如果需要左旋 */
		if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
			if (X < T->Left->Data)
				T = SingleLeftRotation(T);      /* 左单旋 */
			else
				T = DoubleLeftRightRotation(T); /* 左-右双旋 */
	} /* else if (插入左子树) 结束 */

	else if (X > T->Data) {
		/* 插入T的右子树 */
		T->Right = Insert(T->Right, X);
		/* 如果需要右旋 */
		if (GetHeight(T->Left) - GetHeight(T->Right) == -2)
			if (X > T->Right->Data)
				T = SingleRightRotation(T);     /* 右单旋 */
			else
				T = DoubleRightLeftRotation(T); /* 右-左双旋 */
	} /* else if (插入右子树) 结束 */

	  /* else X == T->Data，无须插入 */

	  /* 别忘了更新树高 */
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
	return T;
}


void InorderTraversal(AVLTree BT)
{

	if (BT) {
		InorderTraversal(BT->Left);
		/* 此处假设对BT结点的访问就是打印数据 */
		printf("%d ", BT->Data); /* 假设数据为整型 */
		InorderTraversal(BT->Right);
	}
}

void PreorderTraversal(AVLTree BT)
{
	if (BT) {
		printf("%d ", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}

void PostorderTraversal(AVLTree BT)
{
	if (BT) {
		PostorderTraversal(BT->Left);
		PostorderTraversal(BT->Right);
		printf("%d ", BT->Data);
	}
}


void Create()
{
	Tree = NULL;
}

int main()
{
	int a[8] = { 12,6,8,5,4,7,14,96 };
	int i;
	Create();

	for (i = 0; i <= 7; i++)
	{
		Tree=Insert(Tree, a[i]);
	}

	PreorderTraversal(Tree);
	printf("\n");
	InorderTraversal(Tree);
	printf("\n");
	PostorderTraversal(Tree);
	printf("\n");

	system("pause");
}