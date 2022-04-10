#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


#define MAX_STACK_SIZE 10//스택의 최대 크기
#define MAX_EXPRESSION_SIZE 20//대기열 구조 정의


typedef enum {  //유형 정의 열거형
	lparen = 0,  
	rparen = 9,  
	times = 7,   
	divide = 6,  
	plus = 5,  
	minus = 4,   
	operand = 1 
} precedence;//계산 기호     우선 순위

char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int postfixStackTop = -1;
int evalStackTop = -1;

int evalResult = 0;

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();//디버깅
void reset();//초기화
void evaluation();//평가하다

int main()
{
	char command;

	do {
      printf("[----- [CHEN YUXIANG]  [2020039089] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
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

void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];
	}
	return x;
}

void evalPush(int x)
{
	evalStack[++evalStackTop] = x;
}

int evalPop()
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}


void getInfix()
{
	printf("Type the expression >>> ");
	scanf_s("%s", infixExp);
}

precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}


void charCat(char* c)
{
	if (postfixExp[19] == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}


void toPostfix()
{
	
	char* exp = infixExp;
	char x; 

	
	while (*exp != '\0')
	{
		if (getPriority(*exp) == operand)
		{
			x = *exp;
			charCat(&x);
		}
		else if (getPriority(*exp) == lparen) {

			postfixPush(*exp);
		}
		else if (getPriority(*exp) == rparen)
		{
			while ((x = postfixPop()) != '(') {
				charCat(&x);
			}
		}
		else
		{
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
			{
				x = postfixPop();
				charCat(&x);
			}
			postfixPush(*exp);
		}
		exp++;
	}

	while (postfixStackTop != -1)
	{
		x = postfixPop();
		charCat(&x);
	}

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);
	char symbol;
	evalStackTop = -1;

	for (i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if (getToken(symbol) == operand)
		{
			evalPush(symbol - '0');
		}
		else
		{
			opr2 = evalPop();
		
			opr1 = evalPop();
			switch (getToken(symbol))//스위치
			{
			case plus: evalPush(opr1 + opr2); break;//케이스 플러스
			case minus: evalPush(opr1 - opr2); break;//대소문자 빼기
			case times: evalPush(opr1 * opr2); break;//케이스 시간
			case divide: evalPush(opr1 / opr2); break;//케이스 구분
			default: break;//기본값  인터럽트
			}
		}
	}
	evalResult = evalPop();
}
