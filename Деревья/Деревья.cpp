#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

char letter = 65;

struct Tree
{
    int data;
    char letter;
    Tree* left;
    Tree* right;
    //unsigned char height;
    int height;
};

struct Arr
{
    char letter;
    int data;
};

int height(Tree* q)
{
    if (q == NULL)
    {
        return 0;
    }
    else
    {
        return q->height;
    }
}

void addNode(Tree** top, int data)//добавь height для коректной работы

{
    Tree* q = new Tree();
    q->data = data;
    if (*top == NULL)
    {
        q->left = NULL;
        q->right = NULL;
        q->height = 1;
        if (letter == 91)
        {
            letter = 97;
        }
        q->letter = letter;
        letter++;
        *top = q;
        return;
    }
    else
    {
        if (data >= (*top)->data)
        {
            addNode(&(*top)->right, data);
            if (height((*top)->right) > height((*top)->left))
            {
                (*top)->height = height((*top)->right) + 1;
            }
            else
            {
                (*top)->height = height((*top)->left) + 1;
            }
        }
        else
        {
            addNode(&(*top)->left, data);
            if (height((*top)->right) > height((*top)->left))
            {
                (*top)->height = height((*top)->right) + 1;
            }
            else
            {
                (*top)->height = height((*top)->left) + 1;
            }
        }
    }
}

void findBadBF(Tree** top, Tree** q)
{
    if ((*top) == NULL)
    {
        return;
    }

    //cout << (*top)->letter << ' ';

    if (height((*top)->right) - height((*top)->left) > 1 || height((*top)->right) - height((*top)->left) < -1)
    {
        (*q) = (*top);
        return;
    }
    findBadBF(&(*top)->left, &(*q));
    findBadBF(&(*top)->right, &(*q));
}

void fixHeight(Tree** top)
{
    if ((*top) == NULL)
    {
        return;
    }

    //cout << (*top)->letter << ' ';

    if (height((*top)->left) > height((*top)->right))
    {
        (*top)->height = height((*top)->left) + 1;
    }
    else
    {
        (*top)->height = height((*top)->right) + 1;
    }

    fixHeight(&(*top)->left);
    fixHeight(&(*top)->right);
}

void printTree(Tree* top, int size, int L, int R)//подумай как реализовать по аналогии с QuickSort
{
    int position = (L + R) / 2;
    for (int i = 0; i < position - 1; i++)
    {
        cout << " ";
    }
    cout << top->letter;
    cout << endl;
    if (top->right != NULL)
    {
        printTree(top->right, (size - 3) / 2, position + 2, R);
        cout << "\033[F";
    }
    if (top->left != NULL)
    {
        printTree(top->left, (size - 3) / 2, L, position - 2);
        cout << "\033[F";
    }
}

Tree* findBeforeBadBF(Tree** top, Tree** top2, int& left)
{
    if ((*top) == (*top2))
    {
        left = -1;
        return *top;
    }
    else if ((*top)->left == (*top2))
    {
        left = 1;
        return *top;
    }
    else if ((*top)->right == (*top2))
    {
        left = 0;
        return *top;
    }
    else if ((*top2)->data > (*top)->data)
    {
        findBeforeBadBF(&(*top)->right, &*top2, left);
    }
    else
    {
        findBeforeBadBF(&(*top)->left, &*top2, left);
    }
}

void small_left_rotation(Tree** beforeBF, Tree** badBF, int left)
{
    Tree* q;
    q = (*badBF)->right;
    (*badBF)->right = (*badBF)->right->left;
    q->left = (*badBF);

    if ((*badBF)->right == NULL && (*badBF)->left == NULL)
    {
        (*badBF)->height = 1;
    }
    else if (height((*badBF)->left) > height((*badBF)->right))
    {
        (*badBF)->height = (*badBF)->left->height + 1;
    }
    else
    {
        (*badBF)->height = (*badBF)->right->height + 1;
    }

    if (height(q->right) > height(q->left))
    {
        q->height = q->right->height + 1;
    }
    else
    {
        q->height = q->left->height + 1;
    }

    if (left == 1)
    {
        (*beforeBF)->left = q;
    }
    else if (left == 0)
    {
        (*beforeBF)->right = q;
    }
    else
    {
        (*beforeBF) = q;
    }
}

void small_right_rotation(Tree** beforeBF, Tree** badBF, int left)
{
    Tree* q;
    q = (*badBF)->left;
    (*badBF)->left = (*badBF)->left->right;
    q->right = (*badBF);

    if ((*badBF)->right == NULL && (*badBF)->left == NULL)
    {
        (*badBF)->height = 1;
    }
    else if (height((*badBF)->left) > height((*badBF)->right))
    {
        (*badBF)->height = (*badBF)->left->height + 1;
    }
    else
    {
        (*badBF)->height = (*badBF)->right->height + 1;
    }

    if (height(q->right) > height(q->left))
    {
        q->height = q->right->height + 1;
    }
    else
    {
        q->height = q->left->height + 1;
    }

    if (left == 1)
    {
        (*beforeBF)->left = q;
    }
    else if (left == 0)
    {
        (*beforeBF)->right = q;
    }
    else
    {
        (*beforeBF) = q;
    }
}

void big_left_rotation(Tree** beforeBF, Tree** BadBF, int left)
{
    Tree* q;
    q = (*BadBF)->right->left;
    (*BadBF)->right->left = q->right;
    Tree* q2;
    q2 = (*BadBF)->right;
    (*BadBF)->right = q->left;
    q->left = (*BadBF);
    q->right = q2;

    if ((*BadBF)->right == NULL && (*BadBF)->left == NULL)
    {
        (*BadBF)->height = 1;
    }
    else if (height((*BadBF)->left) > height((*BadBF)->right))
    {
        (*BadBF)->height = (*BadBF)->left->height + 1;
    }
    else
    {
        (*BadBF)->height = (*BadBF)->right->height + 1;
    }

    if (height(q->right) > height(q->left))
    {
        q->height = q->right->height + 1;
    }
    else
    {
        q->height = q->left->height + 1;
    }
    
    if (left == 1)
    {
        (*beforeBF)->left = q;
    }
    else if (left == 0)
    {
        (*beforeBF)->right = q;
    }
    else
    {
        (*beforeBF) = q;
    }
}

void big_right_rotation(Tree** beforeBF, Tree** BadBF, int left)
{
    Tree* q;
    q = (*BadBF)->left->right;
    (*BadBF)->left->right = q->left;
    Tree* q2;
    q2 = (*BadBF)->left;
    (*BadBF)->left = q->right;
    q->right = (*BadBF);
    q->left = q2;

    if ((*BadBF)->right == NULL && (*BadBF)->left == NULL)
    {
        (*BadBF)->height = 1;
    }
    else if (height((*BadBF)->left) > height((*BadBF)->right))
    {
        (*BadBF)->height = (*BadBF)->left->height + 1;
    }
    else
    {
        (*BadBF)->height = (*BadBF)->right->height + 1;
    }

    if (height(q->right) > height(q->left))
    {
        q->height = q->right->height + 1;
    }
    else
    {
        q->height = q->left->height + 1;
    }

    if (left == 1)
    {
        (*beforeBF)->left = q;
    }
    else if (left == 0)
    {
        (*beforeBF)->right = q;
    }
    else
    {
        (*beforeBF) = q;
    }
}

Tree* findValue(Tree** top, int value)
{
    if ((*top) == NULL)
    {
        return NULL;
    }
    else if ((*top)->data == value)
    {
        return (*top);
    }
    else if ((*top)->data > value)
    {
        findValue(&(*top)->left, value);
    }
    else
    {
        findValue(&(*top)->right, value);
    }
}

void deleteValue(Tree** top, Tree** deleteNode)
{
    Tree* q = (*deleteNode)->left;

    if (q == NULL && (*deleteNode)->right == NULL)
    {
        int left;
        q = findBeforeBadBF(&*top, &*deleteNode, left);
        if (left == 1)
        {
            delete q->left;
            q->left = NULL;
        }
        else
        {
            delete q->right;
            q->right = NULL;
        }
    }
    else if (q == NULL)
    {
        q = (*deleteNode)->right;
        (*deleteNode)->data = q->data;
        (*deleteNode)->letter = q->letter;
        (*deleteNode)->right = q->right;
        (*deleteNode)->left = q->left;
        delete q;
        q = NULL;
    }
    else if (q->right == NULL)
    {
        (*deleteNode)->data = q->data;
        (*deleteNode)->letter = q->letter;
        (*deleteNode)->left = q->left;
        delete q;
        q = NULL;
    }
    else
    {
        while (q->right->right != NULL)
        {
            q = q->right;
        }
        (*deleteNode)->letter = q->right->letter;
        (*deleteNode)->data = q->right->data;
        delete q->right;
        q->right = NULL;
    }
}

void deleteTree(Tree** top)
{
    Tree* left;
    Tree* right;
    if ((*top) != NULL)
    {
        left = (*top)->left;
        right = (*top)->right;
        delete (*top);
        deleteTree(&left);
        deleteTree(&right);
    }
    else
    {
        return;
    }
}

int getValueInt()
{
    while (true)
    {
        bool badValue = false;
        char arr[256];
        cin >> arr;

        for (int i = 0; arr[i] != '\0'; i++)
        {
            if (i == 0 && arr[i] == 45 && arr[i + 1] <= 57 && arr[i + 1] >= 48)
            {
                continue;
            }
            if (arr[i] > 57 || arr[i] < 48)
            {
                cin.clear();
                cin.ignore(32767, '\n');
                badValue = true;
                cout << "Введенно не ЦЕЛОЕ число или не число вовсе, попробуйте ещё раз" << endl;
                break;
            }
        }
        if (badValue == false)
        {
            return atoi(arr);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    cout << "На какое количество элементов создавать дерево?" << endl;
    int count;
    count = getValueInt();
    Arr* arr = new Arr[count] {};

    cout << "Если хотитите создать дерево самостоятельно то введите 1, иначе дерево создатится само" << endl;
    int own;
    cin >> own;
    cin.ignore(32464, '\n');
    cin.clear();

    if (own == 1)
    {
        for (int i = 0; i < count; i++)
        {
            cout << i << ": ";
            arr[i].data = getValueInt();
            cout << endl;
        }
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            arr[i].data = rand() % 100 - 50;
        }
    }

    Tree* top = NULL;
    addNode(&top, arr[0].data);
    for (int i = 1; i < count; i++)
    {
        addNode(&top, arr[i].data);
    }

    int position = (pow(2, top->height - 1) - 1) * 4 + 1;//Определяем количество символов которое нужно для нижнего уровня дерева
    printTree(top, position + 1, 1, position);//Вывод дерева
    for (int i = 0; i < top->height + 1; i++)
    {
        cout << endl;
    }

    char letter2 = 65;//Вывод массива значений
    arr[0].letter = letter2;
    cout << "[ " << arr[0].letter << " = " << arr[0].data;
    letter2++;
    for (int i = 1; i < count; i++)
    {
        arr[i].letter = letter2;
        cout << " , " << arr[i].letter << " = " << arr[i].data;
        letter2++;
        if (letter2 == 91)
        {
            letter2 = 97;
        }
    }
    cout << " ]" << endl;

    int exit;
    do
    {
        cout << "Введите 1 если хотите добавить элементы в дерево" << endl;
        cout << "Введите 2 если хотите вывести дерево" << endl;
        cout << "Введите 3 если хотите сбалансировать дерево" << endl;
        cout << "Введите 4 если хотите найти элемент в дереве" << endl;
        cout << "Введите 5 если хотите удалить элемент из дерева" << endl;
        cout << "Введите 0 если хотите выйти из прорамы(очистка памяти произойдёт автоматически)" << endl;
        exit = getValueInt();
        if (exit > 5 || exit < 0)
        {
            cout << "Такого пункта нету, попробуйте ещё раз" << endl;
            continue;
        }

        if (exit == 1)
        {
            int n;
            while (true)
            {
                cout << "Введите количество элементов, которое хотите добавить" << endl;
                n = getValueInt();
                if (n < 0)
                {
                    cout << "Слишком мало, попробуйте ещё раз!" << endl;
                    continue;
                }
                break;
            }
            Arr* arr2 = new Arr[count + n];
            for (int i = 0; i < count; i++)
            {
                arr2[i] = arr[i];
            }

            if (arr[count - 1].letter == 90)
            {
                arr2[count].letter = (char)97;
            }
            else
            {
                arr2[count].letter = arr[count - 1].letter + 1;
            }
            cout << arr2[count].letter << ": ";
            arr2[count].data = getValueInt();
            addNode(&top, arr2[count].data);
            for (int i = count + 1; i < count + n; i++)
            {
                arr2[i].letter = arr2[i - 1].letter + 1;
                cout << arr2[i].letter << ": ";
                arr2[i].data = getValueInt();
                addNode(&top, arr2[i].data);
            }

            delete[] arr;
            arr = arr2;
            arr2 = nullptr;
            count += n;
        }
        else if (exit == 2)
        {
            fixHeight(&top);
            position = (pow(2, top->height - 1) - 1) * 4 + 1;//Определяем количество символов которое нужно для нижнего уровня дерева
            printTree(top, position + 1, 1, position);//Вывод дерева
            for (int i = 0; i < top->height + 1; i++)
            {
                cout << endl;
            }

            //letter2 = 65;//Вывод массива значений
            cout << "[ " << arr[0].letter << " = " << arr[0].data;
            //letter2++;
            for (int i = 1; i < count; i++)
            {
                cout << " , " << arr[i].letter << " = " << arr[i].data;
                //letter2++;
                //if (letter2 == 91)
                //{
                //    letter2 = 97;
                //}
            }
            cout << " ]" << endl;
        }
        else if (exit == 3)
        {
            Tree* BadBF = NULL;
            findBadBF(&top, &BadBF);
            if (BadBF == NULL)
            {
                cout << "Дерево сбалансировано!" << endl;
            }
            else
            {
                cout << '\n' << BadBF->letter << endl;
                if (height(BadBF->right) > height(BadBF->left))//левое вращение
                {
                    if (height(BadBF->right->left) > height(BadBF->right->right))//большое левое вращение
                    {
                        Tree* beforeBF;
                        int left = -2;
                        beforeBF = findBeforeBadBF(&top, &BadBF, left);
                        if (beforeBF == BadBF)
                        {
                            big_left_rotation(&beforeBF, &BadBF, left);
                            top = beforeBF;
                        }
                        else
                        {
                            big_left_rotation(&beforeBF, &BadBF, left);
                        }
                    }
                    else//малое левое вращение
                    {
                        Tree* beforeBF;
                        int left = -2;
                        beforeBF = findBeforeBadBF(&top, &BadBF, left);
                        if (beforeBF == BadBF)
                        {
                            small_left_rotation(&beforeBF, &BadBF, left);
                            top = beforeBF;
                        }
                        else
                        {
                            small_left_rotation(&beforeBF, &BadBF, left);
                        }
                        
                        
                    }
                }
                else//правое вращение
                {
                    if (height(BadBF->left) > height(BadBF->right))//правое вращение
                    {
                        if (height(BadBF->left->right) > height(BadBF->left->left))//большое праве вращение
                        {
                            Tree* beforeBF;
                            int left = -2;
                            beforeBF = findBeforeBadBF(&top, &BadBF, left);
                            if (beforeBF == BadBF)
                            {
                                big_right_rotation(&beforeBF, &BadBF, left);
                                top = beforeBF;
                            }
                            else
                            {
                                big_right_rotation(&beforeBF, &BadBF, left);
                            }
                        }
                        else//малое правое вращение
                        {
                            Tree* beforeBF;
                            int left = -2;
                            beforeBF = findBeforeBadBF(&top, &BadBF, left);
                            if (beforeBF == BadBF)
                            {
                                small_right_rotation(&beforeBF, &BadBF, left);
                                top = beforeBF;
                            }
                            else
                            {
                                small_right_rotation(&beforeBF, &BadBF, left);
                            }
                        }
                    }
                }
                fixHeight(&top);
                fixHeight(&top);
            }
        }
        else if (exit == 4)
        {
            cout << "Введите число которое надо найти" << endl;
            int number;
            number = getValueInt();
            Tree* ptr;
            ptr = findValue(&top, number);
            if (ptr == NULL)
            {
                cout << "Такого значения в этом дереве нету" << endl;
            }
            else
            {
                cout << "Буква которая соответствует данному значению: " << ptr->letter << endl;
            }
            ptr = NULL;
        }
        else if (exit == 5)
        {
            cout << "Какое количество элементов хотите удалить?" << endl;
            int count_for_delete;
            while (true)
            {
                count_for_delete = getValueInt();
                if (count_for_delete > count)
                {
                    cout << "Это больше чем в всего элементов в дереве, попробуйте ещё раз!" << endl;
                }
                else if (count_for_delete < 1)
                {
                    cout << "Слишком мало, попробуйте ещё раз!" << endl;
                }
                else
                {
                    break;
                }
            }
            for (; count_for_delete > 0; count_for_delete--)
            {
                cout << "Введие элемент коорый хотите удалить: ";
                int value_for_delete;
                value_for_delete = getValueInt();
                Tree* ptr;
                ptr = findValue(&top, value_for_delete);
                if (ptr == NULL)
                {
                    cout << "Такого элемента нет, попробуете ещё раз!" << endl;
                    count_for_delete++;
                }
                else
                {
                    deleteValue(&top, &ptr);
                    fixHeight(&top);
                }
                Arr* arr2 = new Arr[count];
                for (int i = 0, j = 0; i < count - 1; i++, j++)
                {
                    if (arr[j].data == value_for_delete)
                    {
                        i--;
                        continue;
                    }
                    arr2[i] = arr[j];
                }
                count--;
                delete[] arr;
                arr = arr2;
                arr2 = NULL;
            }
        }

    } while (exit != 0);

    deleteTree(&top);
}
