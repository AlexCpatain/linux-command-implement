#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "list.h"


typedef struct {
	struct _NODE *prev;
	struct _NODE *next;
	const char *str;
}Node;

int SearchConditon(_Node *node,void *arg)
{
    char *i = (char*)arg;
	Node *p = (Node *)node;
    if(strcmp(p->str, i) == 0)
    {
        return  SUCCESS;
    }
    return FAILURE;
}

void list_print(List *list)
{
	_Node *head = list_begin(list);
	while(head != list_end(list)){
		printf("%s ", ((Node *)head)->str);
		head = list_next(list, head);
	}
	printf("\n");
}

void list_rprint(List *list)
{
	_Node *head = list_rbegin(list);
	while(head != list_rend(list)){
		printf("%s ", ((Node *)head)->str);
		head = list_rnext(list, head);
	}
	printf("\n");
}

int compare(_Node *p, _Node *q)
{
	return strcmp(  ((Node *)p)->str,
			     ((Node *)q)->str );

}

List *getList1(){
    List *list = create_list();
	Node *node = (Node *)malloc(sizeof(Node));
	node->str = "d";
	list_push_back(list, (_Node *)node);

    Node *node2 = (Node *)malloc(sizeof(Node));
	node2->str = "b";
	list_push_back(list, (_Node *)node2);

    Node *node3 = (Node *)malloc(sizeof(Node));
	node3->str = "g";
	list_push_back(list, (_Node *)node3);

    Node *temp = (Node *)malloc(sizeof(Node));
	temp->str = "a";
	list_push_back(list, (_Node *)temp);
	return list;
}

List *getList2(){
    List *list = create_list();
	Node *node = (Node *)malloc(sizeof(Node));
	node->str = "w";
	list_push_back(list, (_Node *)node);

    Node *node2 = (Node *)malloc(sizeof(Node));
	node2->str = "x";
	list_push_back(list, (_Node *)node2);

    Node *node3 = (Node *)malloc(sizeof(Node));
	node3->str = "y";
	list_push_back(list, (_Node *)node3);

    Node *temp = (Node *)malloc(sizeof(Node));
	temp->str = "z";
	list_push_back(list, (_Node *)temp);
	return list;
}

int main(int argc, char *argv[])
{
	List *list1 = getList1();
	List *list2 = getList2();
	list_print(list1);
    list_print(list2);

    list_sort(&list1, compare);
    list_sort(&list2, compare);
    list_print(list1);
    list_print(list2);


	delete_list_free(list1);
	delete_list_free(list2);
	printf("%s\n", ((Node *)list_begin(list1))->str);
	return 0;
}
