/*----------------------------------------------*/
/*      Project Name : Calculaor                */
/*      Code Author Chinese Name : Wang jing    */
/*      Code Author English Name : Eazey        */
/*      Code Tpye : C                           */
/*      Date : 2016-2-18                        */
/*----------------------------------------------*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
typedef int Status;

#define LevelNone 0
#define LevelOne 1
#define LevelTwo 2
#define LevelThree 3
#define LevelFour 4
typedef int OperationLevel;

typedef struct OperandStackNode{
	int operand;
	struct OperandStackNode *next;
}OperandStack,*LinkOperandNode;

typedef struct OperationStackNode{
	char operation;
	struct OperationStackNode *next;
}OperationStack,*LinkOperationNode;

typedef struct Calculator{
	LinkOperationNode OperationTop;
	LinkOperandNode OperandTop;
	int result;
}Calculator;

void InitCalculator(Calculator *C){
	C = (Calculator *)malloc(sizeof(Calculator));
	C->OperandTop = NULL;
	C->OperationTop = NULL;
	printf("Init a new Calculator Successed!!!");
	printf(" -------- InitCalculator();\n");
}

Status PushOperand(Calculator *C, int _operand){
	LinkOperandNode n = (LinkOperandNode)malloc(sizeof(OperandStack));
	if(n == NULL){
		printf("Warning! The Memory is full!");
		printf(" -------- PushOperand();\n");
		return ERROR;
	}
	n->operand = _operand;
	n->next = C->OperandTop;
	C->OperandTop = n;
	printf("Push Successed!!!");
	printf(" -------- PushOperand();\n");
	return OK;
}

Status PushOperation(Calculator *C, char _operation){
	LinkOperationNode n = (LinkOperationNode)malloc(sizeof(OperationStack));
	if(n == NULL){
		printf("Warning! The Memory is full!");
		printf(" -------- PushOperation();\n");
		return ERROR;
	}
	n->operation = _operation;
	n->next = C->OperationTop;
	C->OperationTop = n;
	printf("Push Successed!!!");
	printf(" -------- PushOperation();\n");
	return OK;
}

Status PopOperand(Calculator *C, int *_operand){
	if(C->OperandTop == NULL){
		printf("Warning! The stack is null!");
		printf(" -------- PopOerand();\n");
		return ERROR;
	}
	*_operand = C->OperandTop->operand;
	LinkOperandNode p;
	p = C->OperandTop;
	C->OperandTop = C->OperandTop->next;
	free(p);
	printf("Pop Successed!!!");
	printf(" -------- PopOerand();\n");
	return OK;
}

Status PopOperation(Calculator *C){
	if(C->OperationTop == NULL){
		printf("Warning! The stack is null!");
		printf(" -------- PopOperation();\n");
		return ERROR;
	}
	LinkOperationNode p;
	p = C->OperationTop;
	C->OperationTop = C->OperationTop->next;
	free(p);
	printf("Pop Successed!!!");
	printf(" -------- PopOperation();\n");
	return OK;
}

void ClearOperandStack(Calculator *C){
	if(C->OperandTop == NULL){
		printf("Advise, the stack is already null.");
		printf(" -------- ClearOperandStack();\n");
		return;
	}
	LinkOperandNode p;
	p = C->OperandTop;
	C->OperandTop = NULL;
	free(p);
	printf("Clear Successed!!!");
	printf(" -------- ClearOperandStack();\n");
}

void ClearOperationStack(Calculator *C){
	if(C->OperationTop == NULL){
		printf("Advise, the stack is already null.");
		printf(" -------- ClearOperationStack();\n");
		return;
	}
	LinkOperationNode p;
	p = C->OperationTop;
	C->OperationTop = NULL;
	free(p);
	printf("Clear Successed!!!");
	printf(" -------- ClearOperationStack();\n");
}

Status OperationJudgment(char c){
	switch (c){
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
	case '(':
	case ')':
	case '=':
		return TRUE;
	default:
		return FALSE;
	}
}

Status OperandJudgment(char c){
	switch (c){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return TRUE;
	default:
		return FALSE;
	}
}

OperationLevel OperationLevelJudgment(char op){
	switch (op){
	case '+':return LevelOne;
	case '-':return LevelOne;
	case '*':return LevelTwo;
	case '/':return LevelTwo;
	case '^':return LevelThree;
	case '(':return LevelFour;
	case ')':return LevelFour;
	default:
		printf("Warning! The operation not exit!");
		printf(" -------- OPerationLevelJudgment();\n");
		return LevelNone;
	}
}

void OnceCalculateResult(Calculator *C){	
	int numberA;
	int numberB;
	int result;
	char op = C->OperationTop->operation;
	PopOperation(C);
	PopOperand(C,&numberA);
	PopOperand(C,&numberB);
	switch (op){
	case '+':
		result = numberA + numberB;
	case '-':
		result = numberB - numberA;
	case '*':
		result = numberA * numberB;
	case '/':
		if(numberA == 0){
			printf("Warning! Find out zero be for a divisor!");
			printf(" -------- OnceCalculatorResult();\n");
			exit(ERROR);
		}
		result = numberB / numberA;
	case '^':
		if(numberA == 0){
			result = 1;
		}
		result = numberB;
		for(int i = numberA; i > 1; i--){
			result *= numberB;
		}
	}
	PushOperand(C,result);
}

void PushOperationStackJudgment(Calculator *C, char newOp){
	if(newOp == '='){
		while(C->OperationTop != NULL){
			printf("Once Calculating...");	
			printf(" --------- In final calculate.\n");
			OnceCalculateResult(C);			
		}
		printf("OK. We successed gain the result.\n");
		PopOperand(C,&(C->result));
		return;
	}

	if(C->OperationTop == NULL || newOp == '('){
		PushOperation(C,newOp);
		return;
	}

	char oldOp = C->OperationTop->operation;
	int oldOpLevel = OperationLevelJudgment(oldOp);
	int newOpLevel = OperationLevelJudgment(newOp);
	if(oldOpLevel == 0 || newOpLevel == 0){
		printf("Warning! Find out a unbeknown operation!");
		printf(" --------- PushOperationStackJudgment();\n");
		exit(ERROR);
	}
	if(newOpLevel <= oldOpLevel){
		printf("Once Calculating...");	
		printf(" --------- In new operation's level <= old operation's level calculate.\n");
		OnceCalculateResult(C);
		PushOperationStackJudgment(C,newOp);
	}else if(newOp == ')'){
		while(C->OperationTop->operation != '('){
			printf("Once Calculating...");	
			printf(" --------- In meeting ')' calculate.\n");
			OnceCalculateResult(C);
		}
		printf("OK. The '(' has met ')'.\n");
		PopOperation(C);
	}else{
		PushOperation(C,newOp);
	}
}


int main(){
	Calculator *C;
	InitCalculator(C);

	// to be continue...

	return 0;
}
