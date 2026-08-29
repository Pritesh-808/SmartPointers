#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define dd double
#define pb push_back
#define For(i,n) for(int i=0;i<n;i++)
#define FOR(i,n) for(ll  i=0;i<n;i++)
#define all(X) X.begin(),X.end()
#define vt vector<long long>
void accept(int arr[], ll size){for(ll h=0;h<size;h++){cin>>arr[h];}}
void accept_vector(vector<ll>&arr,ll n){for(ll i =0;i<n;i++){cin>>arr[i];}}
void showlist(list<ll>ans){for(auto it=ans.begin();it!=ans.end();it++) cout<<*it<<" ";}
void showstack(stack<ll>s){if(s.empty())return;int x=s.top();s.pop();showstack(s);cout <<x<<" ";s.push(x);}
/*clock_t tStart = clock();
printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC); */

template < typename T >
class UniquePointer {
    
    private:
    T* mem;
    
    public:
    UniquePointer(T* other=nullptr): mem(other)
    {
        
    }
    
    ~UniquePointer(){delete mem;}
    
    UniquePointer(UniquePointer& obj) = delete;
    
 
    
    UniquePointer(UniquePointer&& obj)
    {
        mem = obj.mem;
        obj.mem = nullptr;
    }
    
    UniquePointer& operator = (UniquePointer&& obj)
    {
        if(this!=&obj)
        {
            if(!(mem==nullptr))
            delete mem;
            mem = obj.mem;
            obj.mem = nullptr;
        }
        return *this;
    }
    
   // UniquePointer operator->()
    T operator*()
    {
        return *mem;
    }
    
    
    friend std::ostream& operator<<(std::ostream& os, const UniquePointer<T>& up) {
        if (up.mem)
            os << *up.mem;   // print the object being pointed to
        else
            os << "nullptr";
        return os;
    }
    
    void swap(UniquePointer& other) noexcept {
        T* temp = mem;
        mem = other.mem;
        other.mem = temp;
    }
    
    T* release()
    {
        if(mem)
        {
            T* temp = mem;
            mem = nullptr;
            return temp;
        }
    }
    void reset(T* p = nullptr)
    {
        if(mem!=p)
        {
            mem = nullptr;
            mem = p;
        }
    }
  
    
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int* p = new int(40);
    UniquePointer<int> obj1(new int(50));
    UniquePointer<int> obj2(new int(60));
    
    obj1=std::move(obj2);
    
    cout<<"obj1:: "<<obj1<<endl; // prints 60
    cout<<"obj2:: "<<obj2<<endl; // nullptr
    
    UniquePointer<int> obj3(std::move(obj1));
    
    cout<<"obj1:: "<<obj1<<endl; // nullptr
    cout<<"obj2:: "<<obj2<<endl; // nullptr
    cout<<"obj3:: "<<obj3<<endl; // prints 60
    
    UniquePointer<int> up1 (new int(40));
    UniquePointer<int> up2 (new int(50));
    
    up1.swap(up2);
    
    cout<<"up1:: "<<up1<<endl;
    cout<<"up2:: "<<up2<<endl;
    
    //cout<<"up1 post release:: "<<*up1.release()<<endl;
    //cout<<"up1 post release:: "<<*up1.release()<<endl; // throws error 
    
    up1.reset(new int(100));
    cout<<"up1:: "<<up1<<endl;
    
    up1.reset(new int(100));
    cout<<"up1:: "<<up1<<endl;
    
    
    
    
    
    
}