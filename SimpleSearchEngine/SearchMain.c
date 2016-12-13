#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Doc.h"
#include "Hash.h"

void main(void)
{
	FILE *fp;
	char word[WORD_LEN], temp[WORD_LEN], input[WORD_LEN];

	element item;
	int i, j;
	int num;

	// 파일 스트림
	for (i = 0; i < MAX_DOC; i++) {
		fopen_s(&fp, fname[i], "r");
		if (fp == NULL) break;

		numofDoc++; // 문서 수 증가
		num = 0; j = 0;

		// 파일 읽기
		while (!feof(fp)) {
			fscanf_s(fp, "%s", word, WORD_LEN);
			// 문자 배열에 복사
			strcpy_s(doc[i][j++], WORD_LEN, word);
			doc_strnum[i]++;

			// 소문자 변환
			wordTolower(temp, word);

			// item 값 입력
			item.num = num++;
			item.key = hash(temp);
			strcpy_s(item.word, WORD_LEN, temp);

			// 해싱 테이블에 item 삽입
			chain_insert(hash_table[i], item);

			// 색인된 단어 증가
			indexWord++;
		}

		fclose(fp); // 파일 닫기
	}

	// 색인 결과 출력
	printf("Total number of documents: %d \n", numofDoc);
	printf("Total number of indexed words: %d \n", indexWord);
	printf("Total number of comparison: %d \n", indexComparison);

	// 검색 단어 입력
	printf("\nInput Word : ");
	scanf_s("%s", input, WORD_LEN);

	wordTolower(temp, input); // 검색 단어 소문자 변환
	chain_search(temp); // 단어 검색
	bubble_sort(Doclist, numofDoc); // 문서 정렬
	printdoc(temp); // 검색 결과 출력

	printf("\nTotal number of comparison: %d \n", searchComparison);
}

int hash(char *key)
{
	return key[0] - 'a'; // 단어 첫 알파벳 - 'a'가 인덱스 값이 됨
}

void chain_insert(list_ptr hash_table[], element item) // 단어 삽입(색인)
{
	int i = item.key;
	// 노드 생성 및 정보 추가
	list_ptr temp = (list_ptr)malloc(sizeof(list));
	temp->item = item;
	temp->link = NULL;

	// 해당 해시 테이블의 두 번째 이후 값 삽입
	if (hash_table[i] != NULL)
		temp->link = hash_table[i];

	hash_table[i] = temp;
}

void chain_search(char *word) // 단어 검색
{
	int i;
	list_ptr temp;
	int key = hash(word);

	for (i = 0; i < numofDoc; i++) {
		Doclist[i].doc = i; // 문서 번호 삽입
		Doclist[i].top = -1; // 각 문서의 top위치 초기화
		Doclist[i].strnum = 0; // 해당 문서의 문자 수 초기화
		temp = hash_table[i][key];
		while (temp != NULL) {
			searchComparison++;
			// 문자가 같을 경우
			if (strcmp(temp->item.word, word) == 0) {
				Doclist[i].strnum++; // 문자 수 증가
				Doclist[i].order[++Doclist[i].top] = temp->item.num;
			}
			temp = temp->link;
		}
	}
}

void wordTolower(char *des, char *origin) // 단어 소문자 변환
{
	int i, j = 0;

	for (i = 0; i < (int)strlen(origin); i++) {
		if ((origin[i] >= 'a' && origin[i] <= 'z') || (origin[i] >= 'A'&&origin[i] <= 'Z')) // 알파벳인 경우
			des[j++] = tolower(origin[i]); // 소문자 변환 후 복사
	}
	des[j] = '\0';
}

void bubble_sort(doclist Doclist[], int n) // 버블 정렬
{
	int i, j, flag = 1;
	doclist temp;

	for (i = n - 1; flag > 0; i--) {
		flag = 0;
		for (j = 0; j < i; j++) {
			// 문서에 포함된 단어 수 기준 내림차순 정렬
			if (Doclist[j].strnum < Doclist[j + 1].strnum) {
				// swap과정
				temp = Doclist[j];
				Doclist[j] = Doclist[j + 1];
				Doclist[j + 1] = temp;
				flag = 1;
			}
		}
	}
}

void printdoc(char *input) // 검색 결과 출력
{
	int i, j, pos;
	int top, doc_num, str_num;
	int count = 0;

	for (i = 0; i < numofDoc; i++) {
		doc_num = Doclist[i].doc; // 문서 번호
		str_num = Doclist[i].strnum; // 문자 수
		top = Doclist[i].top; // top위치

		if (top > -1) {
			count++;
			printf("\n<%s> %s: %d \n", fname[doc_num], input, str_num);
			while (top > -1) {
				pos = Doclist[i].order[top];
				// 검색 단어 앞 5번째 자리에 단어가 존재할 때
				if (pos - 5 >= 0)
					printf(". . . ");
				top--;
				// 검색 단어 + 앞뒤 4단어 출력
				for (j = pos - 4; j <= pos + 4; j++) {
					if (j >= 0 && j <= WORD_NUM)
						printf("%s ", doc[doc_num][j]);
				}
				// 검색 단어 뒤 5번째 자리에 단어가 존재할 때
				if (doc_strnum[doc_num] >= pos + 5)
					printf(" . . .");
				puts("");
			}
		}
	}

	// 검색 단어 존재하지 않을 경우
	if (count == 0)
		printf("\nNo such word! \n");
}