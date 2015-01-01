#include "structmetadata.h"
#include "type.h"

StructMetadata::StructMetadata(std::map<std::string, const Type*> fields)
	: fields(fields) {

}

StructMetadata::StructMetadata() {

}

const Type* StructMetadata::getField(std::string fieldName) const {
	if (fields.count(fieldName) > 0) {
		return fields.at(fieldName);
	} else {
		return nullptr;
	}
}

std::size_t StructMetadata::getFieldOffset(std::string fieldName) const {
	std::size_t offset = 0;

	for (auto field : fields) {
		if (field.first == fieldName) {
			return offset;
		}

		offset += TypeSystem::sizeOfType(field.second);
	}

	return offset;
}

std::size_t StructMetadata::getSize() const {
	std::size_t size = 0;

	for (auto field : fields) {
		size += TypeSystem::sizeOfType(field.second);
	}

	return size;
}