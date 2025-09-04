#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode
{
    void *data;
    struct ListNode *next;
} ListNode;

typedef struct
{
    ListNode *head;
    ListNode *tail;
    size_t data_size;
    size_t length;
} List;

typedef int (*CompareFunc)(const void *, const void *);

void list_init(List *list, size_t data_size)
{
    list->head = NULL;
    list->tail = NULL;
    list->data_size = data_size;
    list->length = 0;
}

void list_append(List *list, const void *data)
{
    ListNode *node = malloc(sizeof(ListNode));
    node->data = malloc(list->data_size);

    memcpy(node->data, data, list->data_size);

    node->next = NULL;

    if (list->tail == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }

    list->length++;
}

void *list_get(const List *list, size_t index)
{
    if (index >= list->length)
        return NULL;

    ListNode *current = list->head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current->data;
}

size_t list_find(const List *list, const void *value, CompareFunc compare)
{
    ListNode *current = list->head;

    for (size_t i = 0; i < list->length; i++)
    {
        if (compare(current->data, value) == 0)
        {
            return i;
        }
        current = current->next;
    }

    return -1;
}

void list_free(List *list)
{
    ListNode *current = list->head;

    while (current != NULL)
    {
        ListNode *next = current->next;
        free(current->data);
        free(current);
        current = next;

        if (current == NULL && next != NULL)
        {
            break;
        }

        if (current == next && next != NULL)
        {
            break;
        }

        if (next != NULL && next == next->next)
        {
            break;
        }
    }
}

typedef struct
{
    int id;
    char name[50];
} Person;

typedef struct
{
    double x, y;
} Point;

int compare_person(const void *a, const void *b)
{
    const Person *pa = a;
    const Person *pb = b;

    if (pa->id < pb->id)
        return -1;
    else if (pa->id > pb->id)
        return 1;
    else
        return 0;
}

int compare_point(const void *a, const void *b)
{
    const Point *pa = a;
    const Point *pb = b;

    double dist_a = pa->x * pa->x + pa->y * pa->y;
    double dist_b = pb->x * pb->x + pb->y * pb->y;

    if (dist_a < dist_b)
        return -1;
    else if (dist_a > dist_b)
        return 1;
    else
        return 0;
}

int main()
{
    List person_list;
    list_init(&person_list, sizeof(Person));

    Person p1 = {.id = 101, .name = "Alice"};
    Person p2 = {.id = 102, .name = "Bob"};

    list_append(&person_list, &p1);
    list_append(&person_list, &p2);

    printf("Person count:%zu\n", person_list.length);

    for (size_t i = 0; i < person_list.length; i++)
    {
        Person *p = (Person *)list_get(&person_list, i);
        printf("ID:%d,Name:%s\n", p->id, p->name);
    }

    Person search_key = {.id = 102};

    size_t found_index = list_find(&person_list, &search_key, &compare_person);

    if (found_index != -1)
    {
        printf("Found at index: %zd\n", found_index);
    }

    list_free(&person_list);

    List pointList;
    list_init(&pointList, sizeof(Point));

    Point pt1 = {.x = 1.5, .y = 2.5}, pt2 = {.x = 3.14, .y = -5.7};

    list_append(&pointList, &pt1);
    list_append(&pointList, &pt2);

    for (size_t i = 0; i < pointList.length; i++)
    {
        Point *p = (Point *)list_get(&pointList, i);
        printf("Point %zu: %.2f, %.2f\n", i, p->x, p->y);
    }

    Point search_point = {.x = 3.14, .y = -5.7};

    size_t found_point = list_find(&pointList, &search_point, &compare_point);

    if (found_point != -1)
    {
        printf("Found at point index: %zd\n", found_point);
    }

    list_free(&pointList);

    return EXIT_SUCCESS;
}