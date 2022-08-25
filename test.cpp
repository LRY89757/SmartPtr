#include <memory>
#include <iostream>
#include "func.h"

void test_shared_ptr01();
void test_basic();
void test_reset();
void test_reset1();

struct Foo
{
    Foo(int n = 0) noexcept : bar(n)
    {
        std::cout << "Foo::Foo(), bar = " << bar << " @ " << this << '\n';
    }
    ~Foo()
    {
        std::cout << "Foo::~Foo(), bar = " << bar << " @ " << this << "\n";
    }
    int getBar() const noexcept { return bar; }

private:
    int bar;
};

int main()
{
    // test_basic();
    // test_reset();
    // test_shared_ptr01();
    test_reset1();
    return 0;
}



template <typename T>
void printshared(std::shared_ptr<T>& ptr)
{
    std::cout<<ptr.use_count()<<std::endl;
    std::cout<<ptr.get()<<std::endl;
}
template <typename T>
void printshared(stdd::shared_ptr<T>& ptr)
{
    std::cout<<ptr.use_count()<<std::endl;
    std::cout<<ptr.get()<<std::endl;
}

void test_shared_ptr01()
/*无参构造函数*/
{
    std::cout<<"无参构造函数"<<std::endl<<std::endl;

    std::cout<<"std:"<<std::endl;
    std::shared_ptr<int> ptr = std::shared_ptr<int>();
    printshared(ptr);
    std::cout<<std::endl;

    std::cout<<"stdd:"<<std::endl;
    stdd::shared_ptr<int> ptr1 = stdd::shared_ptr<int>();
    printshared(ptr1);
    std::cout<<std::endl;
}

void test_shared_ptr02()
/*拷贝构造函数*/
{
    std::cout<<"拷贝构造函数"<<std::endl<<std::endl;

    // std::cout<<"std:"<<std::endl;
    // std::shared_ptr<int> ptr = std::shared_ptr<int>();
    // printshared(ptr);
    // std::cout<<std::endl;

    // std::cout<<"stdd:"<<std::endl;
    // stdd::shared_ptr<int> ptr1 = stdd::shared_ptr<int>();
    // printshared(ptr1);
    // std::cout<<std::endl;
}

void test_reset1()
{
    std::cout << "1) std:\n";
    {
        // std::shared_ptr<Foo> sptr = std::make_shared<Foo>(100);
        std::shared_ptr<Foo> sptr = std::shared_ptr<Foo>(new Foo);
        // std::shared_ptr<int> sptr = std::shared_ptr<int>(new int[10]);

        std::cout << "Foo::bar = " << sptr->getBar() << ", use_count() = "
                  << sptr.use_count() << '\n';

        // Reset the shared_ptr without handing it a fresh instance of Foo.
        // The old instance will be destroyed after this call.
        std::cout << "call sptr.reset()...\n";
        sptr.reset(); // calls Foo's destructor here
        sptr.reset(); // calls Foo's destructor here
        sptr.reset(); // calls Foo's destructor here
        std::cout << "After reset(): use_count() = " << sptr.use_count()
                  << ", sptr = " << sptr.get() << '\n';
    } // No call to Foo's destructor, it was done earlier in reset().

    std::cout<<std::endl;

    std::cout << "2) stdd:\n";
    {
        // std::shared_ptr<Foo> sptr = std::make_shared<Foo>(100);
        stdd::shared_ptr<Foo> sptr = stdd::shared_ptr<Foo>(new Foo);
        // std::shared_ptr<int> sptr = std::shared_ptr<int>(new int[10]);

        std::cout << "Foo::bar = " << sptr->getBar() << ", use_count() = "
                  << sptr.use_count() << '\n';

        // Reset the shared_ptr without handing it a fresh instance of Foo.
        // The old instance will be destroyed after this call.
        std::cout << "call sptr.reset()...\n";
        sptr.reset(); // calls Foo's destructor here
        sptr.reset(); // calls Foo's destructor here
        sptr.reset(); // calls Foo's destructor here
        sptr.reset(); // calls Foo's destructor here
        std::cout << "After reset(): use_count() = " << sptr.use_count()
                  << ", sptr = " << sptr.get() << '\n';
    } // No call to Foo's destructor, it was done earlier in reset().


}


void test_basic()
{
    std::cout<<"阶段1"<<std::endl;
    std::shared_ptr<int> ptr = std::shared_ptr<int>(new int);
    printshared(ptr);
    std::cout<<std::endl;

    // std::cout<<ptr.use_count()<<std::endl;
    // std::cout<<ptr.get()<<std::endl;

    std::cout<<"阶段2"<<std::endl;
    std::shared_ptr<int> ptr1 = ptr;
    printshared(ptr);
    std::shared_ptr<int> ptr2(ptr);
    printshared(ptr);
    std::cout<<std::endl;

    std::cout<<"阶段3"<<std::endl;
    std::shared_ptr<int> ptr3 = std::move(ptr);

    printshared(ptr);
    printshared(ptr3);
    std::cout<<std::endl;

    std::cout<<"阶段4"<<std::endl;
    std::shared_ptr<int> ptr4;
    ptr4 = std::move(ptr3);
    printshared(ptr3);
    printshared(ptr4);
    std::cout<<std::endl;

    std::cout<<"阶段5"<<std::endl;
    ptr4 = ptr4;
    ptr4 = ptr2;
    ptr3 = ptr4;
    ptr4 = std::move(ptr4);
    std::cout<<std::endl;

    std::cout<<"阶段6"<<std::endl;
    std::shared_ptr<Foo>fptr = std::shared_ptr<Foo>(new Foo);
    std::cout<<std::endl;

    std::cout<<"阶段7"<<std::endl;
    std::shared_ptr<int>ptr5 = std::shared_ptr<int>(new int);
    // ptr5.reset();
    std::cout<<std::endl;

    std::cout<<"阶段8"<<std::endl;
    // std::shared_ptr<int>ptr6 = new int; // 没有explict
    std::cout<<std::endl;

    std::cout<<"阶段last"<<std::endl;
    std::cout<<ptr.use_count()<<std::endl;
    std::cout<<ptr3.use_count()<<std::endl;
    std::cout<<ptr4.use_count()<<std::endl;
}

void test_reset()
{
    std::cout << "1) unique ownership\n";
    {
        // std::shared_ptr<Foo> sptr = std::make_shared<Foo>(100);
        std::shared_ptr<Foo> sptr = std::shared_ptr<Foo>(new Foo);
        // std::shared_ptr<int> sptr = std::shared_ptr<int>(new int[10]);

        std::cout << "Foo::bar = " << sptr->getBar() << ", use_count() = "
                  << sptr.use_count() << '\n';

        // Reset the shared_ptr without handing it a fresh instance of Foo.
        // The old instance will be destroyed after this call.
        std::cout << "call sptr.reset()...\n";
        sptr.reset(); // calls Foo's destructor here
        std::cout << "After reset(): use_count() = " << sptr.use_count()
                  << ", sptr = " << sptr.get() << '\n';
    } // No call to Foo's destructor, it was done earlier in reset().

//     std::cout << "\n2) unique ownership\n";
//     {
//         std::shared_ptr<Foo> sptr = std::make_shared<Foo>(200);

//         std::cout << "Foo::bar = " << sptr->getBar() << ", use_count() = "
//                   << sptr.use_count() << '\n';

//         // Reset the shared_ptr, hand it a fresh instance of Foo.
//         // The old instance will be destroyed after this call.
//         std::cout << "call sptr.reset()...\n";
//         sptr.reset(new Foo{222});
//         std::cout << "After reset(): use_count() = " << sptr.use_count()
//                   << ", sptr = " << sptr << "\nLeaving the scope...\n";
//     } // Calls Foo's destructor.

//     std::cout << "\n3) multiple ownership\n";
//     {
//         std::shared_ptr<Foo> sptr1 = std::make_shared<Foo>(300);
//         std::shared_ptr<Foo> sptr2 = sptr1;
//         std::shared_ptr<Foo> sptr3 = sptr2;

//         std::cout << "Foo::bar = " << sptr1->getBar() << ", use_count() = "
//                   << sptr1.use_count() << '\n';

//         // Reset the shared_ptr sptr1, hand it a fresh instance of Foo.
//         // The old instance will stay shared between sptr2 and sptr3.
//         std::cout << "call sptr1.reset()...\n";
//         sptr1.reset(new Foo{333});

//         std::cout << "After reset():\n"
//                   << "sptr1.use_count() = " << sptr1.use_count()
//                   << ", sptr1 @ " << sptr1 << '\n'
//                   << "sptr2.use_count() = " << sptr2.use_count()
//                   << ", sptr2 @ " << sptr2 << '\n'
//                   << "sptr3.use_count() = " << sptr3.use_count()
//                   << ", sptr3 @ " << sptr3 << '\n'
//                   << "Leaving the scope...\n";
//     } // Calls two destructors of: 1) Foo owned by sptr1,
//       // 2) Foo shared between sptr2/sptr3.
}

