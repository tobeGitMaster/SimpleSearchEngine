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

	// ���� ��Ʈ��
	for (i = 0; i < MAX_DOC; i++) {
		fopen_s(&fp, fname[i], "r");
		if (fp == NULL) break;

		numofDoc++; // ���� �� ����
		num = 0; j = 0;

		// ���� �б�
		while (!feof(fp)) {
			fscanf_s(fp, "%s", word, WORD_LEN);
			// ���� �迭�� ����
			strcpy_s(doc[i][j++], WORD_LEN, word);
			doc_strnum[i]++;

			// �ҹ��� ��ȯ
			wordTolower(temp, word);

			// item �� �Է�
			item.num = num++;
			item.key = hash(temp);
			strcpy_s(item.word, WORD_LEN, temp);

			// �ؽ� ���̺� item ����
			chain_insert(hash_table[i], item);

			// ���ε� �ܾ� ����
			indexWord++;
		}

		fclose(fp); // ���� �ݱ�
	}

	// ���� ��� ���
	printf("Total number of documents: %d \n", numofDoc);
	printf("Total number of indexed words: %d \n", indexWord);
	printf("Total number of comparison: %d \n", indexComparison);

	// �˻� �ܾ� �Է�
	printf("\nInput Word : ");
	scanf_s("%s", input, WORD_LEN);

	wordTolower(temp, input); // �˻� �ܾ� �ҹ��� ��ȯ
	chain_search(temp); // �ܾ� �˻�
	bubble_sort(Doclist, numofDoc); // ���� ����
	printdoc(temp); // �˻� ��� ���

	printf("\nTotal number of comparison: %d \n", searchComparison);
}

int hash(char *key)
{
	return key[0] - 'a'; // �ܾ� ù ���ĺ� - 'a'�� �ε��� ���� ��
}

void chain_insert(list_ptr hash_table[], element item) // �ܾ� ����(����)
{
	int i = item.key;
	// ��� ���� �� ���� �߰�
	list_ptr temp = (list_ptr)malloc(sizeof(list));
	temp->item = item;
	temp->link = NULL;

	// �ش� �ؽ� ���̺��� �� ��° ���� �� ����
	if (hash_table[i] != NULL)
		temp->link = hash_table[i];

	hash_table[i] = temp;
}

void chain_search(char *word) // �ܾ� �˻�
{
	int i;
	list_ptr temp;
	int key = hash(word);

	for (i = 0; i < numofDoc; i++) {
		Doclist[i].doc = i; // ���� ��ȣ ����
		Doclist[i].top = -1; // �� ������ top��ġ �ʱ�ȭ
		Doclist[i].strnum = 0; // �ش� ������ ���� �� �ʱ�ȭ
		temp = hash_table[i][key];
		while (temp != NULL) {
			searchComparison++;
			// ���ڰ� ���� ���
			if (strcmp(temp->item.word, word) == 0) {
				Doclist[i].strnum++; // ���� �� ����
				Doclist[i].order[++Doclist[i].top] = temp->item.num;
			}
			temp = temp->link;
		}
	}
}

void wordTolower(char *des, char *origin) // �ܾ� �ҹ��� ��ȯ
{
	int i, j = 0;

	for (i = 0; i < (int)strlen(origin); i++) {
		if ((origin[i] >= 'a' && origin[i] <= 'z') || (origin[i] >= 'A'&&origin[i] <= 'Z')) // ���ĺ��� ���
			des[j++] = tolower(origin[i]); // �ҹ��� ��ȯ �� ����
	}
	des[j] = '\0';
}

void bubble_sort(doclist Doclist[], int n) // ���� ����
{
	int i, j, flag = 1;
	doclist temp;

	for (i = n - 1; flag > 0; i--) {
		flag = 0;
		for (j = 0; j < i; j++) {
			// ������ ���Ե� �ܾ� �� ���� �������� ����
			if (Doclist[j].strnum < Doclist[j + 1].strnum) {
				// swap����
				temp = Doclist[j];
				Doclist[j] = Doclist[j + 1];
				Doclist[j + 1] = temp;
				flag = 1;
			}
		}
	}
}

void printdoc(char *input) // �˻� ��� ���
{
	int i, j, pos;
	int top, doc_num, str_num;
	int count = 0;

	for (i = 0; i < numofDoc; i++) {
		doc_num = Doclist[i].doc; // ���� ��ȣ
		str_num = Doclist[i].strnum; // ���� ��
		top = Doclist[i].top; // top��ġ

		if (top > -1) {
			count++;
			printf("\n<%s> %s: %d \n", fname[doc_num], input, str_num);
			while (top > -1) {
				pos = Doclist[i].order[top];
				// �˻� �ܾ� �� 5��° �ڸ��� �ܾ ������ ��
				if (pos - 5 >= 0)
					printf(". . . ");
				top--;
				// �˻� �ܾ� + �յ� 4�ܾ� ���
				for (j = pos - 4; j <= pos + 4; j++) {
					if (j >= 0 && j <= WORD_NUM)
						printf("%s ", doc[doc_num][j]);
				}
				// �˻� �ܾ� �� 5��° �ڸ��� �ܾ ������ ��
				if (doc_strnum[doc_num] >= pos + 5)
					printf(" . . .");
				puts("");
			}
		}
	}

	// �˻� �ܾ� �������� ���� ���
	if (count == 0)
		printf("\nNo such word! \n");
}