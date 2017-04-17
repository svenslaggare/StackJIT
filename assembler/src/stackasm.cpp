#include "parser.h"
#include "assembler.h"
#include "imageloader.h"
#include "bytecodeparser.h"
#include "bytecodegenerator.h"
#include <fstream>
#include <chrono>

int main(int argc, char* argv[]) {
	try {
		std::vector<stackjit::AssemblyParser::Assembly> assemblies;
		std::string outputFile = "library.simg";

		bool disassemble = false;
		std::vector<BinaryData> images;

		//Parse the input files
		for (int i = 1; i < argc; i++) {
			std::string file = argv[i];

			if (file == "-o") {
				if (i + 1 < argc) {
					outputFile = argv[i + 1];
					i++;
				} else {
					std::cerr << "Expected file name after -o flag." << std::endl;
					break;
				}
			} else if (file == "-d") {
				disassemble = true;
			} else {
				if (!disassemble) {
					std::ifstream fileStream(file);
					if (fileStream.is_open()) {
						stackjit::AssemblyParser::Assembly assembly;
						stackjit::AssemblyParser::load(fileStream, assembly);
						assemblies.emplace_back(assembly);
					} else {
						std::cerr << "Could not load file '" + file + "'" << std::endl;
					}
				} else {
					std::ifstream fileStream(file, std::ios::binary);
					if (fileStream.is_open()) {
						fileStream.seekg(0, std::ios::end);
						auto size = (std::size_t)fileStream.tellg();
						fileStream.seekg(0, std::ios::beg);

						BinaryData imageData(size);
						if (!fileStream.read(imageData.data(), size)) {
							throw std::runtime_error("Could not load image.");
						}

						images.emplace_back(imageData);
					} else {
						std::cerr << "Could not load file '" + file + "'" << std::endl;
					}
				}
			}
		}

		if (!disassemble) {
			//Generate the image
			std::ofstream imageFile(outputFile, std::ios::binary);
			Assembler assembler;
			assembler.generateImage(assemblies, imageFile);
		} else {
			//Load the image
			for (auto& imageData : images) {
				stackjit::AssemblyImage image;
				stackjit::AssemblyImageLoader::load(imageData, image);

				std::size_t i = 0;
				for (auto& func : image.functions()) {
					image.loadFunctionBody(func.first);
					stackjit::ByteCodeGenerator::generateFunction(std::cout, func.second);

					if (i != image.functions().size() - 1) {
						std::cout << std::endl;
					}
					i++;
				}

				if (image.classes().size() > 0) {
					std::cout << std::endl;
				}

				i = 0;
				for (auto& classDef : image.classes()) {
					image.loadClassBody(classDef.first);
					stackjit::ByteCodeGenerator::generateClass(std::cout, classDef.second);

					if (i != image.classes().size() - 1) {
						std::cout << std::endl;
					}
					i++;
				}
			}
		}
	} catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}