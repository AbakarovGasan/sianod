#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include "ttmath/ttmath.h"
using namespace std;

class exc: public exception
{
  public:
  char * body;
  void set (char * it){
      body = it;
  }
  virtual const char* what() const throw()
  {
    return body;
  }
} myexception;

void throw_exception(const char * item)
{
    myexception.set((char * )item);
    throw myexception;
}

template <class item>
class stack{
    public:
    int size = 0;
    item * body = NULL;
    int index = 0;
    stack(){};
    stack(int i){
        resize(i);
    }
    //поменять размер стека
    void resize(int i){
        body = new item[i];
        size = i;
        index = 0;
    }
    //очистить стек
    void clear(){
        body = NULL;
        index = 0;
        size = 0;
    }
    //проверка на пустоту
    bool is_empty(){
        return index == 0;
    }
    //проверка на наполненость
    bool is_full(){
        return index == size;
    }
    //вставить в конец стека
    void push(item a){
        if (is_full())
            throw_exception("stack is full");
        body[index] = a;
        index ++;
    }
    //удалить из конца стека
    item pop(){
        if (is_empty())
            throw_exception("stack is empty");
        index --;
        return body[index];
    }
    //прочитать из конца стека
    item peek(){
        if (is_empty())
            throw_exception("stack is empty");
        return body[index - 1];
    };
};

template <class item>
class deque{
    public:
    int size = 0;
    item * body = NULL;
    item * body_back = NULL;
    int index_begin = 0;
    int index_end = 0;
    int left = 0;
    deque(){};
    deque(int i){
        resize(i);
    }
    //поменять размер стека
    void resize(int i){
        body = new item[i];
        body_back = body;
        body_back += i - 1;
        left = i;
        size = i;
    }
    //проверка на пустоту
    bool is_empty(){
        return left == size;
    }
    //проверка на наполненость
    bool is_full(){
        return left == 0;
    }
    //вставить в конец стека
    void push(item it){
        if (is_full())
        {
            throw_exception("deque is full");
        }
        left --;
        body[index_begin] = it;
        index_begin ++;
        if (index_begin == size){
            index_begin = 0;
        }
    }
    //извлечь из конца стека
    item pop(){
        if (is_empty()){
            throw_exception("deque is empty");
        }
        left ++;
        if(index_begin == 0){
            index_begin = size;
        }
        index_begin --;
        return body[index_begin];
    }
    //прочитать из конца стека
    item peek(){
        return body[index_begin - 1];
    }
    //вставить в начало стека
    void push_back(item it){
        if (is_full())
        {
            throw_exception("deque is full");
        }
        left --;
        body_back[-index_end] = it;
        index_end ++;
        if (index_end == size){
            index_end = 0;
        }
    }
    //удалить из начала стека
    item pop_back(){
        if (is_empty()){
            throw_exception("deque is empty");
        }
        left ++;
        if(index_end == 0){
            index_end = size;
        }
        index_end --;
        return body_back[-index_end];
    }
    //прочитать из начала стека
    item peek_back(){
        return body_back[1 - index_end];
    }
};

template <class item>
void extend(deque<item> &u1){
    deque<item> u2(u1.size * 2);
    while (!u1.is_empty()){
        u2.push(u1.pop_back());
    }
    u1 = u2;
}

template <class item>
void extend(stack<item> &u1){
    item * body = u1.body;
    int index = u1.index;
    int size = u1.size;
    u1.resize(size * 2);
    int i = 0;
    while (i < size){
        u1.push(body[i]);
        i++;
    }
    u1.index = index;
}

template <class item>
void deque_push(deque<item> &u1, item it){
    if (u1.is_full()){
        extend<item>(u1);
    }
    u1.push(it);
}

template <class item>
void deque_push_back(deque<item> &u1, item it){
    if (u1.is_full()){
        extend<item>(u1);
    }
    u1.push_back(it);
}

template <class item>
void stack_push(stack<item> &u1, item it){
    if (u1.is_full()){
        extend<item>(u1);
    }
    u1.push(it);
}

deque<string> task1_read(){
    ifstream input;
    input.open("task1.txt");

    if (!input.is_open()){
        throw_exception("file task1.txt is not found");
    }

    string name;
    deque<string> u1(12);
    cout<<"Начальный порядок\n";
    while (getline(input, name)){
        deque_push(u1, name);
        cout<<name<<endl;
    }
    return u1;
};

stack<string> task8_read(){
    ifstream input;
    input.open("task8.txt");
    if (!input.is_open()){
        throw_exception("file task8.txt is not found");
    }
    string name;
    stack<string> u1(12);
    cout<<"Начальный порядок\n";
    while (getline(input, name)){
        stack_push(u1, name);
        cout<<name<<endl;
    }
    return u1;
};

void task1_finish(deque<string> &u1){
    cout<<"\nПорядок по возрастанию\n";
    while(!u1.is_empty()){
        cout<<u1.pop_back()<<endl;
    }
}

void task1(){
    deque<string> u1 = task1_read();
    deque<string> u2(u1.size);

    string big;
    string tmp;

    //присвоить big элемент из u1
    big = u1.pop();

    loop1:

    // если массив u1 пуст, то добавить элемент big в u2 и завершить
    if (u1.is_empty()){
        u2.push(big);
        task1_finish(u2);
        return;
    }

    //присвоить tmp элемент из u1
    tmp = u1.pop();

    //если tmp > big
    if (tmp > big){
        //добавить big в u2 и присвоить tmp big
        u2.push(big);
        big = tmp;
        goto loop1;
    }
    //если tmp <= big
    else{
        //если u2 пуст
        if (u2.is_empty()){
            u2.push(tmp);
            goto loop1;
        }
        //иначе
        else{
            u1.push(tmp);
            u1.push_back(big);
            big = u2.pop();
            goto loop1;
        }
    }
}

template<class ch>
void deque_bind(deque<ch> &u1, ch * ua, int len){
    u1.body = ua;
    u1.body_back = ua + len - 1;
    u1.size = len;
    u1.left = 0;
    u1.index_end = 0;
    u1.index_begin = 0;
}

template<class ch>
void decode(deque<ch> &u1, ch &i){
    ch u;
    int k = u1.size - u1.left;
    while (k > 0){
        k --;
        u = u1.pop_back();
        u1.push(u);
        if (u == i){
            i = u1.pop_back();
            u1.push(i);
            return;
        }
    }
    return;
}

void task2(){
    ifstream input;
    input.open("task2.txt");
    if (!input.is_open()){
        throw_exception("file task2.txt is not found");
    }
    deque<char> dec;
    string out;
    input>>out;

    cout<<"Последовательность символов для шифровки сообщений: "<<out<<endl;
    char * j = (char *) out.c_str();
    deque_bind<char>(dec, j, out.length());
    char u;
    int i = input.tellg();
    cout<<"Зашифрованное сообщение:\n";
    while (!input.eof()){
        input.read(&u, 1);
        cout<<u;
    }

    input.close();
    input.open("task2.txt");
    input.seekg(i, ios::beg);


    cout<<"Расшифрованное сообщение:\n";
    while (!input.eof()){
        input.read(&u, 1);
        decode<char>(dec, u);
        cout<<u;
    }
    input.close();
}

typedef ttmath::Big<100, 100> num;

template<class s>
void print(stack<s> u1){
    int i = 0;
    int l = u1.index;
    while (i < l){
        cout<<u1.body[i]<<" ";
        i ++;
    }
    cout<<endl;
}

void task3(){
    ifstream input;
    input.open( "task3.txt" );
    stack <num> a(12);
    num temp;
    while (input>>temp){
        stack_push(a, temp);
    }


    cout<<"Cтержень A:"<<endl;
    print<num>(a);
    cout<<endl;

    if (a.size <= 1)
    {
        cout<<"Cтержень С:"<<endl;
        print<num>(a);
        return;
    }

    stack <num> b(a.size);
    stack <num> c(a.size);

    num max;
    while (!a.is_empty())
    {
        temp = a.pop();
        look1:
        if (temp >= max){
            b.push(temp);
            max = temp;
        }
        else
        {
            if (b.is_empty()){
                b.push(temp);
                max = temp;
            }
            else
            {
                max = b.pop();
                a.push(max);
                if (!b.is_empty()){
                    max = b.peek();
                }
                goto look1;
            }
        }
    }
    while (!b.is_empty()){
        temp = b.pop();
        c.push(temp);
    }
    cout<<"Cтержень С:"<<endl;
    print<num>(c);
    input.close();
    return;
}


void task4()
{
    ifstream input;
    input.open("task4.txt");
    if (!input.is_open()){
        throw_exception("file task4.txt not found");
    }
    stack<char> u1(12);
    char i;
    cout<<"Текст\n";
    while (!input.eof()){
        input.read(&i, 1);
        cout<<i;
        stack_push(u1, i);
    }
    cout<<"\n";
    int counter = 0;
    while (!u1.is_empty()){
        i = u1.pop();
        if (i == ')'){
            counter += 1;
        }
        else if (i == '('){
            counter -= 1;
            if (counter < 0) break;
        }
    }
    if (counter != 0){
        cout<<"Баланс скобок не соблюдается\n";
    }
    else{
        cout<<"Баланс скобок не соблюдается\n";
    }
}

void task5()
{
    ifstream input;
    input.open("task5.txt");
    if (!input.is_open()){
        throw_exception("file task5.txt not found");
    }
    stack<char> u1(12);
    char i;
    cout<<"Текст\n";
    while (!input.eof()){
        input.read(&i, 1);
        cout<<i;
        stack_push(u1, i);
    }
    cout<<"\n";
    int counter = 0;
    while (!u1.is_empty()){
        i = u1.pop();
        if (i == ']'){
            counter += 1;
        }
        else if (i == '['){
            counter -= 1;
            if (counter < 0) break;
        }
    }
    if (counter != 0){
        cout<<"Баланс скобок не соблюдается\n";
    }
    else{
        cout<<"Баланс скобок не соблюдается\n";
    }
}

void task6(){
    ifstream input;
    input.open("task6.txt");
    if (!input.is_open()){
        throw_exception("file task6.txt not found");
    }
    char j;
    stack<char> u1(12); // буквы
    stack<char> u2(12); // другие символы
    stack<char> u4(12); // цифры
    cout<<"Teкст\n";
    while (!input.eof()){
        input.read(&j, 1);
        cout<<j;
        if (isdigit(j)){
            stack_push(u4, j);
        }
        else if (isalpha(j)){
            stack_push(u1, j);
        }
        else{
            stack_push(u2, j);
        }
    }
    cout<<"\nВывод\n";
    stack<char> u3(u1.size + u2.size + u4.size);
    while (!u2.is_empty()){
        j = u2.pop();
        u3.push(j);
    }
    while (!u1.is_empty()){
        j = u1.pop();
        u3.push(j);
    }
    while (!u4.is_empty()){
        j = u4.pop();
        u3.push(j);
    }
    while (!u3.is_empty()){
        cout<<(u3.pop());
    }
    input.close();
}

char is_number(string &name){
    int l = name.length();
    int i = 0;
    if (l == 0){
        return 0;
    }
    char stat = 1;
    char u = name.at(i);
    if (u == '-'){
        i +=1;
        stat = -1;
    }
    bool dot = true;
    while (i < l){
        u = name.at(i);
        if (dot){
            if (u == '.'){
                dot = false;
                i++;
                continue;
            }
        }
        if (u>= '0' && u <= '9'){
            i++;
        }
        else{
            return 0;
        }
    }
    return stat;
}

void task7(){
    ifstream input;
    input.open("task7.txt");
    if (!input.is_open()){
        throw_exception("file task7.txt is not found");
    }
    string name;
    char u;
    deque<string> u1(12);
    int cons = 0;
    int pros = 0;
    cout<<"Начальный порядок"<<endl;
    while (input>>name){
        cout<<name<<" ";
        u = is_number(name);
        if (u == -1){
            cons ++;
            deque_push_back(u1, name);
        }
        else if (u == 1){
            pros ++;
            deque_push(u1, name);
        }
    }
    cout<<"\nКонечный порядок\n";
    while (cons > 0){
        u1.push(u1.pop_back());
        cons --;
    }
    while (pros > 0){
        pros --;
        cout<<u1.pop_back()<<" ";
    }
    while (!u1.is_empty()){
        cout<<u1.pop()<<" ";
    }
}

void task8(){
    stack<string> u1 = task8_read();
    cout<<"\nОбратный порядок\n";

    loop2:
    {
        if (u1.is_empty()) return;
        cout<<u1.pop()<<endl;
        goto loop2;
    }
    return;
}

bool and_(bool a, bool b){
    return a & b;
}

bool or_(bool a, bool b){
    return a | b;
}

bool xor_(bool a, bool b){
    return a != b;
}

bool ret_(bool a, bool b){
    return b;
}

bool syntax_error(bool a, bool b){
    throw_exception("invalid syntax: expected operand");
    return false;
}

void task9()
{
    ifstream input;
    input.open("task9.txt");
    if (!input.is_open()) throw_exception("file task9.txt is not found");
    stack<bool> u1(12);
    stack<bool (*)(bool, bool)> u2(12);
 //   int cur = 0;
    char i;
    bool t = true; // выражение, текущее
    bool temp;
    bool r = true; // инверсия (да, нет)
    bool (*f) ( bool, bool );
    f = &ret_;
    cout<<"Форумла\n";
    while(input >> i)
    {
        cout<<i;
        if (isspace(i)) continue;
        if (i == 'N'){
            r = !r;
        }
        else if (i == 'A'){
            f = &and_;
        }
        else if (i == 'X'){
            f = &xor_;
        }
        else if (i == 'O'){
            f = &or_;
        }
        else if (i == 'T'){
            t = f(t, true);
            f = &syntax_error;
        }
        else if (i == 'F'){
            t = f(t, false);
            f = &syntax_error;
        }
        else if (i == '('){
            u1.push(t);
            u2.push(f);
            f = &ret_;
            t = true;
        }
        else if (i == ')'){
            temp = t;
            t = u1.pop();
            f = u2.pop();
            t = f(t, temp);
        }
        else{
            throw_exception("Invalid_syntax");
        }
    };
    cout<<"\nВывод\n";
    if (t){
        cout<<"T\n";
    }
    else{
        cout<<"F\n";
    }
    input.close();
    return;
}

char max(char a, char b){
    if (a > b){
        return a;
    }
    return b;
}

char min(char a, char b){
    if (a > b){
        return b;
    }
    return a;
}

struct Pair{
    char first;
    char second;
};

void task10()
{
    ifstream input;
    input.open("task10.txt");
    if (!input.is_open()){
        throw_exception("file task10.txt is not found");
    }
    stack<Pair> u1(12);
    stack<char> u3(12);
    stack<char (*)(char, char)> u2(12);
    char req = 0;
    Pair pair;
    char i;
    cout<<"Форумла\n";
    char (*f) (char, char);
    // req 3 - ожидается 1-ая формула
    // req 2 - ожидается 2-ая формула
    // req 1 - нейтральное состояние
    // req 0 - можно выводить ответ
    while (input>>i){
        cout<<i;
        if (isspace(i)) continue;
        if (i == ',') continue;
        if ((i >='0')&(i <='9')){
            if (req == 0){
                cout<<"\nВывод\n";
                cout<<i<<endl;
                return;
            }
            else{
                if (req == 3){
                    pair.first = i;
                    req = 2;
                }
                else if(req == 2)
                {
                    pair.second = i;
                    req = 1;
                }
            }
        }
        else if (i == 'M'){
            f = &max;
        }
        else if (i == 'N'){
            f = &min;
        }
        else if (i == '(')
        {
            stack_push<char>(u3, req);
            req = 3;
            stack_push<char (*)(char, char)>(u2, f);
            stack_push<Pair>(u1, pair);
        }
        else if (i == ')')
        {
            if (req != 1)
            {
                throw_exception("Syntax error");
            }
            f=u2.pop();
            i = f(pair.first, pair.second);
            req=u3.pop();

            if (req == 3)
            {
                pair.first = i;
                req = 2;
            }
            else if(req == 2)
            {
                pair.second = i;
                req = 1;
            }
            else if (req == 0){
                cout<<"\nВывод\n";
                cout<<i<<endl;
                return;
            }
        }
        else{
            throw_exception("Invalid_syntax");
        }
    }
    input.close();
}

void task11(){
    char j;
    ifstream input("task11.txt");
    if (!input.is_open()) throw_exception("file task11.txt not found");
    char req = 4;

    stack<char> u1(12);
    stack_push<char>(u1, 0);
    cout<<"Форумла\n";
    //req 4 - ожидается терм
    //req 3 - ожидается оператор + или -
    //req 2 - ожидается формула
    //req 1 - нейтральное состояние
    //req 0 - можно выводить ответ
    while (input>>j)
    {
        cout << j;
        if (isspace(j)) continue;
        if (j == 'x' || j == 'y' || j == 'z'){
            if (req == 4)
            {
          //      pair.first = j;
                req = 3;
            }
            else if (req == 3){
                cout<<"\nФормула записана неправильно, ожидалось + или -\n";
                return;
            }
            else if (req == 2)
            {
          //      pair.second = j;
          label90:
                req = u1.pop();
                if (req == 0)
                {
                    cout<<"\nФормула записана правильно\n";
                    return;
                }
                if (input>>j){
                    cout<<j;
                    if (j == ')')
                    {
                        continue;
                    }
                    else
                    {
                         cout<<"\nФормула записана неправильно, ожидалось )\n";
                         return;
                    }
                }
                else{

                    cout<<"\nФормула записана неправильно, ожидалось )\n";
                    return;
                };
            }
        }
        else{
            if (req == 3){
                if (j == '+' || j == '-'){
                    req = 2;
                    continue;
                }
                else if (j == ')'){
                    req = u1.pop();
                    if (req == 0){
                        cout<<"\nФормула записана неправильно, не ожидалось )\n";
                        return;
                    }
                    if (req == 1){
                            goto label90;
                    }
                }
                else{
                    cout<<"\nФормула записана неправильно, ожидалось + или - или )\n";
                    return;
                }
            }
            else{
                if (j != '('){
                    cout<<"\nФормула записана неправильно, ожидался терм\n";
                    return;
                }
                if (req != 0) req --;
                stack_push(u1, req);
                req = 4;
            }
        }
    }
    if (req == 3){
        req = u1.pop();
        if (req == 0){
            cout<<"\nФормула записана правильно\n";
            return;
        }
        else{
            cout<<"\nФормула записана неправильно, ожидалось + или -\n";
            return;
        }
    }
    if (req == 2){
        cout<<"\nФормула записана неправильно, ожидался терм\n";
        return;
    }
    input.close();
}

int main(){
    cout<<"Задача 1\n";
    task1();
    cout<<"\nЗадача 2\n";
    task2();
    cout<<"\nЗадача 3\n";
    task3();
    cout<<"\nЗадача 4\n";
    task4();
    cout<<"\nЗадача 5\n";
    task5();
    cout<<"\nЗадача 6\n";
    task6();
    cout<<"\nЗадача 7\n";
    task7();
    cout<<"\n\nЗадача 8\n";
    task8();
    cout<<"\nЗадача 9\n";
    task9();
    cout<<"\nЗадача 10\n";
    task10();
    cout<<"\nЗадача 11\n";
    task11();
}
