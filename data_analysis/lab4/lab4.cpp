#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h>
#include "ttmath/ttmath.h"

typedef ttmath::Big<100, 100> num;
using namespace std;

class full_stack: public exception
{
  virtual const char* what() const throw()
  {
    return "stack is full";
  }
} myexfull;

class empty_stack: public exception
{
  virtual const char* what() const throw()
  {
    return "stack is empty";
  }
} myexempty;

class file_open: public exception
{
  virtual const char* what() const throw()
  {
    return "can't open file";
  }
} file;

class syntax_open: public exception
{
  virtual const char* what() const throw()
  {
    return "syntax error";
  }
} syntax;



template <class item>
class stack{
    public:
    int size;
    item * body = NULL;
    int index = 0;
    stack(){}
    stack(int i){
        body = new item[i];
        size = i;
        index = 0;
    }
    void resize(int i){
 //       delete [] body;
        body = new item[i];
        size = i;
        index = 0;
    }
    void push(item it){
        if (is_full())
        {
            throw myexfull;
        }
        body[index] = it;
        index ++;
    }
    void pop(){
        if (is_empty()){
            throw myexempty;
        }
        index --;
    }
    void pop(item &it){
        pop();
        it = body[index];
    }
    bool is_empty(){
        return index == 0;
    }
    bool is_full(){
        return index == size;
    }
};

template <class item>
class deque{
    public:
    int size;
    item * body;
    item * body_back;
    int index_begin = 0;
    int index_end = 0;
    int left;
    deque(){};
    deque(int i){
        body = new item[i];
        body_back = body;
        body_back += i - 1;
        left = i;
        size = i;
    }
    void resize(int i){
        body = new item[i];
        body_back = body;
        body_back += i - 1;
        left = i;
        size = i;
    }
    bool is_empty(){
        return left == size;
    }
    bool is_full(){
        return left == 0;
    }
    void push(item it){
        if (is_full())
        {
            throw myexfull;
        }
        left --;
        body[index_begin] = it;
        index_begin ++;
        if (index_begin == size){
            index_begin = 0;
        }
    }
    void pop(){
        if (is_empty()){
            throw myexempty;
        }
        left ++;
        if(index_begin == 0){
            index_begin = size;
        }
        index_begin --;
    }
    void pop(item & it){
        pop();
        it = body[index_begin];
    }
    void push_back(item it){
        if (is_full())
        {
            throw myexfull;
        }
        left --;
        body_back[-index_end] = it;
        index_end ++;
        if (index_end == size){
            index_end = 0;
        }
    }
    void pop_back(){
        if (is_empty()){
            throw myexempty;
        }
        left ++;
        if(index_end == 0){
            index_end = size;
        }
        index_end --;
    }
    void pop_back(item & it){
        pop_back();
        it = body_back[-index_end];
    }
};

class InputStream: public ifstream{
public:
    int len;
    void init(const char * path){

    this->open(path);
    if (!this->is_open()){
        //cout<<"throw"<<endl;
        throw file;
    }
        this->seekg(0, ios::end);
        len = this->tellg();
        this->seekg(0, ios::beg);
    }
    char read_char(){
    char u;
    read(&u, 1);
    return u;
    }
};


template<class ch>
void deque_bind(deque<ch> &u1, ch * ua, int len){
    u1.body = ua;
    u1.body_back = ua + len - 1;
    u1.size = len;
    u1.left = 0;
    u1.index_end = 0;
    u1.index_begin = 0;
}

deque<string> temp(){
    ifstream input;
    input.open("task1.txt");
    if (!input.is_open()){
        throw file;
    }
    cout<<string("Начальный порядок")<<endl;
    vector <string> ret;
    string out;
    while (getline(input, out)) {
        ret.push_back(out);
    //    cout<<out<<endl;
    }
    deque<string> u1(ret.size());
    for (string i: ret){
        u1.push(i);
        cout<<i<<endl;
    }
    cout<<endl;
    return u1;
    input.close();
}

void print(string * args, int len){
    int i = 0;
    while (i < len){
        cout<<args[i]<<" ";
        i++;
    }
}


void task1(){
    deque<string> u1 = temp();
    deque<string> u2(u1.size);

    string big;
    string tmp;

//    print(u1.body, a6);
//    cout<<"b"<<u1.index_begin<<" e"<<u1.index_end<<endl;

 //   print(u2.body, a6);
 //   cout<<"b"<<u2.index_begin<<" e"<<u2.index_end<<endl;

    u1.pop(big);
 //   u1.body[u1.index_begin] = -1;

    loop1:

//    print(u1.body, a6);
//    cout<<"b"<<u1.index_begin<<" e"<<u1.index_end<<" left "<<u1.left<<endl;

//    print(u2.body, a6);
//    cout<<"b"<<u2.index_begin<<" e"<<u2.index_end<<" left "<<u1.left<<endl;

 //   cout<<"big"<<big<<endl;

//    cout<<endl;
//    cin.get();

    if (u1.is_empty())
    {
        cout <<"Порядок по убыванию"<< endl;
        u2.push(big);
        while (!u2.is_empty()){
            string i;
            u2.pop(i);
 //  /**/         u2.body[u2.index_begin] = -1;
            cout<<i<<endl;
        }
        return;
    }

    u1.pop(tmp);
//    cout<<"next_tmp"<<tmp<<endl;
 //  /**/         u1.body[u1.index_begin] = -1;

    if (tmp > big){
        u2.push(big);
        big = tmp;
        goto loop1;
    }
    else{
        if (u2.is_empty()){
             u2.push(tmp);
             goto loop1;
        }
        else{
            u1.push(tmp);
            u1.push_back(big);
            u2.pop(big);
//            /**/         u2.body[u2.index_begin] = -1;

            goto loop1;
        }
    }
}

ifstream open_input(const char * a);

template<class r>
void stack_push(stack<r> & u1, r temp){
    if (u1.is_full())
        {
            auto f = u1.body;
            int f_len = u1.size;
            int i = 0;
            u1.resize(u1.size * 2);
            while (i < f_len){
                u1.push(f[i]);
                i ++;
            }
            delete [] f;
        };
        u1.push(temp);
}

template<class s>
void print(stack<s> u1){
    int i = 0;
    int l = u1.index;
    while (i < l){
        cout<<u1.body[i]<<" ";
        i ++;
    }
}

template<class ch>
void decode(deque<ch> &u1, ch &i){
    ch u;
    int k = u1.size - u1.left;
    while (k > 0){
        k --;
        u1.pop_back(u);
        u1.push(u);
        if (u == i){
            u1.pop_back(i);
            u1.push(i);
            return;
        }
    }
    return;
}

void task2(){
    InputStream input;
    input.init("task2.txt");
    deque<char> dec;
    string out;
    input>>out;
    cout<<"Последовательность символов для шифровки сообщений: "<<out<<endl;
    char * j = (char *) out.c_str();
    deque_bind<char>(dec, j, out.length());
    char u;
    int pos = input.tellg();
    cout<<"Зашифрованное сообщение:\n";
    int len = input.len - pos;
    while (len > 0){
        len --;
        input.read(&u, 1);
        cout<<u;
    }
    cout<<"Расшифрованное сообщение:\n";
    len = input.len - pos;
    input.seekg(pos, ios::beg);
    while (len > 0){
        len --;
        input.read(&u, 1);
        decode<char>(dec, u);
        cout<<u;
    }
    input.close();
}

void task3(){
    ifstream input = open_input( "task3.txt" );
    stack <num> a(12);

    num temp;
    while (input>>temp){
        stack_push(a, temp);
    }


    cout<<"Cтержень A:"<<endl;
    print<num>(a);
    cout<<endl;

    if (a.size == 0)
    {
        print(a);
    }

    stack <num> b(a.size);
    stack <num> c(a.size);

    num max;
    while (!a.is_empty())
    {
        a.pop(temp);
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
                b.pop(max);
                a.push(max);
                if (!b.is_empty()){
                    max = b.body[b.index - 1];
                }
                goto look1;
            }
        }
    }
    while (!b.is_empty()){
        b.pop(temp);
        c.push(temp);
    }
    cout<<"Cтержень С:"<<endl;
    print<num>(c);
    input.close();
}

void task4()
{
 //   cout<<"here"<<endl;
    ifstream input;
    input.open("task4.txt");
    if (!input.is_open()){
        cout<<"throw"<<endl;
        throw file;
    }
    int l;
    input.seekg(0, ios::end);
    l = input.tellg();
  //  cout<<l<<endl;
    stack<char> u1(l);
    char x;
    char quote = 0;
    input.seekg(0, ios::beg);
    while (l > 0){
        l --;
        input.read(&x, 1);
        if (quote == 0){
            if (x == '"'){
                quote = '"'; continue;
            }
            else if (x=='\''){
                quote = '\''; continue;
            }
            else if (x == '|'){
                quote = '|'; continue;
            }
        }
        else{
            if (x == '"' & x == quote){
                quote = 0;
            }
            else if (x=='\'' & x == quote){
                quote = 0;
            }
            else if (x == '\n' & quote == '|' ){
                quote = 0;
            }
            continue;
        }
        if (x == '('){
        u1.push(x);
        }
        else if (x == ')'){
                if (u1.is_empty()){
                    cout<<"баланс скобок соблюдается"<<endl;
                    return;
                }
        u1.pop(x);
        }
    }


    if (u1.is_empty()){
        cout<<"баланс скобок соблюдается\n";
    }
    else{
        cout<<"баланс скобок не соблюдается\n";
    }
    input.close();
    return;
}

void task5()
{
 //   cout<<"here"<<endl;
    ifstream input;
    input.open("task4.txt");
    if (!input.is_open()){
        cout<<"throw"<<endl;
        throw file;
    }
    int l;
    input.seekg(0, ios::end);
    l = input.tellg();
  //  cout<<l<<endl;
    deque<char> u1(l);
    char x;
    char quote = 0;
    input.seekg(0, ios::beg);
    while (l > 0){
        l --;
        input.read(&x, 1);
        if (quote == 0){
            if (x == '"'){
                quote = '"'; continue;
            }
            else if (x=='\''){
                quote = '\''; continue;
            }
            else if (x == '|'){
                quote = '#'; continue;
            }
        }
        else{
            if (x == '"' & x == quote){
                quote = 0;
            }
            else if (x=='\'' & x == quote){
                quote = 0;
            }
            else if (x == '\n' & quote == '#' ){
                quote = 0;
            }
            continue;
        }
        if (x == '['){
        u1.push(x);
        }
        else if (x == ']'){
                if (u1.is_empty()){
                    cout<<"баланс скобок соблюдается"<<endl;
                    return;
                }
        u1.pop(x);
        }
    }


    if (u1.is_empty()){
        cout<<"баланс скобок соблюдается\n";
    }
    else{
        cout<<"баланс скобок не соблюдается\n";
    }
    input.close();
    return;
}



void task6(){
    InputStream input;
    input.init("task6.txt");
    char j;
    int l = input.len;
    stack<char> u1(l);
    stack<char> u2(l);
    stack<char> u3(l);
    while (l > 0){
        l--;
        j = input.read_char();
        if (isdigit(j)){
            cout<<j;
        }
        else if (isalpha(j)){
            u1.push(j);
        }
        else{
            u2.push(j);
        }
    }
    while (!u2.is_empty()){
        u2.pop(j);
        u3.push(j);
    }
    while (!u1.is_empty()){
        u1.pop(j);
        u3.push(j);
    }
    while (!u3.is_empty()){
        u3.pop(j);
        cout<<(j);
    }
    input.close();
}

char what_number(const string &str){
	int i = 0;
	char ret = 1;
	char j;
	int l = str.length();
	if (l == 0) return 3;
	if (str[i] == '-') {
            i++;
            ret = -1;
	}
	while (i < l) {
        j = str[i];
   //     cout << j <<endl;
        if (j <= '9'){
            if (j >= '0'){
                i++;
                continue;
            }
        }
        return 0;
	}
	return ret;
}

void task7(){
    InputStream input;
    input.init("task7.txt");
    char j;
    int l = input.len;
    deque <string> u1(l);
    string temp;
    int count = 0;
    while ( input>>temp ){
        j = what_number(temp);
     //   cout<<temp<<endl;
      //  cout<<input.tellg()<<endl;
        switch (j){
        case 0:
      //      cout<<"fuck"<<endl;
            continue;
        case -1:
            count ++;
      //      cout<<"zero"<<endl;
            u1.push(temp);
            continue;
        case 1:
            u1.push_back(temp);
            continue;
        }
      //  cin>>temp;

    }
    while (count > 0){
        u1.pop(temp);
        u1.push_back(temp);
        count--;
    }
    while (!u1.is_empty()){
        u1.pop(temp);
        cout<<temp<<" ";
    }
    input.close();

}

bool check_file_is_empty ( ifstream& file){
    return file.peek() == EOF ;
}

void task8(){
  //  cout<<"here"<<endl;
   // return;
    ifstream input;
    string temp;
    string * f;
    int i = 0;
    int f_len = 12;
    stack<string> u1(12);
    input.open("task8.txt");
    while (getline(input, temp))
    {
        if (u1.is_full())
        {
            f = u1.body;
            f_len = u1.size;
            i = 0;
            u1.resize(u1.size * 2);
            while (i < f_len){
                u1.push(f[i]);
                i ++;
            }
            delete [] f;
        };
        u1.push(temp);
    }
    while (!u1.is_empty()){
        u1.pop(temp);
        cout<<temp<<endl;
    }
    input.close();
}

ifstream open_input(const char * i){
    ifstream input;
    input.open(i);
    if (!input.is_open()){
        throw file;
    }
    return input;
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

void task9()
{
    ifstream input = open_input("task9.txt");
    stack<bool> u1(12);
    stack<bool (*)(bool, bool)> u2(12);
    int cur = 0;
    char i;
    bool t = true;
    bool temp;
    bool r = true;
    bool (*f) ( bool, bool );
    f = &ret_;
    bool is_opt_expected = false;
    while(input >> i)
    {

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
        }
        else if (i == 'F'){
            t = f(t, false);
        }
        else if (i == '('){
            u1.push(t);
            u2.push(f);
            f = &ret_;
            t = true;
        }
        else if (i == ')'){
            temp = t;
            u1.pop(t);
            u2.pop(f);
            t = f(t, temp);
        }
    };
    if (t){
        cout<<"T"<<endl;
    }
    else{
        cout<<"F"<<endl;
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
    ifstream input = open_input("task10.txt");
    stack<Pair> u1(12);
    stack<char> u3(12);
    stack<char (*)(char, char)> u2(12);

    char req = 0;

    Pair pair;
    char i;
    char (*f) (char, char);
    while (input>>i){
        if ((i >='0')&(i <='9')){
            if (req == 0){
     //           cout<<i<<endl;
                return;
            }
            else{
          //      label_recurse:
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
     //       cout<<"<<m"<<endl;
        }
        else if (i == 'N'){
            f = &min;
        }
        else if (i == '(')
        {
     //       cout<<"("<<endl;
            stack_push<char>(u3, req);
            req = 3;
            stack_push<char (*)(char, char)>(u2, f);
            stack_push<Pair>(u1, pair);
        }
        else if (i == ')')
        {
         //   cout<<")"<<endl;
            if (req != 1)
            {
                throw (syntax);
            }
            u2.pop(f);
            i = f(pair.first, pair.second);
            u3.pop(req);

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
                cout<<i<<endl;
                return;
            }
        }
    }
    input.close();
}


void task11(){
    char j;
    ifstream input = open_input("task11.txt");
    char req = 4;

    stack<char> u1(12);
    stack_push<char>(u1, 0);

 //   Pair pair;
    while (input>>j)
    {
        if (j == 'x' | j == 'y' | j == 'z'){
            if (req == 4)
            {
          //      pair.first = j;
                req = 3;
            }
            else if (req == 3){
                cout<<"Формула записана неправильно, ожидалось + или -\n";
                return;
            }
            else if (req == 2)
            {
          //      pair.second = j;
          label90:
                u1.pop(req);
                if (req == 0)
                {
                    cout<<"Формула записана правильно\n";
                    return;
                }
                if (input>>j){
                    if (j == ')')
                    {
                        continue;
                    }
                    else
                    {
                         cout<<"3Формула записана неправильно, ожидалось )\n";
                         return;
                    }
                }
                else{

                    cout<<"Формула записана неправильно, ожидалось )\n";
                    return;
                };
            }
        }
        else{
            if (req == 3){
                if (j == '+' | j == '-'){
                    req = 2;
                    continue;
                }
                else if (j == ')'){
                    u1.pop(req);
                    if (req == 0){
                        cout<<"Формула записана неправильно, не ожидалось )\n";
                        return;
                    }
                    if (req == 1){
                            goto label90;
                    }
                }
                else{
                    cout<<"Формула записана неправильно, ожидалось + или - или )\n";
                    return;
                }
            }
            else{
                if (j != '('){
                    cout<<"Формула записана неправильно, ожидался терм\n";
                    return;
                }
                if (req != 0) req --;
                stack_push(u1, req);
                req = 4;
            }
        }
    }
    if (req == 3){
        u1.pop(req);
        if (req == 0){
            cout<<"Формула записана правильно\n";
            return;
        }
        else{
            cout<<"Формула записана неправильно, ожидалось + или -\n";
            return;
        }
    }
    if (req == 2){
        cout<<"Формула записана неправильно, ожидался терм\n";
        return;
    }
    input.close();
}

void print_file(const char * u){
    cout<<"Исходный текст:\n";
    InputStream input;
    input.init(u);
    int len = input.len;
    char j;
    while (len > 0)
    {
        input.read(&j, 1);
        cout<<j;
        len --;
    }
    cout<<"\nВывод: \n";
    input.close();
}

int main(){
    cout<<"Задача 1\n";
    task1();
    cout<<"\nЗадача 2\n";
    task2();
    cout<<"\n\nЗадача 3\n";
    task3();
    cout<<"\n\nЗадача 4\n";
    print_file("task4.txt");
    task4();
    cout<<"\nЗадача 5\n";
    print_file("task5.txt");
    task5();
    cout<<"\nЗадача 6\n";
    print_file("task6.txt");
    task6();
    cout<<"\nЗадача 7\n";
    print_file("task7.txt");
    task7();
    cout<<"\n\nЗадача 8\n";
    print_file("task8.txt");
    task8();
    cout<<"\nЗадача 9\n";
    print_file("task9.txt");
    task9();
    cout<<"\nЗадача 10\n";
    print_file("task10.txt");
    task10();
    cout<<"\nЗадача 11\n";
    print_file("task11.txt");
    task11();
}
