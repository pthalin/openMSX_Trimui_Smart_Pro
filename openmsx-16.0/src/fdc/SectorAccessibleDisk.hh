#ifndef SECTORACCESSIBLEDISK_HH
#define SECTORACCESSIBLEDISK_HH

#include "DiskImageUtils.hh"
#include "Filename.hh"
#include "sha1.hh"
#include <vector>
#include <memory>

namespace openmsx {

class FilePool;
class PatchInterface;

class SectorAccessibleDisk
{
public:
	static constexpr size_t SECTOR_SIZE = sizeof(SectorBuffer);

	// sector stuff
	void readSector (size_t sector,       SectorBuffer& buf);
	void writeSector(size_t sector, const SectorBuffer& buf);
	size_t getNbSectors() const;

	// write protected stuff
	bool isWriteProtected() const;
	void forceWriteProtect();

	virtual bool isDummyDisk() const;

	// patch stuff
	void applyPatch(Filename patchFile);
	std::vector<Filename> getPatches() const;
	bool hasPatches() const;

	/** Calculate SHA1 of the content of this disk.
	 * This value is cached (and flushed on writes).
	 */
	Sha1Sum getSha1Sum(FilePool& filepool);

	// For compatibility with nowind
	//  - read/write multiple sectors instead of one-per-one
	//  - use error codes instead of exceptions
	//  - different order of parameters
	int readSectors (      SectorBuffer* buffers, size_t startSector,
	                 size_t nbSectors);
	int writeSectors(const SectorBuffer* buffers, size_t startSector,
	                 size_t nbSectors);

	// should only be called by EmptyDiskPatch
	virtual void readSectorImpl (size_t sector, SectorBuffer& buf) = 0;

protected:
	SectorAccessibleDisk();
	~SectorAccessibleDisk();

	// Peek-mode changes the behaviour of readSector(). ATM it only has
	// an effect on DirAsDSK. See comment in DirAsDSK::readSectorImpl()
	// for more details.
	void setPeekMode(bool peek) { peekMode = peek; }
	bool isPeekMode() const { return peekMode; }

	virtual void checkCaches();
	virtual void flushCaches();
	virtual Sha1Sum getSha1SumImpl(FilePool& filepool);

private:
	virtual void writeSectorImpl(size_t sector, const SectorBuffer& buf) = 0;
	virtual size_t getNbSectorsImpl() const = 0;
	virtual bool isWriteProtectedImpl() const = 0;

	std::unique_ptr<const PatchInterface> patch;
	Sha1Sum sha1cache;
	bool forcedWriteProtect = false;
	bool peekMode = false;
};

} // namespace openmsx

#endif
