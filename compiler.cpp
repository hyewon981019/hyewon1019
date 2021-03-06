#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isDelimiter1(char ch) // 아래에서 세부 분류될 모든 기호들을 다시 Delimiter1, Delimiter2 라는 함수로 정의 (편의성을 위함)
{
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == '{' || ch == '}' || ch == '&' || ch == '|' ||
		ch == '!')
		return (true);
	return (false);
}

bool isDelimiter2(char ch) // <,>,=는 다른 기호와 함께 사용이 가능하기 때문에 따로 분리(<=, >=, ==, != 등 합성하여 사용 가능)
{
	if (ch == '>' || ch == '<' || ch == '=')
		return (true);
	return (false);
}

bool isVariable(char* str) // 변수 타입 정의
{
	if (!strcmp(str, "char") || !strcmp(str, "int") || !strcmp(str, "bool") ||
		!strcmp(str, "float") || !strcmp(str, "void"))
		return (true);
	return (false);
}

bool whatNumber(char* str) //입력된 값이 정수형인지 실수형인지 판별하는 함수
{
	int nlen = strlen(str);

	for (int i = 0; i < nlen; i++)
	{
		if (str[i] == '.') return (true);
	}
	return (false);
}

bool isString(char ch) // 문자열인지 판단하는 함수
{
	if (ch == '\"')
		return (true);
	return (false);
}

bool isBoolean(char* str) //참과 거짓을 판별하는 함수 ****
{
	if (!strcmp(str, "true") || !strcmp(str, "false"))
		return (true);
	return (false);
}

bool isID(char* str) //입력된 값이 identifier인지 판단하는 함수
{
	if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
		str[0] == '3' || str[0] == '4' || str[0] == '5' ||
		str[0] == '6' || str[0] == '7' || str[0] == '8' ||
		str[0] == '9')
		return (false);
	return(true);
}

bool isKeyword(char* str) //입력된 값이 keyword인지 판단하는 함수
{
	if (!strcmp(str, "if") || !strcmp(str, "else if") || !strcmp(str, "else") ||
		!strcmp(str, "for") || !strcmp(str, "while") || !strcmp(str, "return") ||
		!strcmp(str, "break") || !strcmp(str, "printf") || !strcmp(str, "scanf"))
		return (true);
	return (false);
}

bool isBitwise1(char* str) //Bitwise에는 << , >>, &, | 이 있는데, '<<', '>>'는 '<','>'의 합성형이므로 따로 분리
{
	if (!strcmp(str, "<<") || !strcmp(str, ">>"))
		return (true);
	return (false);
}

bool isBitwise2(char ch)
{
	if (ch == '&' || ch == '|')
		return (true);
	return (false);
}

bool isArithmetic(char ch) //입력된 문자가 수학기호인지를 판단하는 함수
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return (true);
	return (false);
}

bool isAssign(char ch) //입력된 문자가 '같음'을 나타내는 기호인지를 판단하는 함수
{
	if (ch == '=')
		return (true);
	return (false);
}

bool isComparison1(char* str) // '비교'를 나타내는 기호 중 '<','>'는 나중에 Bitwise1 함수(<<,>>)를 사용한 후 한 번 더 판단이 들어가야 하므로 Comparion2로 분리
{
	if (!strcmp(str, "!=") || !strcmp(str, ">=") || !strcmp(str, "<=") || !strcmp(str, "=="))
		return (true);
	return (false);
}

bool isComparison2(char ch)
{
	if (ch == '<' || ch == '>')
		return (true);
	return (false);
}

bool isTerminal(char ch) //입력된 값이 문장의 끝을 나타내는 기호인지를 판단하는 함수
{
	if (ch == ';')
		return (true);
	return (false);
}

bool isPair1(char ch) //입력된 값이 소괄호인지를 판단하는 함수
{
	if (ch == '(' || ch == ')')
		return (true);
	return (false);
}

bool isPair2(char ch) //입력된 값이 중괄호인지를 판단하는 함수
{
	if (ch == '{' || ch == '}')
		return (true);
	return (false);
}

bool isSeparating(char ch) //입력된 값이 분리의 기호인지를 판단하는 함수
{
	if (ch == ',')
		return (true);
	return (false);
}

char* subString(char* str, int left, int right) // 일부 문자열을 동적할당으로 받음. \0을 붙이기 위해 문자열 길이에 2를 더함
{
	int i;
	char* subStr = (char*)malloc(
		sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];  // 입력된 문자열을 token을 기준으로 나누어 str배열에 각각 저장
	subStr[right - left + 1] = '\0';
	return (subStr);
}

void scanner(char* str, FILE* test) 
{
	int left = 0, right = 0; //left와 right는 각각 입력된 문자열의 시작과 끝을 의미, 두 값 모두 0으로 초기화
	int len = strlen(str);

	while (right <= len && left <= right) //right가 문자열의 길이보다 적고, left가 right의 값을 초월하기 전까지 while문이 돌아감
	{
		if (isString(str[right]) == true)
		{
			while (true)
			{
				right++;
				if (isString(str[right]) == true)
					break;
			}
			char* substr = subString(str, left, right);
			fprintf(test, "%20s IS LITERAL STRING\n", substr);
			right++;
			left = right;
		}

		if (isDelimiter1(str[right]) == false) // Delimiter를 만날 때까지 증가
			right++;

		if (isDelimiter1(str[right]) == true && left == right) //첫 번째 문자가 Delimiter1에 해당하는 기호일 때
		{
			if (isDelimiter2(str[right + 1]) == true)
			{
				right++;
				char* substr = subString(str, left, right);

				if (isComparison1(substr) == true) // Comparison1(!=, ==, <=, >=)중에 해당되는 것이 있을 경우
					fprintf(test, "%20s IS COMPARISON\n", substr);
				else if (isBitwise1(substr) == true)// Bitwise1(<<, >>)중에 해당되는 것이 있을 경우
					fprintf(test, "%20s IS BITWISE\n", substr);
			}
			else  //그 다음 문자가 Delimiter2에 해당되는 것이 없으면 단일 기호라고 판단
			{
				if (isBitwise2(str[right]) == true) // Bitwise인 경우
					fprintf(test, "%20c IS BITWISE\n", str[right]);
				else if (isArithmetic(str[right]) == true) // Arithmetic인 경우
					fprintf(test, "%20c IS ARITHMETIC\n", str[right]);
				else if (isAssign(str[right]) == true) // Assign인 경우
					fprintf(test, "%20c IS ASSIGN\n", str[right]);
				else if (isComparison2(str[right]) == true) // Comparison인 경우
					fprintf(test, "%20c IS COMPARISON\n", str[right]);
				else if (isTerminal(str[right]) == true) // 종료인 경우
					fprintf(test, "%20c IS TERMINAL\n", str[right]);
				else if (isPair1(str[right]) == true) // 소괄호
					fprintf(test, "%20c IS INDICATING PAIR\n", str[right]);
				else if (isPair2(str[right]) == true) // 다른 괄호
					fprintf(test, "%20c IS DEFINING PAIR\n", str[right]);
				else if (isSeparating(str[right]) == true) // Separating인 경우
					fprintf(test, "%20c IS SEPARATING\n", str[right]);
			}

			right++;
			left = right; //substr로 이전 문자까지 처리했기 때문에 left와 right는 다시 같은 지점에서 카운팅함
		}
		else if (str[right] == '!' && str[right + 1] != '=')
		{
			fprintf(test, "%20c IS ERROR\n", str[right]);
			return;
		}
		else if (isDelimiter1(str[right]) == true && left != right || (right == len && left != right))
		{
			char* subStr = subString(str, left, right - 1);

			if (isVariable(subStr) == true)
				fprintf(test, "%20s IS VARIABLE TYPE\n", subStr);
			else if (isBoolean(subStr) == true)
				fprintf(test, "%20s IS BOOLEAN\n", subStr);
			else if (isKeyword(subStr) == true)
				fprintf(test, "%20s IS KEYWORD\n", subStr);
			else if (isID(subStr) == true)
				fprintf(test, "%20s IS IDENTIFIER\n", subStr);
			else if (isID(subStr) == false) //숫자로 시작할 경우 ID가 되지 못하므로 수라고 판단함
			{
				if (whatNumber(subStr) == true)
					fprintf(test, "%20s IS FLOATING-POINT NUMBER\n", subStr);
				else
					fprintf(test, "%20s IS SIGNED INTEGER\n", subStr);
			}
			left = right;
		}
	}

	return;
}

int main()
{
	// maximum legth of string is 100 here  
	char str[100];
	FILE* input, *output;

	char cmd[100], subcmd[50], fileinput[50], fileoutput[50];
	int i = 0, j = 0, k = 0;

	do
	{
		printf("please enter a command: ");
		gets_s(cmd, sizeof(cmd));
		for (i = 0; i <= 16; i++)
			subcmd[i] = cmd[i];
		subcmd[i] = '\0';
	} while (strcmp(subcmd, "lexical_analyzer "));

	k = strlen(cmd);

	for (i = 17; i < k; i++)
	{
		fileinput[i - 17] = cmd[i];
		fileoutput[i - 17] = cmd[i];
	}
	fileinput[i - 17] = '.', fileinput[i - 16] = 't', fileinput[i - 15] = 'x', fileinput[i - 14] = 't', fileinput[i - 13] = '\0';
	fileoutput[i - 17] = '.', fileoutput[i - 16] = 'o', fileoutput[i - 15] = 'u', fileoutput[i - 14] = 't', fileoutput[i - 13] = '\0';

	fopen_s(&input, fileinput, "r");
	fopen_s(&output, fileoutput, "w");

	fgets(str, sizeof(str), input);

	scanner(str, output); // calling the parse function 

	return (0);
}