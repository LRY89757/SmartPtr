#pragma once
#ifndef FUNC_H_
#define FUNC_H_
#include <iostream>

namespace std{

    template <typename T>
    class shared_ptr{

        typedef T elemtype;

private:
        int *countptr{nullptr};
        elemtype *ptr{nullptr};

public:
        shared_ptr();

        shared_ptr(const shared_ptr<T> &sptr); // 拷贝构造

        shared_ptr& operator=(const shared_ptr& r ) noexcept; // 拷贝赋值

        shared_ptr(shared_ptr<T>&&sptr) noexcept; // 移动构造

        shared_ptr &operator=(shared_ptr<T> &&sptr) noexcept; // 移动赋值

        shared_ptr(T *); // 指针构造

        ~shared_ptr(); // 析构函数

        int use_count() { return ptr ? *countptr : 0; }

        T *get() { return ptr; }

        T *operator->() const { return ptr; } // 重载指针运算符

        // void reset() noexcept; 

        // To Do
        // std::basic_ostream &operator<<(std::basic_ostream&os, const shared_ptr<T> &sptr){ os << sptr.ptr; return os; }
    };


    template <typename T>
    class unique_ptr
    {

private:

public:





    };

    template <typename T>
    shared_ptr<T>::shared_ptr() : countptr(new int[1]), ptr(nullptr) 
    {
        std::cout<<"无参构造函数"<<std::endl;
        *countptr = 1;
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(const shared_ptr<T> &sptr): countptr(sptr.countptr), ptr(sptr.ptr)
    {
        std::cout<<"拷贝构造函数"<<std::endl;
        *countptr += 1;
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(T* _ptr): countptr(new int [1]), ptr(_ptr)
    {
        std::cout<<"指针构造函数"<<std::endl;
        *countptr = 1;
    }

    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& sptr)noexcept
    // :countptr(sptr.countptr), ptr(sptr.ptr)
    {
        if(ptr == sptr.ptr)
            return *this;
        
        this->~shared_ptr();
        std::cout<<"拷贝赋值函数"<<std::endl;
        this->countptr = sptr.countptr;
        this->ptr = sptr.ptr;
        *countptr += 1;
        return *this;
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(shared_ptr<T>&&sptr)noexcept
    {
        std::cout<<"移动构造函数"<<std::endl;
        this->countptr = sptr.countptr;
        this->ptr = sptr.ptr;

        sptr.ptr = nullptr;
        sptr.countptr = new int[1];
        *(sptr.countptr) = 1;
    }

    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T> &&sptr)noexcept
    {
        if(ptr == sptr.ptr) // 两个if语句顺序也不能换
            return *this;
        
        this->~shared_ptr();
        std::cout<<"移动赋值函数"<<std::endl;
        this->countptr = sptr.countptr;
        this->ptr = sptr.ptr;

        sptr.ptr = nullptr;
        sptr.countptr = new int[1];
        *(sptr.countptr) = 1;
        return *this;
    }

    template <typename T>
    shared_ptr<T>::~shared_ptr()
    {
        int count = *countptr;
        // std::cout<<count<<std::endl;
        if (count > 1)
        {
            *countptr -= 1;
            countptr = nullptr;
            ptr = nullptr;
        }
        else
        {
            std::cout << "最后的析构" << std::endl;
            if (countptr)
            {
                delete[] countptr;
                countptr = nullptr;
            }
            if (ptr)
            {
                delete ptr;
                ptr = nullptr;
            }
        }
    }




} // namespace std;

#endif

