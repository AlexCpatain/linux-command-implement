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

int main(int argc, char *argv[])
{
	//list1
	List list1;
	create_list(&list1, NULL);
	Node *node = (Node *)malloc(sizeof(Node));
	node->str = "d";
	list_push_back(&list1, (_Node *)node);

    Node *node2 = (Node *)malloc(sizeof(Node));
	node2->str = "b";
	list_push_back(&list1, (_Node *)node2);

    Node *node3 = (Node *)malloc(sizeof(Node));
	node3->str = "g";
	list_push_back(&list1, (_Node *)node3);

    Node *temp = (Node *)malloc(sizeof(Node));
	temp->str = "a";
	list_push_back(&list1, (_Node *)temp);

	//list2
	List list2;
	create_list(&list2, NULL);
	Node *node4 = (Node *)malloc(sizeof(Node));
	node4->str = "w";
	list_push_back(&list2, (_Node *)node4);

    Node *node5 = (Node *)malloc(sizeof(Node));
	node5->str = "x";
	list_push_back(&list2, (_Node *)node5);

    Node *node6 = (Node *)malloc(sizeof(Node));
	node6->str = "y";
	list_push_back(&list2, (_Node *)node6);

    Node *temp2 = (Node *)malloc(sizeof(Node));
	temp2->str = "z";
	list_push_back(&list2, (_Node *)temp2);

	//operation
	list_print(&list1);
	list_print(&list2);

    list_sort(&list1, compare);
    list_sort(&list2, compare);

    list_print(&list1);
    list_print(&list2);

	delete_list(&list1);
	delete_list(&list2);

	return 0;
}
