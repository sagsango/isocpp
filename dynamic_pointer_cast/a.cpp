#include <iostream>
#include <memory>

#if !defined(PRAGMA)
#define PRAGMA ONCE
#endif

#if !defined(CONSTRUCTOR)
#define CONSTRUCTOR(class) std::cout << "Constructor of class :" << class << std::endl;
#endif

#if !defined(DISTRUCTOR)
#define  DISTRUCTOR(class) std::cout << "Constructor of class :" << class << std::endl;
#endif

class Person{
public:
    std::string name;
    std::string address;
    Person(){
        CONSTRUCTOR("Person");
        
    }
    virtual ~Person(){
        DISTRUCTOR("Person");
        
    }
};
class Animal{
public:
    std::string name;
    std::string ower;
    Animal(){
        CONSTRUCTOR("Animal");
        
    }
    virtual ~Animal(){
        DISTRUCTOR("Animal");
        
    }
};
class Alex:public Person{
public:
    Alex(){
        CONSTRUCTOR("Person");
        
    }
    ~Alex(){
        DISTRUCTOR("Person");
        
    }
};
class Tommy:public Animal{
public:
    Tommy(){
        CONSTRUCTOR("Tommy");
    }
    ~Tommy(){
        DISTRUCTOR("Tommy");
    }
};
int main(){
#if 0
    std::shared_ptr<Person> person = std::make_shared<Alex>();
    std::shared_ptr<Animal> animal = std::make_shared<Tommy>();
    std::shared_ptr<Alex> alexs = std::dynamic_pointer_cast<Alex>(person);
    std::shared_ptr<Tommy> tommy = std::dynamic_cast<Tommy>(animal);
#endif
    
    
#if 1
    std::shared_ptr<Alex> alexs = std::make_shared<Alex>();
    std::shared_ptr<Person> person = std::dynamic_pointer_cast<Alex>(person);
    
    std::shared_ptr<Alex> alexs1 = std::dynamic_pointer_cast<Alex>(person);
    
    std::shared_ptr<Person> person1 = std::dynamic_pointer_cast<Person>(alexs);
#endif
    // removing virtuial distructor will give error 
    
}

