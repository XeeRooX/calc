
#include <iostream>
using namespace std;

struct Stack
{
    char value;
    struct Stack* next;
};
void Push(Stack*& Head, char val)
{
    Stack* NewStack = new Stack;
    NewStack->value = val;
    NewStack->next = Head;
    Head = NewStack;
}
char Del(Stack*& Head)
{
    char value;
    Stack* q = Head;
    if (Head == NULL)
    {
        return char(255);
    }
    value = Head->value;
    Head = Head->next;
    delete q;
    return value;
}
struct Stackint
{
    float value;
    struct Stackint* next;
};
void Add(Stackint*& Head, float val)
{
    Stackint* NewStack = new Stackint;
    NewStack->value = val;
    NewStack->next = Head;
    Head = NewStack;
}
float Delete(Stackint*& Head)
{
    float value;
    Stackint* q = Head;
    if (Head == NULL)
    {
        return char(255);
    }
    value = Head->value;
    Head = Head->next;
    delete q;
    return value;
}
struct Node
{
    char value;
    Node* next;
};
struct Queue
{
    Node* Head, * Tail;
};
void InQueue(Queue& Q, int val)
{
    Node* NewNode = new Node;
    NewNode->value = val;
    NewNode->next = NULL;
    if (Q.Tail)
        Q.Tail->next = NewNode;
    Q.Tail = NewNode;
    if (Q.Head == NULL)
    {
        Q.Head = Q.Tail;
    }
}
char DeQueue(Queue& Q)
{
    Node* Head = Q.Head;
    char val;
    if (Head == NULL)
        return'?';
    val = Head->value;
    Q.Head = Head->next;
    if (Q.Head == NULL)
        Q.Tail = NULL;
    delete Head;
    return val;
}
bool CheckBalance(string a)
{
    struct Stack* head = new Stack;
    head->next = NULL;
    for (int i = 0; i < a.length(); i++)
    {
        switch (a[i])
        {
        case '(':
            Push(head, a[i]);
            break;
        case ')':
            if (head->value == '(')
            {
                Del(head);
            }
            else
            {
                return 0;
            }
            break;
        default:
            break;
        }

    }
    if (head->next == NULL)
    {
        delete head;
        return 1;
    }
    else
    {
        delete head;
        return 0;
    }
}
bool prioritet(char a, char b)
{
    if ((a == '/' || a == '*') && (b == '+' || b == '-'))
        return true;
    else
        return false;
}

string postfix(string str)
{
    Queue* queue = new Queue();
    Stack* S = NULL;
    // Шаг1
    for (int a = 0; a < str.length(); a++)
    {

        //cout << S->value;
        if (str[a] != '\0')
        {
            //Шаг2 Считать элемент
            if (str[a] != '9' && str[a] != '8' && str[a] != '7' &&
                str[a] != '6' && str[a] != '5' && str[a] != '4' &&
                str[a] != '3' && str[a] != '2' && str[a] != '1' &&
                str[a] != '0' && str[a] != '+' && str[a] != '-' &&
                str[a] != '*' && str[a] != '/' && str[a] != '(' && str[a] != ')')
            {
                return"ERROR";
            }
            if (str[a] >= '0' && str[a] <= '9') // Шаг 3
            {
                // Шаг 4
                InQueue(*queue, str[a]);
                continue;
            }
            else
            {
                // Шаг 5
                if (str[a] == '+' || str[a] == '-' || str[a] == '*' || str[a] == '/')
                {
                    // Шаг 6
                    if (S == NULL || S->value == '(') {
                        //Шаг 7
                        Push(S, str[a]);
                        continue;

                    }
                    else
                    {
                        // Шаг 8      
                        if (prioritet(str[a], S->value)) {
                            // Шаг 9
                            Push(S, str[a]);
                            //cout << "asdsadsa";
                            continue;
                        }
                        else {
                            // Шаг 10
                            if (S != NULL)
                            {
                                while (S->value != '(' && !prioritet(str[a], S->value)) {
                                    //cout << S->value;
                                    InQueue(*queue, Del(S));
                                    if (S == NULL)
                                    {
                                        break;
                                    }
                                }
                                // Шаг 11
                                Push(S, str[a]);
                                continue;
                            }
                        }

                    }
                }
                else
                {
                    // Шаг 12
                    if (str[a] == '(') {
                        // Шаг 13
                        Push(S, str[a]);
                        continue;
                    }
                    else {
                        // Шаг 14
                        while (S->value != '(')
                        {
                            InQueue(*queue, Del(S));
                        }
                        Del(S);
                        continue;
                    }
                }
            }



        }

       
    }
    //Шаг16 
    while (S != NULL) {
        InQueue(*queue, Del(S));
    }

    string val;
    while (queue->Head != NULL)
        val += DeQueue(*queue);
    return val;
}
float calc(string a)
{
    Stackint* S = NULL;
    for (int i = 0; i < a.length(); i++)
    {
        if (i < a.length())
        {
            if (a[i] >= '0' && a[i] <= '9')
            {
                Add(S, a[i] - '0');
                continue;
            }
            else
            {
                float x = Delete(S);
                float y = Delete(S);
                if (a[i] == '+')
                    Add(S, x + y);
                if (a[i] == '-')
                    Add(S, y - x);
                if (a[i] == '*')
                    Add(S, x * y);
                if (a[i] == '/')
                    if (x != 0)
                    {
                        Add(S, y / x);
                    }
                    else
                    {
                        return INT16_MAX;

                    }

            }
        }
    }

    return Delete(S);
}
string check(string str)
{
    bool ch = 0;
    for (int i = 0; i < str.length() - 1; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            ch = 1;
        }
        if (str[i] >= '0' && str[i] <= '9' && str[i + 1] != '*' && str[i + 1] != '*' && str[i + 1] != '/' && str[i + 1] != '+' && str[i + 1] != '-' && str[i + 1] != ')')

        {

            return "ERROR";
        }
        if (str[0] == '*' || str[0] == '/' || str[0] == '-' || str[0] == '+' || str[str.length() - 1] == '*' || str[str.length() - 1] == '/' || str[str.length() - 1] == '-' || str[str.length() - 1] == '+')
        {

            return "ERROR";
        }
        if ((str[i] == '(' || str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-') && (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == ')'))
        {

            return "ERROR";
        }
        if (str[i] == ')' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
            return "ERROR";
        if (str[i + 1] == '(' && (str[i] >= '0' && str[i] <= '9'))
            return "ERROR";
    }
    if (ch == 0)
        return "ERROR";
    return "SccA";
}
int main()
{
    setlocale(LC_ALL, "Rus");

    string uravn = "  ";
    while (true)
    {
        std::cout << "\n\nВведите уравнение или q для выхода:  \n";
        cin >> uravn;
        if (uravn == "q")
        {
            break;
        }

        if (CheckBalance(uravn) == true)
        {
            //cout << "Баланс скобок правильный!\n";
            string transform = postfix(uravn);
            if (transform != "ERROR")
            {
                if (check(uravn) != "ERROR")
                {
                    cout << "Выражение в постфиксной форме:  " << transform << endl;
                    float otv = calc(transform);
                    if (otv == INT16_MAX)
                    {
                        cout << "На 0 делить нельзя!" << endl;
                    }
                    else
                    {
                        cout << "Ответ:  " << otv << endl;
                    }
                }
                else
                    cout << "Ошибка!!";
            }
            else
            {

                cout << "Выражение записано неправильно!" << endl << endl;
            }
        }
        else
            cout << "Баланс скобок не правильный!\n";
    }
}