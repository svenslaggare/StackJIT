#include "classloader.h"
#include "loader.h"
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
		void forEachClass(ImageContainer& imageContainer, std::function<void (const stackjit::Loader::Class&)> fn) {
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

	ClassLoader::ClassLoader(VMState& vmState)
		: mVMState(vmState) {

	}

	void ClassLoader::defineClasses(const std::vector<Loader::Class>& classes) {
		//First, create the classes
		std::vector<std::pair<ClassMetadata*, std::string>> inheritingClasses;
		for (auto& classDef : classes) {
			if (mVMState.classProvider().isDefined(classDef.name())) {
				throw std::runtime_error("The class '" + classDef.name() + "' is already defined.");
			}

			mVMState.classProvider().add(classDef.name(), ClassMetadata(classDef.name()));

			if (classDef.parentClassName() != "") {
				inheritingClasses.push_back(std::make_pair(
						&mVMState.classProvider().getMetadata(classDef.name()),
						classDef.parentClassName()));
			}
		}

		//Handle inheritance
		if (inheritingClasses.size() > 0) {
			for (auto& current : inheritingClasses) {
				auto parentClass = LoaderHelpers::getClassType(mVMState, current.second);
				auto thisClass = LoaderHelpers::getClassType(mVMState, current.first->name());

				//Check if valid inheritance
				if (parentClass == thisClass) {
					throw std::runtime_error("Self inheritance is not allowed (" + current.first->name() + ").");
				}

				current.first->setParentClass(parentClass);

				if (TypeSystem::isSubtypeOf(parentClass, thisClass)	&& TypeSystem::isSubtypeOf(thisClass, parentClass)) {
					auto parentName = parentClass->className();
					auto thisName = thisClass->className();
					if (parentName > thisName) {
						std::swap(parentName, thisName);
					}

					throw std::runtime_error("Mutual inheritance is not allowed (" + parentName + ", " + thisName + ").");
				}
			}
		}
	}

	void ClassLoader::defineFields(const std::vector<Loader::Class>& classes) {
		for (auto& classDef : classes) {
			auto& classMetadata = mVMState.classProvider().getMetadata(classDef.name());

			for (auto& field : classDef.fields()) {
				auto accessModifier = LoaderHelpers::getAccessModifier(field.attributes());
				classMetadata.addField(field.name(), LoaderHelpers::getType(mVMState, field.type()), accessModifier);
			}
		}
	}

	void ClassLoader::createFields(const std::vector<Loader::Class>& classes) {
		for (auto& classDef : classes) {
			auto& classMetadata = mVMState.classProvider().getMetadata(classDef.name());
			classMetadata.makeFields();
		}
	}

	void ClassLoader::loadClasses(const std::vector<stackjit::Loader::Class>& classes) {
		defineClasses(classes);
		defineFields(classes);
		createFields(classes);
	}

	void ClassLoader::loadClasses(ImageContainer& imageContainer) {
		std::vector<Loader::Class> classes;
		forEachClass(imageContainer, [&](const stackjit::Loader::Class& classDef) {
			imageContainer.loadClassBody(classDef.name());
			classes.push_back(classDef);
		});

		loadClasses(classes);
	}
}