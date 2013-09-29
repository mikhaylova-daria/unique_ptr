#include <iostream>
#include <unordered_set>
namespace my {


class exception: public std::exception {
private:
    std::string _what;
public:
    exception(const char * _what) throw() {
           this->_what = _what;
    }
    const char* what() const throw(){
        return _what.c_str();
    }
    ~exception() throw(){}
};



template <typename T>
    class unique_ptr {
        T** ptr = nullptr;
    public:
        unique_ptr() noexcept {;}

        unique_ptr(T* &x) {
            if (x != nullptr) {
                ptr = new T*(x);
                x =nullptr;
            }
        }

        unique_ptr(const unique_ptr<T> & x) = delete;

        unique_ptr(unique_ptr<T>&& x) noexcept{
            this->ptr = x.ptr;
            x->ptr = nullptr;
        }

        ~unique_ptr(){
            if (this->ptr != nullptr) {
                if (*(this->ptr) != nullptr) {
                    delete(*(this->ptr));
                    delete(this->ptr);
                }
            }
        }

        void operator = (unique_ptr<T> & x) noexcept {
            if (this != &x) {
                this->ptr = x.ptr;
                x.ptr = nullptr;
            }
            return;
        }

        T operator *() const {
            if (this->ptr == nullptr || (*(this->ptr) == nullptr)) {
                throw (exception("nullptr"));
            } else {
             return **(this->ptr);
            }
        }

        T* operator->() const noexcept {
            return *(this->ptr);
        }

        T* get() {
            if (this->ptr == nullptr) {
                return nullptr;
            }
            return *(this->ptr);
        }

        T* release() noexcept {
            T* p = *(this->ptr);
            this->ptr = nullptr;
            return p;
        }

        void reset(T* p) noexcept {
            if (this->ptr != nullptr && *(this->ptr) != nullptr) {
                delete(*(this->ptr));
            }
            this->ptr = new T*(p);
            return;
        }

        void swap(unique_ptr& x) noexcept{
            T** p = x.ptr;
            x.ptr = this->ptr;
            this->ptr = p;
            return;
        }

        explicit operator bool() {
            return this->get() != nullptr;
        }

 };

}
    using namespace std;

int main()
{
    my::unique_ptr<char> z;
    {
        char *ptr= new char('A');
        my::unique_ptr<char> x(ptr);
        z=x;
        cout<<*z<<endl;
    }
   cout<<(*z)<<endl;

//    {
//        my::unique_ptr<char> y(ptr);
//        try {
//            cout<<(*y)<<endl;
//        } catch(my::exception &exp) {
//            cout<<exp.what()<<endl;
//        }
//    }
    int *p = new int(123);
    my::unique_ptr<int> a(p);
    cout<<(*a)<<endl;
    my::unique_ptr<int> b;
    b = a;
    cout<<*b<<endl;
    cout<<*b.get()<<endl;
    cout<<bool(a)<<endl;
    a.swap(b);
    cout<<*a<<endl;
    //cout<<*b<<endl;
    a.release();
    //cout<<*a<<endl;
    a.reset(new int (679));
    cout<<*a<<endl;

    pair<int, char> * pa = new pair<int, char>();
    my::unique_ptr<pair<int, char> > q(pa);
    q->first = 9;
    q->second ='C';
    cout << q->first<< endl;
    return 0;
}

