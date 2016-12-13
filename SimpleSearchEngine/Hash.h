#define TABLE_SIZE 26

typedef struct _element {
	int num; // �� �������� ���ڿ� ��ġ
	char key;
	char word[WORD_LEN];
} element;

typedef struct list *list_ptr;
typedef struct list {
	element item;
	list_ptr link;
} list;

// ������ �ؽ� ���̺�
list_ptr hash_table1[TABLE_SIZE];
list_ptr hash_table2[TABLE_SIZE];
list_ptr hash_table3[TABLE_SIZE];
list_ptr hash_table4[TABLE_SIZE];
list_ptr hash_table5[TABLE_SIZE];
list_ptr hash_table6[TABLE_SIZE];
list_ptr hash_table7[TABLE_SIZE];
list_ptr hash_table8[TABLE_SIZE];
list_ptr hash_table9[TABLE_SIZE];

list_ptr *hash_table[] = { hash_table1, hash_table2, hash_table3, hash_table4, hash_table5, 
							hash_table6, hash_table7, hash_table8, hash_table9 };

int hash(char *key);
void chain_insert(list_ptr hash_table[], element item);
void chain_search(char *word);