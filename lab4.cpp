#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("Ошибка выделения памяти");
            exit(0);
        }

        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;

        if (data > root->data) root->left = r;
        else root->right = r;
        return r;
    }

    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);

    return root;
}

/* level — уровень узла (корень = 0) */
void print_tree(struct Node* r, int l, int level)
{
    if (r == NULL)
        return;

    print_tree(r->right, l + 1, level + 1);
    for (int i = 0; i < l; i++)
        printf(" ");

    printf("%d (%d)\n", r->data, level);
    print_tree(r->left, l + 1, level + 1);
}

struct Node* FindNode(struct Node* r, int data)
{
    if (r == NULL)
        return NULL;

    if (r->data == data)
        return r;

    if (data > r->data)
        return FindNode(r->left, data);
    else
        return FindNode(r->right, data);
}

int CountOccurrences(struct Node* r, int data)
{
    if (r == NULL)
        return 0;

    int count = (r->data == data) ? 1 : 0;
    count += CountOccurrences(r->left, data);
    count += CountOccurrences(r->right, data);
    return count;
}

int FindLevels(struct Node* r, int data, int level, int* first)
{
    if (r == NULL)
        return 0;

    int cnt = 0;

    if (r->data == data)
    {
        if (!*first) printf(", ");
        printf("%d", level);
        *first = 0;
        cnt++;
    }

    cnt += FindLevels(r->left, data, level + 1, first);
    cnt += FindLevels(r->right, data, level + 1, first);

    return cnt;
}

int main()
{
    setlocale(LC_ALL, "");
    int D, start = 1;
    struct Node* found;

    root = NULL;
    printf("-1 - окончание построения дерева\n");
    while (start)
    {
        printf("Введите число: ");
        scanf_s("%d", &D);
        if (D == -1)
        {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else
            root = CreateTree(root, root, D);
    }

    printf("Дерево (значение (уровень)):\n");
    print_tree(root, 0, 0);

    printf("\nВведите значение для поиска: ");
    scanf_s("%d", &D);

    found = FindNode(root, D);
    if (found != NULL)
        printf("Элемент %d найден\n", found->data);
    else
        printf("Элемент %d в дереве не найден\n", D);

    printf("\nВведите значение для подсчёта: ");
    scanf_s("%d", &D);

    int cnt = CountOccurrences(root, D);
    if (cnt == 0)
    {
        printf("Элемент %d в дереве не встречается\n", D);
    }
    else
    {
        printf("Элемент %d встречается %d раз(а)\n", D, cnt);
        printf("Уровни элемента %d: ", D);
        int first = 1;
        FindLevels(root, D, 0, &first);
        printf("\n");
    }

    scanf_s("%d", &D);
    return 0;
}