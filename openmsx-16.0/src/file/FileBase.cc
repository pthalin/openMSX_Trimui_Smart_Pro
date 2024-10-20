#include "FileBase.hh"
#include "FileOperations.hh"
#include <algorithm>
#include <cstring>

using std::string;

namespace openmsx {

span<uint8_t> FileBase::mmap()
{
	auto size = getSize();
	if (mmapBuf.empty()) {
		auto pos = getPos();
		seek(0);

		MemBuffer<uint8_t> tmpBuf(size);
		read(tmpBuf.data(), size);
		std::swap(mmapBuf, tmpBuf);

		seek(pos);
	}
	return {mmapBuf.data(), size};
}

void FileBase::munmap()
{
	mmapBuf.clear();
}

void FileBase::truncate(size_t newSize)
{
	auto oldSize = getSize();
	if (newSize < oldSize) {
		// default truncate() can't shrink file
		return;
	}
	auto remaining = newSize - oldSize;
	seek(oldSize);

	constexpr size_t BUF_SIZE = 4096;
	uint8_t buf[BUF_SIZE];
	memset(buf, 0, sizeof(buf));
	while (remaining) {
		auto chunkSize = std::min(BUF_SIZE, remaining);
		write(buf, chunkSize);
		remaining -= chunkSize;
	}
}

string FileBase::getLocalReference()
{
	// default implementation, file is not backed (uncompressed) on
	// the local file system
	return {};
}

string FileBase::getOriginalName()
{
	// default implementation just returns filename portion of URL
	return string(FileOperations::getFilename(getURL()));
}

} // namespace openmsx
