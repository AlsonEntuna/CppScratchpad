#include <iostream>
#include <memory>
#include <string>

class MyClass
{
public:
    MyClass(const char* name)
    : m_name(name)
    {
        std::cout << "Constructor Initialized " << m_name << std::endl;
    }

    ~MyClass()
    {
        std::cout << m_name << " is getting deleted " << std::endl;
    }

    std::string GetName() const { return m_name; }
    void SetName(const char* new_name) { m_name = new_name; }
private:
    std::string m_name;
};

std::vector<std::shared_ptr<MyClass> > g_cache;

std::shared_ptr<MyClass> GetOrCreateCacheObject(const char* name)
{
    for (const auto& cache : g_cache)
    {
        if (cache.get()->GetName() == name)
        {
            std::cout << "Cached ptr at: " << cache.get() << " detected" << std::endl;
            return cache;
        }
    }
    
    std::shared_ptr<MyClass> newPtr = std::make_shared<MyClass>(name);
    g_cache.emplace_back(newPtr);
    return newPtr;
}

int main()
{
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>("John");
    std::cout << "Name of ptr1: " << ptr1->GetName() << std::endl;

    // Setting of the new name
    ptr1->SetName("Alson");
    std::cout << "New Name of ptr1: " << ptr1->GetName() << std::endl;

    // Make a new shared poiter
    std::shared_ptr<MyClass> ptr2(ptr1);

    std::cout << "Name of ptr2: " << ptr2->GetName() << std::endl;

    std::cout << "---- Caching Mechanism ----" << std::endl;

    std::shared_ptr<MyClass> cachedPtr1 = GetOrCreateCacheObject("Ange");
    std::cout << "result of cached cachedPtr1: " << cachedPtr1->GetName() << std::endl;

    std::shared_ptr<MyClass> cachedPtr2 = GetOrCreateCacheObject("Ange");
    std::cout << "result of cached cachedPtr2: " << cachedPtr2->GetName() << std::endl;

    cachedPtr2->SetName("Entuna");
    std::cout << "after setting of value from cachedPtr2: " << cachedPtr1->GetName() << std::endl;


    std::cin.get();
    return 0;
}