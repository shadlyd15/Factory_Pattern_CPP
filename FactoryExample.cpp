#include <string>
#include <map>
#include <iostream>
#include "debug.h"

using namespace std;

// Base interface
class I_Class{
    public:
        int attribute_1 = 0;
        int attribute_2 = 0;
        virtual void Initiate(I_Class *p_Object) = 0;
        virtual void Method_1() = 0;
        virtual void Method_2() = 0;
        virtual void Delete() = 0;
};

// Create function pointer
typedef I_Class* (*CreateObjectFn)(void);

// Factory for creating instances of I_Class
class Object_Factory{
    private:
        Object_Factory();
        Object_Factory(const Object_Factory &) { }
        Object_Factory &operator=(const Object_Factory &) { return *this; }


    public:
        ~Object_Factory() { m_FactoryMap.clear(); }

        typedef map<string, CreateObjectFn>	FactoryMap;
        FactoryMap		m_FactoryMap;

        static Object_Factory *Get(){
            static Object_Factory instance;
            return &instance;
        }

        void Register(const string &Class_Name, CreateObjectFn pfnCreate);
        I_Class *Create_Object(const string &Class_Name);
};

// I_Class implementations
class Class_1 : public I_Class{
    public:
        int attribute_1;
        int attribute_2;
        void Initiate(I_Class *p_Object) { 
            p_Object->attribute_1 = 11; 
            p_Object->attribute_2 = 12; 
        }
        void Method_1() { DEBUG_OK(__PRETTY_FUNCTION__); }
        void Method_2() { DEBUG_OK(__PRETTY_FUNCTION__); }
        void Delete() { delete this; }

        static I_Class * Create() { return new Class_1(); }
};

class Class_2 : public I_Class{
    public:
        int attribute_1;
        int attribute_2;
        void Initiate(I_Class *p_Object) { 
            p_Object->attribute_1 = 21; 
            p_Object->attribute_2 = 22; 
        }
        void Method_1() { DEBUG_OK(__PRETTY_FUNCTION__); }
        void Method_2() { DEBUG_OK(__PRETTY_FUNCTION__); }
        void Delete() { delete this; }

        static I_Class * Create() { return new Class_2(); }
};

class Class_3 : public I_Class{
    public:
        int attribute_1;
        int attribute_2;
        void Initiate(I_Class *p_Object) { 
            p_Object->attribute_1 = 31; 
            p_Object->attribute_2 = 32; 
        }
        void Method_1() { DEBUG_OK(__PRETTY_FUNCTION__); }
        void Method_2() { DEBUG_OK(__PRETTY_FUNCTION__); }
        void Delete() { delete this; }

        static I_Class * Create() { return new Class_3(); }
};

class Class_4 : public I_Class{
    public:
        int attribute_1;
        int attribute_2;
        void Initiate(I_Class *p_Object) { 
            p_Object->attribute_1 = 41; 
            p_Object->attribute_2 = 42; 
        }
        void Method_1() { DEBUG_OK(__PRETTY_FUNCTION__); }
        void Method_2() { DEBUG_OK(__PRETTY_FUNCTION__); }
        void Delete() { delete this; }

        static I_Class * Create() { return new Class_4(); }
};

/* Object factory constructor.
Private, called by the singleton accessor on first call.
Register the types of animals here.
*/
Object_Factory::Object_Factory(){
	Register("1", &Class_1::Create);
	Register("2", &Class_2::Create);
	Register("3", &Class_3::Create);
    Register("4", &Class_4::Create);
}

void Object_Factory::Register(const string &Class_Name, CreateObjectFn pfnCreate){
	m_FactoryMap[Class_Name] = pfnCreate;
}

I_Class *Object_Factory::Create_Object(const string &Class_Name){
	FactoryMap::iterator it = m_FactoryMap.find(Class_Name);
	if( it != m_FactoryMap.end() )
		return it->second();
	return NULL;
}

int main( int argc, char **argv ){
	I_Class *p_Object = NULL;
	string Class_Name;

	while( p_Object == NULL ){
        DEBUG("\r\n");
		DEBUG_ALERT("Type the name of a Class or 'q' to quit: ");
		cin >> Class_Name;

		if( Class_Name == "q" )
			break;

		I_Class *p_Object = Object_Factory::Get()->Create_Object(Class_Name);
		if( p_Object ){
            p_Object->Initiate(p_Object);
            p_Object->Method_1();
            p_Object->Method_2();
            DEBUG_VALUE(p_Object->attribute_1, "%d");
            DEBUG_VALUE(p_Object->attribute_2, "%d");
		}
		else{
			DEBUG_ERROR("Class_%s Class Does Not Exit !", Class_Name.c_str());
		}
		if( p_Object )
			p_Object->Delete();

		p_Object = NULL;
		Class_Name.clear();
	}
	return 0;
}
