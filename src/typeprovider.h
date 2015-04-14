#pragma once
#include <unordered_map>
#include <string>

class Type;

//Provides types
class TypeProvider {
private:
	std::unordered_map<std::string, const Type*> mTypes;
public:
	//Creates a new type provider
	TypeProvider();
	~TypeProvider();

	TypeProvider(const TypeProvider&) = delete;
	TypeProvider& operator=(const TypeProvider&) = delete;

	//Tries to construct the given type. If the type could not be constructed, nullptr is returned.
	const Type* makeType(std::string name);

	//Adds the given type
	void addType(const Type* type);

    //Returns the given type. Nullptr if not found.
    const Type* getType(std::string name) const;
};