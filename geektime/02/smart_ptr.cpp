#include <iostream>
using namespace std;


template <typename T>
class unique_ptr
{
public:
    explicit unique_ptr(T* ptr=nullptr) : ptr_(ptr) {}
    ~unique_ptr() { delete ptr_; }
    T* get() const { return ptr_; }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    operator bool() const { return ptr_; }

    template <typename U>
    unique_ptr(unique_ptr<U>&& other)
    {
        ptr_ = other.release();
    }

    unique_ptr& operator=(unique_ptr rhs)
    {
        rhs.swap(*this);
        return *this;
    }

private:
    T* ptr_;
    T* release()
    {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void swap(unique_ptr& rhs)
    {
        using std::swap;
        swap(ptr_, rhs.ptr_);
    }
};


class shared_count
{
public:
    shared_count(): count_(1) {}
    void add_count() { ++count_; }
    long reduce_count() { return --count_; }
    long get_count() const { return count_; }

private:
    long count_;

};


template <typename T>
class shared_ptr
{
public:
    template <typename U> friend class shared_ptr;
    explicit shared_ptr(T* ptr=nullptr) : ptr_(ptr)
    {
        if (ptr)
        {
            shared_count_ = new shared_count();
        }
    }

    template <typename U>
    shared_ptr(const shared_ptr<U>& other, T* ptr)
    {
        ptr_ = ptr;
        if (ptr_)
        {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }

    ~shared_ptr()
    {
        if (ptr_ && !shared_count_->reduce_count())
        {
            delete ptr_;
            delete shared_count_;
        }
    }

    template <typename U>
    shared_ptr(const shared_ptr<U>& other)
    {
        ptr_ = other.ptr_;
        if (ptr_)
        {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }

    template <typename U>
    shared_ptr(shared_ptr<U>&& other)
    {
        ptr_ = other.ptr_;
        if (ptr_)
        {
            shared_count_ = other.shared_count_;
            other.ptr_ = nullptr;
        }
    }

    operator bool() const { return ptr_; }
    T* get() const { return ptr_; }

    void swap(shared_ptr& rhs)
    {
        using std::swap;
        swap(ptr_, rhs.ptr_);
        swap(shared_count_, rhs.shared_count_);
    }

    long use_count() const
    {
        if (ptr_)
        {
            return shared_count_->get_count();
        }
        else
        {
            return 0;
        }
    }

private:
    T* ptr_;
    shared_count* shared_count_;

};

template <typename T, typename U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U>& other)
{
    T* ptr = dynamic_cast<T*>(other.get());
    return shared_ptr<T>(other, ptr);
}


class shape
{
public:
    virtual ~shape() {}
};


class circle : public shape
{
public:
    ~circle() { puts("~circle"); }
};


int main()
{
    shared_ptr<circle> ptr1(new circle());
    printf("use count of ptr1 is %ld\n", ptr1.use_count());
    shared_ptr<shape> ptr2;
    printf("use count of ptr2 was %ld\n", ptr2.use_count());
    ptr2 = ptr1;
    printf("use count of ptr2 is now %ld\n", ptr2.use_count());
    if (ptr1)
    {
        puts("ptr1 is not empty");
    }
    shared_ptr<circle> ptr3 = dynamic_pointer_cast<circle>(ptr2);
    printf("use count of ptr3 is now %ld\n", ptr3.use_count());

    
    return 0;
}
