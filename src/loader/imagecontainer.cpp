#include "imagecontainer.h"
#include "imageloader.h"

namespace stackjit {
	ImageContainer::ImageContainer() {

	}

	ImageContainer::~ImageContainer() {
		for (auto image : mImages) {
			delete image;
		}
	}

	const std::vector<AssemblyImage*>& ImageContainer::images() const {
		return mImages;
	}

	void ImageContainer::addImage(AssemblyImage* image) {
		mImages.push_back(image);

		for (auto& classDef : image->classes()) {
			mClassToImage.insert({ classDef.first, image });
		}

		for (auto& func : image->functions()) {
			mFuncToImage.insert({ func.first, image });
		}
	}

	const Loader::Function* ImageContainer::getFunction(std::string function) const {
		if (mFuncToImage.count(function) > 0) {
			return &mFuncToImage.at(function)->functions().at(function);
		}

		return nullptr;
	}

	void ImageContainer::loadFunctionBody(std::string function) {
		if (mFuncToImage.count(function) > 0) {
			mFuncToImage[function]->loadFunctionBody(function);
		}
	}

	void ImageContainer::loadClassBody(std::string className) {
		if (mClassToImage.count(className) > 0) {
			mClassToImage[className]->loadClassBody(className);
		}
	}
}
