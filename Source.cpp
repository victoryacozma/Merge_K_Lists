#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

//#define K 4
//#define N 6
int comp;
int asig;
#include "Profiler.h"
Profiler profiler("interclasare");

typedef struct node {
	int key;
	struct node* next;
}NodeT;

typedef struct list_type
{
	NodeT* pfirst;
	NodeT* plast;
	int len;
}List;

void init_list(List* l)
{
	l->pfirst = NULL;
	l->plast = NULL;
	l->len = 0;
}



NodeT* createNod(int val) {
	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	comp++;

	if (p!=NULL) {
		p->key = val;
		p->next = NULL;
		asig++;
	}
	return p;
}

void insertLast(List* l, int givenKey) {
	NodeT* p = createNod(givenKey);
	comp++;
	if (l->plast == NULL) {
		l->pfirst = p;
		l->plast = p;
		asig = +2;
	}
	else {
		
		l->plast->next = p;
		l->plast = p;
		asig += 2;
	}
	(l->len)++;
}


void pop(List* l)
{
	//TODO: delete first list element
	comp++;
	if (l->pfirst != NULL)
	{
		asig+=2;
		NodeT* r = l->pfirst;
		l->pfirst = l->pfirst->next;
		(l->len)--;
			free(r);

		/*if (*head == NULL)
		{
			printf("stiva e goala");
		}*/
	}
}

void swap(int* a, int* b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;

}


void reconstr_heap(List l[], int n, int i)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int minim;

	minim  = i;
	
	
	if (left < n && l[left].pfirst->key < l[i].pfirst->key)
	{
		comp++;
		minim = left;
	
	}
	
	if (right < n && l[right].pfirst->key < l[minim].pfirst->key)
	{

		comp++;
		minim = right;
	}

	if (minim != i)
	{
		asig += 3;
		List aux;
		aux = l[i];
		l[i] = l[minim];
		l[minim] = aux;
		reconstr_heap(l, n, minim);
	}


}

void minHeap(List l[], int n)
{

	for (int i = n / 2 - 1; i >= 0; i--)
	{

		reconstr_heap(l, n, i);
	}

}


void printList(List l) {
	
	for (NodeT* p = l.pfirst; p != NULL; p = p->next) {
		printf("%d " , p->key);
	}
}
	


void merge_lists(int k, List hTable[] , List* rez) {
	
	minHeap(hTable, k);
	init_list(rez);
	int hSize = k;

	while (hSize >= 1) {


		insertLast(rez, hTable[0].pfirst->key);
		pop(&hTable[0]);

		comp++;
		if (hTable[0].pfirst == NULL) {

			asig++;
			hTable[0] = hTable[hSize - 1];
			hSize--;
		}
		reconstr_heap(hTable, hSize, 0);

	}
}

void variate_n(int k, const char* typek) {
	
	
	for (int n = 100; n <= 10000; n += 100)
	{
		int N = n / k;
		List* hTable = (List*)calloc(k, sizeof(List));
		int hSize = k;
		int a[100000];

		for (int i = 0; i < k; i++)
		{
			init_list(&hTable[i]);
		}

		for (int i = 0; i < k; i++)
		{
			FillRandomArray(a, N, 0, 500000, true, 1);
			for (int j = 0; j < N; j++) {
				insertLast(&hTable[i], a[j]);

			}
		}
		List finala;
		merge_lists(k, hTable, &finala);
		profiler.countOperation("comp", n, comp);
		profiler.countOperation("asig", n, asig);
		profiler.addSeries(typek, "comp", "asig");
	}
}




int main()
{
	/*int n = 20;
	int k = 4;
	int N = n * k;
	
	List* hTable = (List*) calloc(k , sizeof(List));
	int hSize = k;
	int a[10000];

	for (int i = 0; i < k; i++)
	{
		init_list(&hTable[i]);
	}

	for (int i = 0; i < k; i++)
	{
		FillRandomArray(a, n, 0, 500, true, 1);
		for (int j = 0; j < n; j++) {
			insertLast(&hTable[i], a[j]);
		}	
	}
	
	for (int i = 0; i < k; i++) {
		printf("\nLista %d este :", i);
		printList(hTable[i]);
	}

	List finala;
	merge_lists(k, hTable, &finala, "a", "b");

	printf("\n");
	printList(finala);*/

	int k1 = 5, k2 = 10, k3 = 100;

	variate_n(k1, "k1");
	comp = 0; asig = 0;
	variate_n(k2, "k2");
	comp = 0; asig = 0;
	variate_n(k3, "k3");
	comp = 0; asig = 0;
	
	profiler.createGroup("nVariabil", "k1", "k2", "k3");
	

/*	int n = 10000;
	int a[10000];
	comp = 0; 
	asig = 0;
	
	for (int k = 10; k < 500; k += 10) {
		
		List* hTable = (List*)calloc(k, sizeof(List));
		int hSize = k;
		int a[100000];

		for (int i = 0; i < k; i++)
		{
			init_list(&hTable[i]);
		}

		for (int i = 0; i < k; i++)
		{
			FillRandomArray(a, n, 0, 500000, false, 1);
			for (int j = 0; j < n; j++) {
				insertLast(&hTable[i], a[j]);

			}
		}
		List finala;
		merge_lists(k, hTable, &finala);
		profiler.countOperation("comp", n, comp);
		profiler.countOperation("asig", n, asig);

	}
	profiler.addSeries("k_variabil", "comparatii", "asignari");
	*/
	profiler.showReport();

	return 0;
	}
