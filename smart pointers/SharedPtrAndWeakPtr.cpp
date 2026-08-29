#include <iostream>
#include <memory>
using namespace std;

struct ControlBlock{
    int strong_count{1}; // number of shared_ptr
    int weak_count{0};   // number of weak_ptr
};

// class SharedPtr;
// class WeakPtr;

// forward declare shared and weak pointers 
template<typename T> class SharedPtr;
template<typename T> class WeakPtr;

// SharedPtr
template<typename T>
class SharedPtr{
   private:
   T* ptr;
   ControlBlock* ctrl;
   
   public:
   
   SharedPtr() : ptr(nullptr) , ctrl(nullptr){}
   
   explicit SharedPtr(T* p):ptr(p),ctrl(new ControlBlock()){
       
   }
   // cc with another SharedPtr
   SharedPtr(const SharedPtr& other){
       ptr  = other.ptr;
       ctrl = other.ctrl;
       
       if(ctrl)
       ctrl->strong_count++;
   }
   
   // construct from weap pointers
   SharedPtr(const WeakPtr<T> wp){
       ptr = wp.ptr;
       ctrl = wp.ctrl;
       //TODO
       if(ctrl && ctrl->strong_count)
       ctrl->strong_count++;
       else
       {
           ptr  = nullptr;
           ctrl = nullptr;
       }
   }
   
   // Move constructor
    SharedPtr(SharedPtr&& other) noexcept {
        ptr = other.ptr;
        ctrl = other.ctrl;
        other.ptr = nullptr;
        other.ctrl = nullptr;
    }

    // Move assignment
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();  // decrement counts from current ownership
            ptr = other.ptr;
            ctrl = other.ctrl;
            other.ptr = nullptr;
            other.ctrl = nullptr;
        }
        return *this;
    }
    
    void release(){
        if(ctrl)
        {
            ctrl->strong_count--;
            if(ctrl->strong_count == 0)
            {
                delete ptr;
                ptr = nullptr;
                
                if(ctrl->weak_count==0)
                {
                    delete ctrl;
                    ctrl = nullptr;
                }
            }
        }
        
    }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }

    int use_count() const { return ctrl ? ctrl->strong_count : 0; }
    
    ~SharedPtr(){
        release();
    }
    
    friend class WeakPtr<T>;
    
    
};

// WeakPtr
template <typename T>
class WeakPtr {
private:
    T* ptr;
    ControlBlock* ctrl;

public:
    WeakPtr() : ptr(nullptr), ctrl(nullptr) {}

    // Construct from SharedPtr
    WeakPtr(const SharedPtr<T>& sp) {
        ptr = sp.ptr;
        ctrl = sp.ctrl;
        if (ctrl) ctrl->weak_count++;
    }
    
    // Copy constructor
    WeakPtr(const WeakPtr& other) {
        ptr = other.ptr;
        ctrl = other.ctrl;
        if (ctrl) ctrl->weak_count++;
    }

    ~WeakPtr() {
        release();
    }
    void release(){
        if(ctrl)
        {
            ctrl->weak_count--;
            if(ctrl->weak_count == 0 && ctrl->strong_count == 0)
            {
                delete ctrl;;
                
            }
            ptr = nullptr;
            ctrl = nullptr;
            
        }
    }
    
    bool expired(){
        return !ctrl || ctrl->strong_count == 0;
    }
    
    SharedPtr<T> lock(){
        if(expired()){
            return make_shared<T>();
        }
        else
            return SharedPtr<T>(*this);
    }
    

};


int main() {
	// your code goes here
	// what is weak_ptr.lock?
    SharedPtr<int>sp1 = make_shared<int>(new int(20));
    SharedPtr<int>sp2(sp1); 
}
