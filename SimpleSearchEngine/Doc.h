#define MAX_DOC 9 // 문서 최대 수
#define WORD_NUM 3000 // 단어 최대 수
#define WORD_LEN 100 // 단어 최대 길이

int doc_strnum[MAX_DOC]; // 문서 단어 수

int numofDoc = 0; // 색인된 문서 수
int indexWord = 0; // 색인된 단어 수
int indexComparison = 0; // 색인 시 비교연산 횟수
int searchComparison = 0; // 검색 시 비교연산 횟수

// 파일 이름 저장
char *fname[] = { "document1.txt", "document2.txt", "document3.txt", "document4.txt",
					"document5.txt", "document6.txt", "document7.txt", "document8.txt", "document9.txt" };

typedef struct _doclist {
	int doc; // 문서 번호
	int strnum; // 단어 수
	int top; // order[]의 원소 참조 변수
	int order[WORD_NUM]; // 단어 위치
} doclist;

doclist Doclist[MAX_DOC]; // 검색 후 문서 및 단어 저장

// 문서별 문자 배열
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