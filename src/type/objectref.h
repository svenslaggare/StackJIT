#pragma once
#include <string>
#include <stdexcept>
#include "../stackjit.h"

namespace stackjit {
	class ClassMetadata;
	class Type;

	//Represents a raw object reference
	using RawObjectRef = BytePtr;

	//Represents a raw class reference
	using RawClassRef = BytePtr;

	//Represents a raw array reference
	using RawArrayRef = BytePtr;

	//Represents an object reference
	class ObjectRef {
	private:
		BytePtr mPtr;
		const Type* mType;
		std::size_t mSize;

		//Sets the GC information
		void setGCInfo(bool isMarked, int count);

		//Sets the mark status
		void setMarked(bool isMarked);
	public:
		//Creates a new reference to the given object.
		//Note the reference should be to the data, not the header.
		ObjectRef(RawObjectRef objRef);

		//Returns the type of the object
		inline const Type* type() const {
			return mType;
		}

		//Returns a pointer to the header
		BytePtr fullPtr() const;

		//Returns a pointer to the data
		BytePtr dataPtr() const;

		//Returns the size of the object
		std::size_t size() const;

		//Returns the size of the object + header
		std::size_t fullSize() const;

		//Indicates if the object is marked
		bool isMarked() const;

		//Marks the current object
		void mark();

		//Unmarks the current object
		void unmark();

		//Returns the number of survived collections. Note this value is bounded, max value is 127.
		int survivalCount() const;

		//Increases the number of survived collections
		void increaseSurvivalCount();

		//Resets the survival count
		void resetSurvivalCount();
	};

	//Represents a field reference
	template<typename T>
	class FieldRef {
	private:
		T* mFieldPtr;

		//Creates a new reference to the given field
		FieldRef(BytePtr fieldPtr);
		friend class ClassRef;
	public:
		//Returns a pointer to the field
		T* value();
	};

	//Represents a class reference
	class ClassRef {
	private:
		ObjectRef mObjRef;
		const ClassMetadata& mMetadata;
	public:
		//Creates a new reference to the given class
		ClassRef(ObjectRef objRef, const ClassMetadata& metadata);

		//Returns the underlying object reference
		inline ObjectRef objRef() const {
			return mObjRef;
		}

		//Returns a reference to a field of the given type
		template<typename T>
		FieldRef<T> getField(std::string name, const Type* type);
	};

	//Represents an array reference
	template<typename T>
	class ArrayRef {
	private:
		T* mElementsPtr;
		int mLength;
	public:
		//Creates a new reference to the given array
		ArrayRef(const RawArrayRef arrayRef);

		//Returns a pointer to the elements
		inline T* elementsPtr() const;

		//Returns the value of the given element
		inline T getElement(int index) const;

		//Returns the length of the array
		inline int length() const;
	};
}

#include "objectref.hpp"
