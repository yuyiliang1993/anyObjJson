#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__

#include <iostream>
#include <string>
#include <memory>
#include <typeindex>
#include "static_json.hpp"

using namespace std;
using namespace static_json;

namespace json {
    
    template<typename U>
    inline std::string dump(U && value) {
        return to_json_string(value);
    }

    template<typename U>
    inline bool parse(U && value,  std::string jsonstr) {	
        return from_json_string(value, jsonstr);
    }

    class ANY
    {
    	public:
    		ANY() : m_tpIndex(std::type_index(typeid(void))) {}
    		ANY(const ANY& other) : m_ptr(other.clone()), m_tpIndex(other.m_tpIndex) {}
    		ANY(ANY&& other) : m_ptr(std::move(other.m_ptr)), m_tpIndex(std::move(other.m_tpIndex)) {}

    		template<class T>
    		ANY(T&& t)
    			: m_ptr(new Derived<typename std::decay<T>::type>(std::forward<T>(t)))
    			, m_tpIndex(typeid(typename std::decay<T>::type)) {
                   // std::cout<<"ANY(T&&t)"<<std::endl;
               }

    		ANY& operator=(const ANY& other) {
    			if (m_ptr == other.m_ptr) {
    				return *this;
    			}
    			m_ptr = other.clone();
    			m_tpIndex = other.m_tpIndex;
    			return *this;
    		}
            
    		template<class Archive>
    		friend void serialize(Archive& ar, ANY& a) {
    		}
            
    	private:
    	    class Base;
            using BasePtr = std::unique_ptr<Base>;
    		class Base {
                public:
    			virtual BasePtr clone() const = 0;
    		};
    	   
    		template<typename T>
    		class Derived : public Base{
    		    public:

                template<typename...Args>
    			Derived(Args&&...args) : m_value(std::forward<Args>(args)...){}
    			BasePtr clone() const {
    				return BasePtr(new Derived(m_value));
    			}
    			T m_value;
    		};

    		BasePtr clone() const {
    			if (m_ptr) {
    				return m_ptr->clone();
    			}
    			return nullptr;
    		}
        
    		BasePtr         m_ptr;
    		std::type_index m_tpIndex;//指向type_info的指针类
    	};
}

#endif