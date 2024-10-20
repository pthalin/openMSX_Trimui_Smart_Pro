#ifndef CARTRIDGESLOTMANAGER_HH
#define CARTRIDGESLOTMANAGER_HH

#include "RecordedCommand.hh"
#include "InfoTopic.hh"
#include <memory>
#include <string_view>

namespace openmsx {

class MSXMotherBoard;
class ExtCmd;
class HardwareConfig;

class CartridgeSlotManager
{
public:
	explicit CartridgeSlotManager(MSXMotherBoard& motherBoard);
	~CartridgeSlotManager();

	static int getSlotNum(std::string_view slot);

	void createExternalSlot(int ps);
	void createExternalSlot(int ps, int ss);
	void removeExternalSlot(int ps);
	void removeExternalSlot(int ps, int ss);
	void testRemoveExternalSlot(int ps, const HardwareConfig& allowed) const;
	void testRemoveExternalSlot(int ps, int ss, const HardwareConfig& allowed) const;

	// Query/allocate/free external slots
	void getSpecificSlot(unsigned slot, int& ps, int& ss) const;
	void getAnyFreeSlot(int& ps, int& ss) const;
	void allocateSlot(int ps, int ss, const HardwareConfig& hwConfig);
	void freeSlot(int ps, int ss, const HardwareConfig& hwConfig);

	// Allocate/free external primary slots
	int allocateAnyPrimarySlot(const HardwareConfig& hwConfig);
	int allocateSpecificPrimarySlot(unsigned slot, const HardwareConfig& hwConfig);
	void freePrimarySlot(int ps, const HardwareConfig& hwConfig);

	bool isExternalSlot(int ps, int ss, bool convert) const;

private:
	int getSlot(int ps, int ss) const;

	MSXMotherBoard& motherBoard;

	class CartCmd final : public RecordedCommand {
	public:
		CartCmd(CartridgeSlotManager& manager, MSXMotherBoard& motherBoard,
			std::string_view commandName);
		void execute(span<const TclObject> tokens, TclObject& result,
			     EmuTime::param time) override;
		std::string help(const std::vector<std::string>& tokens) const override;
		void tabCompletion(std::vector<std::string>& tokens) const override;
		bool needRecord(span<const TclObject> tokens) const override;
	private:
		const HardwareConfig* getExtensionConfig(std::string_view cartname);
		CartridgeSlotManager& manager;
		CliComm& cliComm;
	} cartCmd;

	struct CartridgeSlotInfo final : InfoTopic {
		explicit CartridgeSlotInfo(InfoCommand& machineInfoCommand);
		void execute(span<const TclObject> tokens,
			     TclObject& result) const override;
		std::string help(const std::vector<std::string>& tokens) const override;
	} extSlotInfo;

	struct Slot {
		~Slot();
		bool exists() const;
		bool used(const HardwareConfig* allowed = nullptr) const;

		std::unique_ptr<CartCmd> cartCommand;
		std::unique_ptr<ExtCmd> extCommand;
		const HardwareConfig* config = nullptr;
		unsigned useCount = 0;
		int ps = 0;
		int ss = 0;
	};
	static constexpr unsigned MAX_SLOTS = 16 + 4;
	Slot slots[MAX_SLOTS];
};

} // namespace openmsx

#endif
