#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

//----------------------------------------------------
namespace sanjay01
{

class P
{
public:
    P(int a, int b)
    {
        cout << "P(int, int), a=" << a << ", b=" << b << endl;
    }

    P(initializer_list<int> initlist)
    {
        cout << "P(initializer_list<int>), values= ";
        for (auto i : initlist)
            cout << i << ' ';
        cout << endl;
    }
};

void print(initializer_list<int> vals)
{
    for (auto p = vals.begin(); p != vals.end(); ++p)
    { //process a list of values
        cout << *p << ' ';
    }
    cout << endl;
}

void test03_initializer_list()
{
    cout << "\ntest03_initializer_list()..................\n";

    print({12, 3, 5, 7, 11, 13, 17}); //pass a list of values to print()

    //initializer lists
    int i;                                                 //i has undefined value
    int j{};                                               //j is initialized by 0
    int *p;                                                //p has undefined value
    int *q{};                                              //q is initialized by nullptr
    cout << i << " " << j << ' ' << p << ' ' << q << endl; //121 0 0x555f8f98ac3f 0

    int x1(5.3);  //OK,but OUCH: x1 becomes 5
    int x2 = 5.3; //OK,but OUCH: x2 becomes 5
    //int x3{5.0};  //ERROR: narrowing
    //[Warning] narrowing conversion of '5.0e+0' from 'double' to 'int' inside { } [-Wnarrowing]
    //int x4 = {5.3}; //ERROR: narrowing
    //[Warning] narrowing conversion of '5.2999999999999998e+0' from 'double' to 'int' inside { } [-Wnarrowing]
    char c1{97}; //OK: even though 7 is an int,this is not narrowing
    //char c2{99999};                                                                      //ERROR: narrowing (if 99999 doesn't into a char)
    //[Warning] narrowing conversion of '99999' from 'int' to 'char' inside { } [-Wnarrowing]
    //[Warning] overflow in implicit constant conversion [-Woverflow]
    //cout << x1 << " " << x2 << ' ' << x3 << ' ' << x4 << ' ' << c1 << ' ' << c2 << endl; //5 5 5 5
    cout << "x1 = " << x1 << ", "
         << "x2 = " << x2 << ", c1 = " << c1 << endl; //这样子c1就是a了

    vector<int> v1{1, 2, 4, 5}; //OK, vector里面有这样的构造函数
    //vector<int> v2{1, 2.3, 4, 5.6}; //ERROR: narrowing doubles to ints
    //                                 //[Warning] narrowing conversion of '2.2999999999999998e+0' from 'double' to 'int' inside { } [-Wnarrowing]
    //                                 //[Warning] narrowing conversion of '5.5999999999999996e+0' from 'double' to 'int' inside { } [-Wnarrowing]
    for (auto &elem : v1)
    {
        cout << elem << ' '; //1 2 4 5
    }
    cout << endl;

    {
        P p(77, 5);     //P(int, int), a=77, b=5
        P q{77, 5};     //P(initializer_list<int>), values= 77 5
        P r{77, 5, 42}; //P(initializer_list<int>), values= 77 5 42
        P s = {77, 5};  //P(initializer_list<int>), values= 77 5
    }

    cout << "========================华丽的分割线=============================" << endl;
    cout << endl;
    {
        vector<int> v1{2, 5, 7, 13, 69, 83, 50};
        vector<int> v2({2, 5, 7, 13, 69, 83, 50});
        vector<int> v3;
        v3 = {2, 5, 7, 13, 69, 83, 50};
        v3.insert(v3.begin() + 2, {0, 1, 2, 3, 4}); //在7前面插入

        for (auto i : v3)
            cout << i << ' ';
        cout << endl; // 2 5 0 1 2 3 4 7 13 69 83 50

        cout << max({string("Ace"), string("Stacy"), string("Sabrina"), string("Barkley")}) << endl; //Stacy
        cout << min({string("Ace"), string("Stacy"), string("Sabrina"), string("Barkley")}) << endl; //Ace
        cout << max({54, 16, 48, 5}) << endl;                                                        //54
        cout << min({54, 16, 48, 5}) << endl;                                                        //5
    }
}
} // namespace sanjay01

//----------------------------------------------------
#include <complex>
namespace sanjay02
{
struct Complex1
{
    int real, imag;

    Complex1(int re, int im = 0) : real(re), imag(im) {}

    Complex1 operator+(const Complex1 &x)
    {
        return Complex1((real + x.real), (imag + x.imag));
    }
};

struct Complex2
{
    int real, imag;

    explicit Complex2(int re, int im = 0) : real(re), imag(im) {}

    Complex2 operator+(const Complex2 &x)
    {
        return Complex2((real + x.real), (imag + x.imag));
    }
};

class P
{
public:
    P(int a, int b)
    {
        cout << "P(int a, int b) \n";
    }

    P(initializer_list<int>)
    {
        cout << "P(initializer_list<int>) \n";
    }

    explicit P(int a, int b, int c) //加了explict
    {
        cout << "explicit P(int a, int b, int c) \n";
    }
};

void fp(const P &){};

void test04_explicit_multiple_argument_ctor()
{
    cout << "\ntest04_explicit_multiple_argument_ctor()..................\n";

    //explicit ctor with multi-arguments
    P p1(77, 5);     //P(int a, int b)
    P p2{77, 5};     //P(initializer_list<int>)
    P p3{77, 5, 42}; //P(initializer_list<int>)
    P p4 = {77, 5};  //P(initializer_list<int>)
    cout << "分割1" << endl;
    P p5 = {77, 5, 42}; //c++14可以, 调用了initializer_list<>模板
    P p6(77, 5, 42);    //explicit P(int a, int b, int c), 只有不需要转换的才可以调用explict的构造函数

    fp({47, 11}); //P(initializer_list<int>)
    cout << "分割" << endl;
    fp({47, 11, 3});  //介个也可以
    fp(P{47, 11});    //P(initializer_list<int>)
    fp(P{47, 11, 3}); //P(initializer_list<int>)

    P p11{77, 5, 42, 500};    //P(initializer_list<int>)
    P p12 = {77, 5, 42, 500}; //P(initializer_list<int>)
    P p13{10};                //P(initializer_list<int>)

    {
        complex<int> c1(3, 2);
        cout << c1 << endl;    //(3,2)
        complex<int> c2{3, 2}; // <== 這是否表示 complex 的 ctor 有個版本接受 initializer_list ? 搜尋結果沒發現.
                               // 可見是編譯器對它做了 implicitly convert.
        cout << c2 << endl;    //(3,2)
    }

    cout << "自定义的complex " << endl;
    {
        Complex1 c1(12, 5);
        Complex1 c2 = c1 + 5;
        cout << "[" << c2.real << "," << c2.imag << "i]" << endl; //[17,5i]
    }

    {
        Complex2 c1(3, 8);
        //Complex2 c2 = c1 + 3;	  //[Error] no match for 'operator+' (operand types are 'jj04::Complex2' and 'int')
        Complex2 c2{4, 0};
        c2 = c1 + c2;
        cout << "[" << c2.real << "," << c2.imag << "i]" << endl; //[7,8i]

        //Complex2 c3 = c1 + {2,6};	//Error] expected primary-expression before '{' token.不懂
        //我以為它會呼叫 c1.operator+(&c1, {2,6}) ==> c1.operator+(&c1, Complex2(2,6))

        //anyway，我想知道 explicit for ctors taking more than one argument 有何用途,
        //但想不出來.
    }
}
} // namespace sanjay02

//----------------------------------------------------
#include <list>
namespace sanjay03
{

template <typename T>
using Vec = list<T, allocator<T>>; // template alias

template <typename First, typename Second, int Third>
class SomeType
{
};
template <typename Second>
using TypedefName = SomeType<string, Second, 5>;

typedef void (*Func1)(double);  // Old style
using Func2 = void (*)(double); // New introduced syntax

void test34_alias_template()
{
    cout << "\ntest34_alias_template().......\n";

    Vec<int> coll;
    coll.push_back(10);
    coll.push_back(11);
    coll.push_back(12);
    for (auto &e : coll)
    {
        cout << e << " ";
    }
    cout << endl;

    TypedefName<string> obj;
}
} // namespace sanjay03
//===================
#include <string>
#include <iterator>
namespace sanjay04
{

template <typename T>
void output_static_data(const T &obj)
{
    cout << "..." << endl;
}

const int SIZE = 10000;
//想用这样着的格式: test_moveable(list, MyString);
// template<typename Container, typename T>
// void test_moveable(Container cntr, T elem){
// typename Container<T> c; //expected nested-name-specifier before ‘Container
//     for(long i = 0; i < SIZE; ++i){
//         c.insert(c.end(), T());
//     }
//     output_static_data(T());
//     Container<T> c1(c);
//     Container<T> c2(std::move(c));
//     c1.swap(c2);
// }

// void test(){
//     test_moveable(list(), string()); //也不行, 容器需要指定类型
// }

//换一个折中的方法:
//test_moveable(list<string>());
template <typename Container>
void test_moveable(Container c)
{
    typedef typename iterator_traits<typename Container::iterator>::value_type Valtype;
    for (long i = 0; i < SIZE; ++i)
    {
        c.insert(c.end(), Valtype()); //插入类对象
    }
    output_static_data(*(c.begin()));
    Container c1(c);
    Container c2(std::move(c));
    c1.swap(c2);
}

void test2()
{
    test_moveable(list<string>());
}

template <typename T,
          template <typename>
          class Container>
class XCls
{
private:
    Container<T> c;

public:
    XCls()
    { //constructor
        for (long i = 0; i < SIZE; ++i)
        {
            c.insert(c.end(), T());
        }
        output_static_data(T());
        Container<T> c1(c);
        Container<T> c2(std::move(c));
        c1.swap(c2);
    }
};

template <typename T>
using Vec = vector<T, allocator<T>>;

} // namespace sanjay04

//---------------------------------------------------
//http://en.cppreference.com/w/cpp/language/type_alias
namespace sanjay05
{

// type alias, identical to
// typedef void (*func)(int, int);
using func = void (*)(int, int);

// the name 'func' now denotes a pointer to function:
void example(int, int) {}
func fn = example;

// type alias used to hide a template parameter
template <class CharT>
using mystring =
    std::basic_string<CharT, std::char_traits<CharT>>;
mystring<char> str;
//其實在 <string>, <string_fwd.h> 都有以下 typedef
// typedef basic_string<char>   string;

// type alias can introduce a member typedef name
template <typename T>
struct Container
{
    using value_type = T; //equals to typedef T value_type;
};
// which can be used in generic programming
template <typename Container>
void fn2(const Container &c)
{
    typename Container::value_type n;
}

void test48_type_alias()
{
    cout << "\ntest48_type_alias().......\n";

    Container<int> c;
    fn2(c); // Container::value_type will be int in this function
}
} // namespace sanjay05
//---------------------------------------------------
#include <map>
namespace sanjay06
{
    //test noexcept
    double div(double a, double b) noexcept{
        return a / b; //用了noexcept, 即使除数是0都不会抛出异常
    }

    class Base{
    public:
        virtual void vfunc(float) {}
    };
    class Derived1 : Base{
    public:
        virtual void vfunc(int) final{} //参数不同, 以为是子类重新写了一个函数
    };
    class Derived2 final: Base{ //加了final, 不让继承
    public:
        // virtual void vfunc(int) override{} //加了override, 编译器会帮你检查
        virtual void vfunc(float) override final{} //函数加了final, 不让重写
    };
    // class Derived3 : Derived2{ // cannot derive from ‘final’ base ‘sanjay06::Derived2’ in derived type ‘sanjay06::Derived3’
    // public:
    //     // virtual void vfunc(int) override{} //加了override, 编译器会帮你检查
    //     virtual void vfunc(float) override{}
    // };
    // class Derived3 final: Derived1{ //加了final, 不让继承
    // public:
    //     void vfunc(int){} //不让重写
    // };
    
    
    //测试decltype
    
map<string, float> coll;
    //before
    map<string, float>::value_type elem; //pair
    //2.0
    decltype(coll)::value_type elem1;
    //用法1: 用在返回值
    // template<typename T1, typename T2>
    // decltype(x+y) add(T1 x, T2 y); //有时候会造成困扰, 因为编译器从左到右的时候看不到x+y
    //因此换一种写法:
    template<typename T1, typename T2>
    auto add(T1 x, T2 y) ->decltype(x + y){ //刚才测试只用auto也可以..
        cout << x + y << endl;
        return x + y;
    };
    //用法2: 之前在类模板或函数模板中, 传入的模板都是T t; t是一个对象, 因此之前用的是: typedef typename T::iterator iType;
    //现在可以直接从对象中拿到类型了: typedef decltype(t)::iterator iType;

} // namespace sanjay06


int main(int argc, char *argv[])
{
    // sanjay01::test03_initializer_list();
    //sanjay02::test04_explicit_multiple_argument_ctor();
    // sanjay03::test34_alias_template();
    // sanjay04::test();
    // sanjay04::test2();
    // using sanjay04::Vec;
    // using sanjay04::XCls;
    // XCls<string, Vec> c1;

    // double c = sanjay06::div(10, 0);
    // cout << c << endl;
    int c = sanjay06::add(2, 3);
    // cout << decltype(c) << endl; //这样肯定不行啊, 因为decltype(c) 得到的是int, 你能cout << int << endl;吗
    //肯定不行!

    return 0;
}
