#pragma once
#include <string>
#include <vector>

namespace stackjit {
	class VMState;
	class ImageContainer;

	//Represents a class loader
	namespace ClassLoader {
		//Loads the given classes from the given image container
		void loadClasses(VMState& vmState, ImageContainer& imageContainer);
	}
}
