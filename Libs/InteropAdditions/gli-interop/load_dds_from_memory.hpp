/*
 * load_dds_from_memory.hpp
 *
 * This file is adapted from the file /Libs/gli-0.5.1.0/include/gli/core/load_dds.inl in the gli library.
 * Unfortunately gli's load_dds-function only loads textures from files,
 * which is incompatible with the desired asset loading system in this engine.
 *
 * The original function was ported directly to using a byte-array instead of an input-stream.
 */

#ifndef LOAD_DDS_FROM_MEMORY_HPP_
#define LOAD_DDS_FROM_MEMORY_HPP_

#include <gli/gli.hpp>
#include <cstring>

namespace gli{

/* REPLACED:
 * inline storage load_dds
 * (
 * 		char const * Filename
 * )
 */
inline storage load_dds_from_memory
(
	char const * data,
	size_t data_size
)
{
	/* REPLACED:
	 * std::ifstream FileIn(Filename, std::ios::in | std::ios::binary);
	 * assert(!FileIn.fail());
	 * 
	 * if(FileIn.fail())
	 * 		return storage();
	 */
	if(!data)
		return storage();
	const char* startPtr=data;
	const char* endPtr=data+data_size;
	const char* currentPtr=data;


	detail::ddsHeader HeaderDesc;
	detail::ddsHeader10 HeaderDesc10;
	char Magic[4];

	//* Read magic number and check if valid .dds file
	//REPLACED: FileIn.read((char*)&Magic, sizeof(Magic));
	memcpy((char*)&Magic,currentPtr,sizeof(Magic));
	currentPtr+=sizeof(Magic);

	assert(strncmp(Magic, "DDS ", 4) == 0);

	// Get the surface descriptor
	//REPLACED: FileIn.read((char*)&HeaderDesc, sizeof(HeaderDesc));
	memcpy((char*)&HeaderDesc,currentPtr,sizeof(HeaderDesc));
	currentPtr+=sizeof(HeaderDesc);
	if(HeaderDesc.format.flags & detail::DDPF_FOURCC && HeaderDesc.format.fourCC == detail::D3DFMT_DX10)
		//REPLACED:FileIn.read((char*)&HeaderDesc10, sizeof(HeaderDesc10));
	{
		memcpy((char*)&HeaderDesc10,currentPtr, sizeof(HeaderDesc10));
		currentPtr+=sizeof(HeaderDesc10);
	}

	gli::format Format(gli::FORMAT_NULL);
	if(HeaderDesc.format.fourCC == detail::D3DFMT_DX10)
		Format = detail::format_dds2gli_cast(HeaderDesc10.Format);
	else if(HeaderDesc.format.flags & detail::DDPF_FOURCC)
		Format = detail::format_fourcc2gli_cast(HeaderDesc.format.flags, HeaderDesc.format.fourCC);
	else if(HeaderDesc.format.flags & detail::DDPF_RGB)
	{
		switch(HeaderDesc.format.bpp)
		{
		case 8:
			Format = R8_UNORM;
			break;
		case 16:
			Format = RG8_UNORM;
			break;
		case 24:
			Format = RGB8_UNORM;
			break;
		case 32:
			Format = RGBA8_UNORM;
			break;
		}
	}
	else
		assert(0);

	/* REPLACED:
	 * std::streamoff Curr = FileIn.tellg();
	 * FileIn.seekg(0, std::ios_base::end);
	 * std::streamoff End = FileIn.tellg();
	 * FileIn.seekg(Curr, std::ios_base::beg);
	 */
	std::streamoff Curr = currentPtr-startPtr;
	std::streamoff End = endPtr-startPtr;

	storage::size_type const MipMapCount = (HeaderDesc.flags & detail::DDSD_MIPMAPCOUNT) ? 
		HeaderDesc.mipMapLevels : 1;

	storage::size_type FaceCount(1);
	if(HeaderDesc.cubemapFlags & detail::DDSCAPS2_CUBEMAP)
		FaceCount = int(glm::bitCount(HeaderDesc.cubemapFlags & detail::DDSCAPS2_CUBEMAP_ALLFACES));

	storage::size_type DepthCount = 1;
	if(HeaderDesc.cubemapFlags & detail::DDSCAPS2_VOLUME)
			DepthCount = HeaderDesc.depth;

	storage Storage(
		HeaderDesc10.arraySize,
		FaceCount,
		MipMapCount,
		Format,
		storage::dimensions_type(HeaderDesc.width, HeaderDesc.height, DepthCount));

	//REPLACED: FileIn.read((char*)Storage.data(), std::size_t(End - Curr));
	memcpy((char*)Storage.data(),currentPtr, std::size_t(End - Curr));

	return Storage;
}


}//namespace gli

#endif /* LOAD_DDS_FROM_MEMORY_HPP_ */
