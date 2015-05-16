#include "objectref.h"

//Struct ref
StructRef::StructRef(StructHandle* handle, const StructMetadata& metadata)
	: mHandle(handle), mMetadata(metadata) {

}