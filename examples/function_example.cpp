#include <iostream>
#include <vector>
#include <functional>


class A
{
    public:
        template<typename Function>
        // void add(Function && fn)
        void add(Function fn) 
        {  
            _functions.push_back(std::forward<Function>(fn)); 
        }
        void invoke_all()
        {
        //    for(auto && fn : _functions)
        //         fn();
        _functions[0]();
        _functions[1]();
        }
    private:
        std::vector<std::function<void()>> _functions;
};

void myfunction() { std::cout << "myfunction" << std::endl; }
void myfunction2() { std::cout << "Hello" << std::endl; } 

// struct myfunctor
// {
//        void operator()() { std::cout << "myfunctor" << std::endl ; }
// };


int main()
{
    A a;
    std::vector<std::function<void()>> _functions2;
    _functions2.push_back(myfunction); 
    _functions2[0]();

    a.add(myfunction);
    a.add(myfunction2);
    // a.add(myfunctor());
    a.invoke_all();
}