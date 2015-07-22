#include "objectref.h"

//Struct ref
StructRef::StructRef(StructHandle* handle, const ClassMetadata& metadata)
	: mHandle(handle), mMetadata(metadata) {

}