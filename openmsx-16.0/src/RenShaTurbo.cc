#include "RenShaTurbo.hh"
#include "XMLElement.hh"
#include "Autofire.hh"
#include "MSXException.hh"
#include <memory>

namespace openmsx {

RenShaTurbo::RenShaTurbo(CommandController& commandController,
                         const XMLElement& machineConfig)
{
	if (auto* config = machineConfig.findChild("RenShaTurbo")) {
		int min_ints = config->getChildDataAsInt("min_ints", 47);
		int max_ints = config->getChildDataAsInt("max_ints", 221);
		if ((min_ints < 1) || (min_ints > max_ints) || (max_ints > 6000)) {
			throw MSXException(
				"Error in RenShaTurbo speed settings: "
				"1 <= min_ints <= max_ints <= 6000.");
		}
		autofire = std::make_unique<Autofire>(
			commandController, min_ints, max_ints, "renshaturbo");
	}
}

RenShaTurbo::~RenShaTurbo() = default;

bool RenShaTurbo::getSignal(EmuTime::param time)
{
	return autofire ? autofire->getSignal(time) : false;
}

} // namespace openmsx
