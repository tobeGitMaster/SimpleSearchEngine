#define MAX_DOC 9 // ���� �ִ� ��
#define WORD_NUM 3000 // �ܾ� �ִ� ��
#define WORD_LEN 100 // �ܾ� �ִ� ����

int doc_strnum[MAX_DOC]; // ���� �ܾ� ��

int numofDoc = 0; // ���ε� ���� ��
int indexWord = 0; // ���ε� �ܾ� ��
int indexComparison = 0; // ���� �� �񱳿��� Ƚ��
int searchComparison = 0; // �˻� �� �񱳿��� Ƚ��

// ���� �̸� ����
char *fname[] = { "document1.txt", "document2.txt", "document3.txt", "document4.txt",
					"document5.txt", "document6.txt", "document7.txt", "document8.txt", "document9.txt" };

typedef struct _doclist {
	int doc; // ���� ��ȣ
	int strnum; // �ܾ� ��
	int top; // order[]�� ���� ���� ����
	int order[WORD_NUM]; // �ܾ� ��ġ
} doclist;

doclist Doclist[MAX_DOC]; // �˻� �� ���� �� �ܾ� ����

// ������ ���� �迭
char doc1[WORD_NUM][WORD_LEN];
char doc2[WORD_NUM][WORD_LEN];
char doc3[WORD_NUM][WORD_LEN];
char doc4[WORD_NUM][WORD_LEN];
char doc5[WORD_NUM][WORD_LEN];
char doc6[WORD_NUM][WORD_LEN];
char doc7[WORD_NUM][WORD_LEN];
char doc8[WORD_NUM][WORD_LEN];
char doc9[WORD_NUM][WORD_LEN];

char(*doc[])[WORD_LEN] = { doc1, doc2, doc3, doc4, doc5, doc6, doc7, doc8, doc9 };

void wordTolower(char *des, char *origin);
void bubble_sort(doclist Doclist[], int n);
void printdoc(char *input);