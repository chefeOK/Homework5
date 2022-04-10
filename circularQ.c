#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4//대기열에 허용되는 최대 요소 수

typedef char element;
typedef struct {  //형식 정의 구조체
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;//대기열 유형


QueueType* createQueue();
int freeQueue(QueueType* cQ);
int isEmpty(QueueType* cQ);
int isFull(QueueType* cQ);
void enQueue(QueueType* cQ, element item);
void deQueue(QueueType* cQ, element* item);
void printQ(QueueType* cQ);
void debugQ(QueueType* cQ);
element getElement();


int main(void)
{
	QueueType* cQ = createQueue();
	element data;

	char command;//문자 명령

	do {
		printf("[----- [CHEN YUXIANG]  [2020039089] -----]\n");
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf_s(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}

QueueType* createQueue()
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType* cQ)
{
	if (cQ == NULL) return 1;
	free(cQ);
	return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf_s(" %c", &item);
	return item;
}


int isEmpty(QueueType* cQ) 
{
	if (cQ->front == cQ->rear) {
		printf("Circular Queue is empty!");//순환 대기열이 비어 있습니다.
		return 1;//1을 반환
	}
	else return 0;//그렇지 않으면 0을 반환
}

int isFull(QueueType* cQ)
{
	if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front) {
		printf(" Circular Queue is full!");//순환 대기열이 가득 찼습니다.
		return 1;
	}
	else return 0;
}

void enQueue(QueueType* cQ, element item)
{
	if (isFull(cQ)) return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item;
	}
}

void deQueue(QueueType* cQ, element* item)
{
	if (isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front];
		return;
	}
}


void printQ(QueueType* cQ)
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	printf("Circular Queue : ["); //순환 대기열

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType* cQ)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
