#pragma once
#include <unordered_map>
#include <typeinfo>
#include <string>

namespace ApiMock {
	class ServiceRegistry {
		static std::unordered_map<std::string, void*> container;

	public:
		template<typename T> 
		static void Register(T* object) {
			container[typeid(T).name()] = reinterpret_cast<void*>(object);
		}

		template<typename T> 
		static T* Resolve() {
			return static_cast<T*>(container[typeid(T).name()]);
		}
	};

	std::unordered_map<std::string, void*> ServiceRegistry::container;
};
