#pragma once
#include "loader.h"
#include <string>
#include <vector>

namespace stackjit {
	class VMState;
	class ImageContainer;

	//Represents a class loader
	namespace ClassLoader {
		//Defines the given classes (not the fields)
		void defineClasses(VMState& vmState, const std::vector<Loader::Class>& classes);

		//Defines the fields for the given classes, assuming they have already been defined
		void defineFields(VMState& vmState, const std::vector<Loader::Class>& classes);

		//Create the fields assuming that they have already been defined
		void createFields(VMState& vmState, const std::vector<Loader::Class>& classes);

		//Loads the given classes
		void loadClasses(VMState& vmState, const std::vector<Loader::Class>& classes);

		//Loads the given classes from the given image container
		void loadClasses(VMState& vmState, ImageContainer& imageContainer);
	}
}
