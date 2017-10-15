#pragma once
#include "loader.h"
#include <string>
#include <vector>

namespace stackjit {
	class VMState;
	class ImageContainer;

	//Represents a class loader
	class ClassLoader {
	private:
		VMState& mVMState;
	public:
		ClassLoader(VMState& vmState);

		//Defines the given classes (not the fields)
		void defineClasses(const std::vector<Loader::Class>& classes);

		//Defines the fields for the given classes, assuming they have already been defined
		void defineFields(const std::vector<Loader::Class>& classes);

		//Create the fields assuming that they have already been defined
		void createFields(const std::vector<Loader::Class>& classes);

		//Loads the given classes
		void loadClasses(const std::vector<Loader::Class>& classes);

		//Loads the given classes from the given image container
		void loadClasses(ImageContainer& imageContainer);
	};
}
