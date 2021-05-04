#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h>
#include "ttmath/ttmath.h"

typedef ttmath::Big<100, 100> num;
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
    item pop(){
        pop();
        return body[index];
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
