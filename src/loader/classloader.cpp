#include "classloader.h"
#include "parser.h"
#include "../core/function.h"
#include "../vmstate.h"
#include "../core/instruction.h"
#include "../type/type.h"
#include "../core/functionsignature.h"
#include "loaderhelpers.h"
#include <stdexcept>
#include <iostream>

namespace stackjit {
	namespace {
		//Applies the given function to each class
		void forEachClass(ImageContainer& imageContainer, std::function<void (const stackjit::AssemblyParser::Class&)> fn) {
			for (auto& image : imageContainer.images()) {
				if (image->hasLoadedDefinitions()) {
					continue;
				}

				for (auto& current : image->classes()) {
					fn(current.second);
				}
			}
		}
	}

	void ClassLoader::loadClasses(VMState& vmState, ImageContainer& imageContainer) {
		//First, create the classes
		std::vector<std::pair<ClassMetadata*, std::string>> inheritingClasses;
		forEachClass(imageContainer, [&](const stackjit::AssemblyParser::Class& classDef) {
			if (vmState.classProvider().isDefined(classDef.name)) {
				throw std::runtime_error("The class '" + classDef.name + "' is already defined.");
			}

			vmState.classProvider().add(classDef.name, ClassMetadata(classDef.name));

			if (classDef.parentClassName != "") {
				inheritingClasses.push_back(std::make_pair(
						&vmState.classProvider().getMetadata(classDef.name),
						classDef.parentClassName));
			}
		});

		//Handle inheritance
		if (inheritingClasses.size() > 0) {
			for (auto& current : inheritingClasses) {
				auto parentClass = LoaderHelpers::getClassType(vmState, current.second);
				auto thisClass = LoaderHelpers::getClassType(vmState, current.first->name());

				//Check if valid inheritance
				if (parentClass == thisClass) {
					throw std::runtime_error("Self inheritance is not allowed (" + current.first->name() + ").");
				}

				current.first->setParentClass(parentClass);

				if (TypeSystem::isSubtypeOf(parentClass, thisClass)
					&& TypeSystem::isSubtypeOf(thisClass, parentClass)) {
					auto parentName = parentClass->className();
					auto thisName = thisClass->className();
					if (parentName > thisName) {
						std::swap(parentName, thisName);
					}

					throw std::runtime_error("Mutual inheritance is not allowed (" + parentName + ", " + thisName + ").");
				}
			}
		}

		//Then add the fields defs
		forEachClass(imageContainer, [&](const stackjit::AssemblyParser::Class& classDef) {
			imageContainer.loadClassBody(classDef.name);
			auto& classMetadata = vmState.classProvider().getMetadata(classDef.name);

			for (auto& field : classDef.fields) {
				auto accessModifier = LoaderHelpers::getAccessModifier(field.attributes);
				classMetadata.addField(field.name, LoaderHelpers::getType(vmState, field.type), accessModifier);
			}
		});

		//Finally, create the actual fields
		forEachClass(imageContainer, [&](const stackjit::AssemblyParser::Class& classDef) {
			auto& classMetadata = vmState.classProvider().getMetadata(classDef.name);
			classMetadata.makeFields();
		});
	}
}