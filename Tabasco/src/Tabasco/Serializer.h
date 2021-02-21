#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <type_traits>
#include "Container.h"



	class Serializer
	{
	public:

		 void StartWrite(std::string_view filePath)
		{
			outFile.open(filePath.data(), std::ios::binary | std::ios::out);
			metadata.clear();
			writeBuffer.clear();
		}

		template<uint32_t ePerRow>
		 void WriteComponents(SparseSet<ePerRow>& sSet)
		{
			sSet.serialize(writeBuffer, metadata);
		}

		 void EndWrite()
		{
			outFile.write(writeBuffer.data(), writeBuffer.size());
			outFile.write(metadata.str().data(), metadata.str().size());
			outFile.close();
			writeBuffer.clear();
			writeBuffer.shrink_to_fit();
			metadata.clear();
		}

		 void StartRead(std::string_view filePath)
		{
			std::ifstream inFile;
			inFile.open(filePath.data(), std::ios::binary | std::ios::in);

			inFile.seekg(0, std::ios::end);
			size_t fileSize = inFile.tellg();
			inFile.seekg(0, std::ios::beg);

			readBuffer.resize(fileSize);

			inFile.read(readBuffer.data(), fileSize);
			inFile.close();
		}

		template<uint32_t ePerRow>
		 void ReadToContainer(SparseSet<ePerRow>& sSet)
		{
			sSet.deserialize(readBuffer);
		}

		 void EndRead()
		 {
			 readBuffer.clear();
			 readBuffer.shrink_to_fit();
		 }


	private:
		std::ofstream outFile;
		std::vector<char> readBuffer;
		std::vector<char> writeBuffer;
		std::stringstream metadata;
	};

