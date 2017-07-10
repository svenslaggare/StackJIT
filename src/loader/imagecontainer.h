#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace stackjit {
	namespace Loader {
		class Function;
	}

	class AssemblyImage;

	//Container for images
	class ImageContainer {
	private:
		std::vector<AssemblyImage*> mImages;
		std::unordered_map<std::string, AssemblyImage*> mFuncToImage;
		std::unordered_map<std::string, AssemblyImage*> mClassToImage;
	public:
		//Creates a new image container
		ImageContainer();
		~ImageContainer();

		//Returns the loaded images
		const std::vector<AssemblyImage*>& images() const;

		//Adds the given image to the container
		void addImage(AssemblyImage* image);

		//Returns the given function
		const Loader::Function* getFunction(const std::string& function) const;

		//Loads the body given function if not already loaded
		void loadFunctionBody(const std::string& function);

		//Loads the body given class if not already loaded
		void loadClassBody(const std::string& className);
	};
}
