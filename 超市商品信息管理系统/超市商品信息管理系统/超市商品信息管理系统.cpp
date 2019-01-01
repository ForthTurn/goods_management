#include "pch.h"

#define MAX 100

int CurrentCnt = 0;

#define MAX_NAME_LEN 30
#define MAX_PRICE_LEN 30

typedef struct node
{
	int goods_id;
	char goods_name[MAX_NAME_LEN + 1];
	int goods_price;
	double goods_discount;
	int goods_amount;
	int goods_remain;
	struct node *next;
} GoodsList;

void info_init(GoodsList **); //read the goodsinfo and creat a linkedlist

void print_all(GoodsList *); //print all info in the linkedlist

void Destory(GoodsList **); //free the memory which used by the linkedlist

void Delete(GoodsList **); //delete the file and free the memory

void info_change(GoodsList *); //change the information of a node which inputed by user

void Print_Goodinfo(GoodsList *); //print a node

void search(GoodsList *); //search information of a node

void info_insert(GoodsList **); //insert a node

void Del_one(GoodsList **); //delete one node

void save(GoodsList *); //save the linkedlist to disk

void sort(GoodsList **); //sort the linkedlist

void exchange_node(GoodsList *, GoodsList *); //exchange two node without its pointer

int main(void)
{
	char cmd, choose;
	GoodsList *lib = NULL;
	info_init(&lib);
	while (1)
	{
		printf("超市商品管理系统\n");
		printf("********************************************\n");
		printf("1.显示所有商品的信息:\n");
		printf("2.修改某个商品的信息:\n");
		printf("3.插入某个商品的信息:\n");
		printf("4.删除某个商品的信息:\n");
		printf("5.查找某个商品的信息:\n");
		printf("6.商品存盘并退出系统:\n");
		printf("7.对商品价格进行排序:\n");
		printf("8.（慎用）删除所有内容:\n");
		printf("其他，不存盘退出系统:\n");
		printf("********************************************\n");
		printf("输入您的选择: ");
		scanf_s("%c", &cmd, 1);
		getchar();
		switch (cmd)
		{
		case '1':
			print_all(lib);
			break;
		case '2':
			info_change(lib);
			break;
		case '3':
			info_insert(&lib);
			break;
		case '4':
			Del_one(&lib);
			break;
		case '5':
			search(lib);
			break;
		case '6':
			save(lib);
			Destory(&lib);
			printf("存盘完成，按任意键退出...\n");
			system("pause >nul");
			return 0;
			break;
		case '7':
			sort(&lib);
			break;
		case '8':
			Delete(&lib);
			break;
		default:
			while (1)
			{
				printf("商品链表未保存，修改内容将会全部丢失，是否退出？(Y/N)\n");
				scanf_s("%c", &choose, 1);
				getchar();
				if (choose == 'Y' || choose == 'y')
				{
					Destory(&lib);
					return 0;
				}
				else if (choose == 'N' || choose == 'n')
					break;
				else
				{
					printf("输入错误，请重新输入(Y/N):\n");
				}
			}
			break;
		}
		system("pause");
		system("CLS");
	}
}

void info_init(GoodsList **first)
{
	FILE *fp = NULL;
	int num = 0, flag = 0;
	GoodsList cache, *new_node, *cur = NULL;
	fopen_s(&fp, "goodsinfo.txt", "r");
	if (fp == NULL)
	{
		printf("商品信息文件不存在！链表为空！将为您新建一个。\n");
		fopen_s(&fp, "goodsinfo.txt", "w");
		fclose(fp);
		*first = NULL;
		return;
	}
	else
	{
		while (
			fscanf_s(fp, "%d%s%d%lf%d%d", &cache.goods_id, &cache.goods_name, sizeof(cache.goods_name), &cache.goods_price, &cache.goods_discount, &cache.goods_amount, &cache.goods_remain) != EOF)
		{
			new_node = (GoodsList *)malloc(sizeof(GoodsList));
			if (new_node == NULL)
			{
				printf("系统内存空间不足！无法创建链表！\n");
				printf("请留出足够内存后启动程序\n");
				system("pause");
				exit(1);
			}
			*new_node = cache;
			new_node->next = NULL;
			if (flag == 0)
			{
				*first = new_node;
				flag = 1;
				cur = new_node;
			}
			else
			{
				cur->next = new_node;
				cur = cur->next;
			}
			num++;
		}
	}
	CurrentCnt = num;
	printf("商品的链表文件已建立，有%d个商品记录\n", num);
	fclose(fp);
}

void print_all(GoodsList *first)
{
	GoodsList *cur;
	for (
		cur = first;
		cur != NULL;
		cur = cur->next)
	{
		printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("ID:%-8d名称:%s\t价格:%-8d折扣:%-8g数量:%-8d剩余:%-d\n",
			cur->goods_id, cur->goods_name, cur->goods_price, cur->goods_discount, cur->goods_amount, cur->goods_remain);
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	}
}

void Destory(GoodsList **first)
{
	GoodsList *pre, *cur;
	for (
		pre = NULL, cur = *first;
		cur != NULL;
		pre = cur, cur = cur->next)
	{
		if (pre != NULL)
		{
			free(pre);
		}
	}
	if (pre != NULL)
	{
		free(pre);
	}
	*first = NULL;
	CurrentCnt = 0;
}

void Delete(GoodsList **first)
{
	char choose;
	FILE *fp = NULL;
	while (1)
	{
		printf("您即将清空所有数据，此操作将不可逆，是否确定？(Y/N)\n");
		scanf_s("%c", &choose, 1);
		getchar();
		if (choose == 'Y' || choose == 'y')
		{
			Destory(first);
			fopen_s(&fp, "goodsinfo.txt", "w");
			fclose(fp);
			return;
		}
		else if (choose == 'N' || choose == 'n')
		{
			printf("操作取消！\n");
			break;
		}
		else
		{
			printf("输入错误，请重新输入(Y/N):\n");
		}
	}
}

void Print_Goodinfo(GoodsList *cur)
{
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("ID:%-8d名称:%s\t价格:%-8d折扣:%-8g数量:%-8d剩余:%-d\n",
		cur->goods_id, cur->goods_name, cur->goods_price, cur->goods_discount, cur->goods_amount, cur->goods_remain);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void info_change(GoodsList *first)
{
	GoodsList *cur;
	char name[MAX_NAME_LEN + 1];
	printf("请输入需要修改的商品名称: \n");
	scanf_s("%s", name, MAX_NAME_LEN + 1);
	getchar();
	for (
		cur = first;
		cur != NULL && strcmp(cur->goods_name, name) != 0;
		cur = cur->next)
		;
	if (cur == NULL)
	{
		printf("商品信息未找到！\n");
		return;
	}
	else
	{
		Print_Goodinfo(cur);
		printf("请输入新的商品信息： \n");
		printf("商品ID：");
		scanf_s("%d", &cur->goods_id);
		printf("商品名称：");
		scanf_s("%s", &cur->goods_name, MAX_NAME_LEN + 1);
		printf("商品价格：");
		scanf_s("%d", &cur->goods_price);
		printf("商品折扣：");
		scanf_s("%lf", &cur->goods_discount);
		printf("商品数量：");
		scanf_s("%d", &cur->goods_amount);
		printf("商品剩余：");
		scanf_s("%d", &cur->goods_remain);
		getchar();
		printf("修改商品信息成功！修改后信息为：\n");
		Print_Goodinfo(cur);
	}
}

void search(GoodsList *first)
{
	GoodsList *cur;
	char name[MAX_NAME_LEN + 1];
	printf("请输入需要查找的商品名称: \n");
	scanf_s("%s", name, MAX_NAME_LEN + 1);
	getchar();
	for (
		cur = first;
		cur != NULL && strcmp(cur->goods_name, name) != 0;
		cur = cur->next)
		;
	if (cur == NULL)
	{
		printf("商品信息未找到！\n");
		return;
	}
	else
	{
		Print_Goodinfo(cur);
	}
}

void info_insert(GoodsList **first)
{
	GoodsList *pre, *cur, *new_node;
	int cmd, i;
	new_node = (GoodsList *)malloc(sizeof(GoodsList));
	if (new_node == NULL)
	{
		printf("系统内存空间不足！无法创建链表！\n");
		printf("请留出足够内存后启动程序\n");
		system("pause");
		exit(1);
	}
	else
	{
		printf("请输入你要插入的商品信息： \n");
		printf("商品ID：");
		scanf_s("%d", &new_node->goods_id);
		printf("商品名称：");
		scanf_s("%s", &new_node->goods_name, MAX_NAME_LEN + 1);
		printf("商品价格：");
		scanf_s("%d", &new_node->goods_price);
		printf("商品折扣：");
		scanf_s("%lf", &new_node->goods_discount);
		printf("商品数量：");
		scanf_s("%d", &new_node->goods_amount);
		printf("商品剩余：");
		scanf_s("%d", &new_node->goods_remain);
		getchar();

		for (
			cur = *first;
			cur != NULL && cur->goods_id != new_node->goods_id;
			cur = cur->next)
			;
		if (cur == NULL)
		{
			printf("输入数字表明你要插入的位置: \n");
			printf("(0.商品列表尾部\t1.商品列表头部\ti.商品列表中间第i个位置)\n");
			printf("请输入: ");
			scanf_s("%d", &cmd);
			getchar();
			if (cmd == 1)
			{
				new_node->next = *first;
				*first = new_node;
			}
			else if (cmd == 0)
			{
				for (
					pre = NULL, cur = *first;
					cur != NULL;
					pre = cur, cur = cur->next)
					;
				if (pre == NULL)
				{
					new_node->next = NULL;
					*first = new_node;
				}
				else
				{
					new_node->next = NULL;
					pre->next = new_node;
				}
			}
			else
			{
				if (CurrentCnt <= cmd)
					printf("位置大于商品列表总数，将为您插入商品列表尾部\n");
				for (
					pre = NULL, cur = *first, i = 1;
					cur != NULL && i < cmd;
					pre = cur, cur = cur->next, i++)
					;
				if (pre == NULL)
				{
					new_node->next = NULL;
					*first = new_node;
				}
				else
				{
					pre->next = new_node;
					new_node->next = cur;
				}
			}
			CurrentCnt++;
			printf("插入商品信息成功！插入的信息为：\n");
			Print_Goodinfo(new_node);
		}
		else
		{
			printf("待插入的商品ID已存在！\n");
			free(new_node);
		}
	}
}

void Del_one(GoodsList **first)
{
	GoodsList *pre, *cur;
	char name[MAX_NAME_LEN + 1], choose;
	printf("请输入需要删除的商品名称: \n");
	scanf_s("%s", name, MAX_NAME_LEN + 1);
	getchar();
	for (
		pre = NULL, cur = *first;
		cur != NULL && strcmp(cur->goods_name, name) != 0;
		pre = cur, cur = cur->next)
		;
	if (cur == NULL)
	{
		printf("商品信息未找到！\n");
		return;
	}
	else
	{

		printf("请确认您将要删除的商品信息: \n");
		Print_Goodinfo(cur);
		while (1)
		{
			printf("是否确认删除？(Y/N)\n");
			choose = getchar();
			getchar();
			if (choose == 'y' || choose == 'Y')
			{
				if (pre == NULL)
				{
					*first = cur->next;
					free(cur);
				}
				else
				{
					pre->next = cur->next;
					free(cur);
				}
				CurrentCnt--;
				printf("删除成功！\n");
				return;
			}
			else if (choose == 'N' || choose == 'n')
			{
				printf("操作取消\n");
				return;
			}
			else
			{
				printf("输入错误，请重新输入(Y/N):\n");
			}
		}
	}
}

void save(GoodsList *first)
{
	FILE *fp;
	GoodsList *cur;
	fopen_s(&fp, "goodsinfo.txt", "w");
	for (
		cur = first;
		cur != NULL;
		cur = cur->next)
	{
		fprintf(fp, "%-d\t%s\t%-d\t%-g\t%-d\t%-d\n",
			cur->goods_id, cur->goods_name, cur->goods_price, cur->goods_discount, cur->goods_amount, cur->goods_remain);
	}
	fclose(fp);
}

void sort(GoodsList **list)
{
	GoodsList *pre, *cur;
	int i;
	for (i = 1; i < CurrentCnt; i++)
	{
		for (
			pre = NULL, cur = *list;
			cur->next != NULL;
			pre = cur, cur = cur->next)
		{
			if (cur->next == NULL)
				break;
			if (cur->goods_price > (cur->next)->goods_price)
			{
				exchange_node(cur, cur->next);
			}
		}
	}
	printf("排序完成\n");
}

void exchange_node(GoodsList *one, GoodsList *two)
{
	GoodsList cache, *one_next, *two_next;
	cache = *two;
	one_next = one->next;
	two_next = two->next;
	*two = *one;
	two->next = two_next;
	*one = cache;
	one->next = one_next;
}
