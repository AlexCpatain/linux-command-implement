#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct LIST{
	_Node *head;
	int size;
}List;


_Node *list_begin(List *list)
{
	if(list != NULL && list->size != 0)
		return list->head->next;
	return NULL;
}
_Node *list_end(List *list)
{
    if(list != NULL && list->size != 0)
        return list->head;
	return NULL;
}

_Node *list_rbegin(List *list)
{
	if(list != NULL && list->size != 0)
		return list->head->prev;
	return NULL;
}
_Node *list_rend(List *list)
{
    if(list != NULL && list->size != 0)
		return list->head;
	return NULL;
}

_Node *list_next(List *list, _Node *node)
{
	if(list == 0 || node == 0)	return 0;
	return node->next;
}

_Node *list_rnext(List *list, _Node *node)
{
	if(list == 0 || node == 0)	return 0;
	return node->prev;
}


int list_size(List *list)
{
	if(list != NULL)
		return list->size;
	return 0;
}
int list_empty(List *list)
{

    return list->head->next == list->head;

}


List *create_list()
{
	List *list = (List *)malloc(sizeof(List));
	list->head = (_Node *)malloc(sizeof(_Node));
	list->head->next = list->head;
	list->head->prev = list->head;
	list->size = 0;
	return list;
}
//don't free memory ,user should free
int delete_list(List **list)
{
    if(*list == 0)
		return 0;
	_Node *head = (*list)->head;
	//while(head->next != head){
	//	_Node *first = head->next;
	//	head->next = first->next;
	//	free(first);
	//}
	free(head);
	free((*list));
	(*list) = 0;
	return SUCCESS;
}

int delete_list_free(List **list)
{
    if((*list) == 0)
		return 0;
	_Node *head = (*list)->head;
	while(head->next != head){
		_Node *first = head->next;
		head->next = first->next;
		free(first);
	}
	free(head);
	free((*list));
	(*list) = 0;
	return SUCCESS;
}

void list_clear(List *list)
{
    if(list == 0)
		return ;
    _Node *head = list->head;
	list->size = 0;
	head->next = head;
	head->prev = head;
}

void list_push_back(List *list, _Node *node)
{
    if(list == 0 || node == 0)
		return ;
	_Node *head = list->head;
	node->next = head;
	node->prev = head->prev;
	head->prev->next = node;
	head->prev = node;
	list->size++;
}

void list_push_front(List *list, _Node *node)
{
    if(list == 0 || node == 0)
		return ;
    _Node *head = list->head;
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
    list->size++;
}

_Node *list_pop_back(List *list)
{
    if(list == NULL || list->size == 0)
		return NULL;
    _Node *back = list->head->prev;
    list_delete(list, back);
    return back;
}

_Node *list_pop_front(List *list)
{
    if(list == NULL || list->size == 0)
		return NULL;
    _Node *front = list->head->next;
    if(list_delete(list, front) == SUCCESS)
        return front;
    else
        return NULL;
}

int list_insert_after(List *list, _Node *index, _Node *node)
{
    if(!list|| !node|| !index)
		return FAILURE;
	node->next = index->next;
	node->prev = index;
	index->next->prev = node;
	index->next = node;
	list->size++;
	return SUCCESS;
}

int list_insert_front(List *list, _Node *index, _Node *node)
{
    if(list_insert_after(list, index->prev, node) == SUCCESS)
        return SUCCESS;
    return FAILURE;
}
int list_delete(List *list, _Node *node)
{
    if(!list || !node)
		return FAILURE;
	_Node *prev = node->prev;
	_Node *next = node->next;
	prev->next = next;
	next->prev = prev;
	list->size--;
	return SUCCESS;
}


_Node *list_search(List *list, int condition(_Node *node, void *argc), void *args)
{
	if(!list || !condition)
		return 0;
	_Node *head = list->head;
	while(head->next != head){
		if(condition(head->next, args)){
			return head->next;
		}
		head->next = head->next->next;
	}
	return 0;
}



void list_merge(List *list1, List *list2, int (*compare)(_Node *p, _Node *q))
{
    if(list1 == NULL || list1->size == 0 ||
       list2 == NULL || list2->size == 0)
        return ;
    list1->size += list_size(list2);

    _Node *first1 = list_begin(list1);
    _Node *last1 = list_end(list1);
    _Node *first2 = list_begin(list2);
    _Node *last2 = list_end(list2);
    while(first1 != last1 && first2 != last2){
        if(compare(first1, first2) >= 0){
            _Node *temp = first2->next;
            list_insert_front(list1, first1, first2);
            first2 = temp;
            first1 = first1->next;
        }
        else{
            first1 = first1->next;
        }
    }

    while(first2 != last2){
        _Node *temp = first2->next;
        list_push_back(list1, first2);
        first2 = temp;
    }
    list_clear(list2);
}

void list_swap(List **list1, List **list2)
{
    List *temp = *list2;
    *list2 = *list1;
    *list1 = temp;
}

void list_sort(List **plist, int (*compare)(_Node *p, _Node *q))
{
    List *list = *plist;
	if(list->size == 0 || list->size == 1)
		return ;
	int index;
	List *carry = create_list();
	List *counter[64];
	for(index=0;index<64;index++)
        counter[index] = create_list();
	int fill = 0;
	while(!list_empty(list)){
        list_push_back(carry, list_pop_front(list));
        int i=0;
        while(i < fill && !list_empty(counter[i])){
            list_merge(counter[i], carry, compare);
            list_swap(&carry, &counter[i]);
            i++;
        }
        list_swap(&counter[i], &carry);
        if(i == fill) ++fill;
	}
	for(index = 1; index<fill; index++)
        list_merge(counter[index], counter[index-1], compare);
	list_swap(plist, &counter[fill-1]);
	for(index=0;index<64;index++)
        delete_list(&counter[index]);
    delete_list(&carry);
}
