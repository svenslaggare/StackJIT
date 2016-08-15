#pragma once
#include <unordered_map>
#include <string>

namespace stackjit {
	class Type;
	class ClassMetadataProvider;

	//Provides types
	class TypeProvider {
	private:
		std::unordered_map<std::string, const Type*> mTypes;
		ClassMetadataProvider& mClassMetadataProvider;

		//Inserts the given type
		void insertType(std::string name, const Type* type);
	public:
		//Creates a new type provider
		TypeProvider(ClassMetadataProvider& classMetadataProvider);
		~TypeProvider();

		TypeProvider(const TypeProvider&) = delete;
		TypeProvider& operator=(const TypeProvider&) = delete;

		//Tries to construct the given type. If the type could not be constructed, nullptr is returned.
		const Type* makeType(std::string name);

	    //Returns the given type. Nullptr if not found.
	    const Type* getType(std::string name) const;
	};
}
