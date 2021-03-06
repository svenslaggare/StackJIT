#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <map>
#include "type.h"
#include "../stackjit.h"

namespace stackjit {
	class Type;
	class ClassType;
	class FunctionDefinition;
	class VMState;

	//The access modifiers
	enum class AccessModifier : unsigned char {
		Private,
		Public
	};

	//The default access modifier
	const AccessModifier DEFAULT_ACCESS_MODIFIER = AccessModifier::Public;

	//Gets an access modifier from the given string
	bool fromString(std::string str, AccessModifier& accessModifier);

	//Converts the given access modifier to a string
	std::string toString(const AccessModifier& accessModifier);

	//Represents a field
	class Field {
	private:
		const Type* mType;
		const std::size_t mOffset;
		const AccessModifier mAccessModifier;
		const bool mIsDefined;
	public:
		//Creates a new field
		Field(const Type* type, std::size_t offset, AccessModifier accessModifier, bool isDefined = true);

		//Returns the type of the field
		const Type* type() const;

		//Returns the offset of the field in the class
		std::size_t offset() const;

		//Returns the access modifier
		AccessModifier accessModifier() const;

		//Indicates if the field is defined in the current class, or in a parent class
		bool isDefined() const;
	};

	//Represents a field definition
	struct FieldDefinition {
		const std::string name;
		const Type* type;
		const AccessModifier accessModifier;

		FieldDefinition(const std::string& name, const Type* type, const AccessModifier accessModifier)
			: name(name),
			  type(type),
			  accessModifier(accessModifier) {

		}
	};

	//Contains metadata for a class
	class ClassMetadata {
	private:
		std::string mName;
		std::size_t mSize;
		const ClassType* mParentClass;

		std::vector<FieldDefinition> mFieldDefinitions;
		std::unordered_map<std::string, Field> mFields;

		std::vector<const FunctionDefinition*> mVirtualFunctions;
		std::unordered_map<std::string, int> mVirtualFunctionToIndex;
		std::map<int, std::string> mIndexToVirtualFunction;
		std::vector<std::string> mVirtualFunctionMapping;
		BytePtr* mVirtualFunctionTable;

		//Inserts the given field
		void insertField(const std::string& name, const Field& field);

		//Returns the root definition of the given virtual function
		const FunctionDefinition* getVirtualFunctionRootDefinition(const FunctionDefinition* funcDef) const;
	public:
		//Creates new class metadata
		ClassMetadata(std::string name);
		~ClassMetadata();

		//Use default move
		ClassMetadata(ClassMetadata&&) = default;
		ClassMetadata& operator=(ClassMetadata&&) = default;

		//Prevent from copying
		ClassMetadata(const ClassMetadata&) = delete;
		ClassMetadata& operator=(const ClassMetadata&) = delete;

		//Returns the name of the class
		const std::string& name() const;

		//Returns the size of the class
		std::size_t size() const;

		//Returns the parent class (if any, else null)
		const ClassType* parentClass() const;

		//Sets the parent class
		void setParentClass(const ClassType* parentClass);

		//Returns the fields
		const std::unordered_map<std::string, Field>& fields() const;

		//Indicates if a field with the given name exits
		bool fieldExists(const std::string& name) const;

		//Adds a new field to the class
		void addField(const std::string& name, const Type* type, AccessModifier accessModifier);

		//Creates the fields
		void makeFields();

		//Returns the list of virtual functions
		const std::map<int, std::string>& virtualFunctions() const;

		//Adds the given function to the list of virtual functions
		void addVirtualFunction(const FunctionDefinition& funcDef);

		//Returns the index of the given virtual function
		int getVirtualFunctionIndex(const FunctionDefinition& funcDef) const;

		//Returns the signature of the given virtual function
		const std::string& getVirtualFunctionSignature(int index) const;

		//Binds the given virtual function
		void bindVirtualFunction(const FunctionDefinition& funcDef, BytePtr funcPtr);

		//Returns the virtual function table
		BytePtr* virtualFunctionTable() const;

		//Creates the virtual function table
		bool makeVirtualFunctionTable();
	};

	//Provides class metadata
	class ClassMetadataProvider {
	private:
		std::unordered_map<std::string, ClassMetadata> mClassesMetadata;
	public:
		//Adds metadata for the given class
	    void add(const std::string& className, ClassMetadata metadata);

	    //Indicates if the struct is defined
	    bool isDefined(const std::string& className) const;

	    //Returns the metadata for the given class
	    const ClassMetadata& getMetadata(const std::string& className) const;
	    ClassMetadata& getMetadata(const std::string& className);

		//Creates the virtual function tables
		void createVirtualFunctionTables(const VMState& vmState);

		//Returns the metadata
		const std::unordered_map<std::string, ClassMetadata>& classesMetadata() const;
	};
}
