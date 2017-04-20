#include "loaderhelpers.h"
#include "../vmstate.h"

namespace stackjit {
	const Type* LoaderHelpers::getType(VMState& vmState, std::string typeName) {
		auto type = vmState.typeProvider().makeType(typeName);

		if (type == nullptr) {
			throw std::runtime_error("There exists no type called '" + typeName  + "'.");
		}

		return type;
	}

	const ClassType* LoaderHelpers::getClassType(VMState& vmState, std::string typeName) {
		if (!vmState.classProvider().isDefined(typeName)) {
			throw std::runtime_error("'" + typeName + "' is not a defined class.");
		}

		return (const ClassType*)vmState.typeProvider().makeType("Ref." + typeName);
	}

	AccessModifier LoaderHelpers::getAccessModifier(const Loader::AttributeContainer& attributeContainer) {
		AccessModifier accessModifier = DEFAULT_ACCESS_MODIFIER;

		if (attributeContainer.count("AccessModifier") > 0) {
			auto& accessModifierAttribute = attributeContainer.at("AccessModifier");
			if (accessModifierAttribute.values().count("value") > 0) {
				auto modifierValue = accessModifierAttribute.values().at("value");
				if (!fromString(modifierValue, accessModifier)) {
					throw std::runtime_error("'" + modifierValue + "' is not a valid access modifier.");
				}
			}
		}

		return accessModifier;
	}

	bool LoaderHelpers::getIsVirtual(const Loader::AttributeContainer& attributeContainer) {
		bool isVirtual = false;

		if (attributeContainer.count("Virtual") > 0) {
			auto& attribute = attributeContainer.at("Virtual");
			if (attribute.values().count("value") > 0) {
				auto value = attribute.values().at("value");
				if (value == "true") {
					isVirtual = true;
				} else if (value == "false") {
					isVirtual = false;
				} else {
					throw std::runtime_error("'" + value + "' is not valid value for the attribute 'Virtual'.");
				}
			}
		}

		return isVirtual;
	}

}