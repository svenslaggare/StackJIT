#include "objectref.h"

//Struct ref
ClassRef::ClassRef(ClassHandle* handle, const ClassMetadata& metadata)
	: mHandle(handle), mMetadata(metadata) {

}