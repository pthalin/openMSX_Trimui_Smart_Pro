#ifndef COMPRESSEDFILEADAPTER_HH
#define COMPRESSEDFILEADAPTER_HH

#include "FileBase.hh"
#include "MemBuffer.hh"
#include <memory>

namespace openmsx {

class CompressedFileAdapter : public FileBase
{
public:
	struct Decompressed {
		MemBuffer<uint8_t> buf;
		size_t size;
		std::string originalName;
		std::string cachedURL;
		time_t cachedModificationDate;
	};

	void read(void* buffer, size_t num) final override;
	void write(const void* buffer, size_t num) final override;
	span<uint8_t> mmap() final override;
	void munmap() final override;
	size_t getSize() final override;
	void seek(size_t pos) final override;
	size_t getPos() final override;
	void truncate(size_t size) final override;
	void flush() final override;
	std::string getURL() const final override;
	std::string getOriginalName() final override;
	bool isReadOnly() const final override;
	time_t getModificationDate() final override;

protected:
	explicit CompressedFileAdapter(std::unique_ptr<FileBase> file);
	~CompressedFileAdapter() override;
	virtual void decompress(FileBase& file, Decompressed& decompressed) = 0;

private:
	void decompress();

	std::unique_ptr<FileBase> file;
	std::shared_ptr<Decompressed> decompressed;
	size_t pos;
};

} // namespace openmsx

#endif
