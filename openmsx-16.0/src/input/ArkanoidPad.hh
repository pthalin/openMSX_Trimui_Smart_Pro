#ifndef ARKANOIDPAD_HH
#define ARKANOIDPAD_HH

#include "JoystickDevice.hh"
#include "MSXEventListener.hh"
#include "StateChangeListener.hh"
#include "serialize_meta.hh"

namespace openmsx {

class MSXEventDistributor;
class StateChangeDistributor;

class ArkanoidPad final : public JoystickDevice, private MSXEventListener
                        , private StateChangeListener
{
public:
	explicit ArkanoidPad(MSXEventDistributor& eventDistributor,
	                     StateChangeDistributor& stateChangeDistributor);
	~ArkanoidPad() override;

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	// Pluggable
	const std::string& getName() const override;
	std::string_view getDescription() const override;
	void plugHelper(Connector& connector, EmuTime::param time) override;
	void unplugHelper(EmuTime::param time) override;

	// JoystickDevice
	byte read(EmuTime::param time) override;
	void write(byte value, EmuTime::param time) override;

	// MSXEventListener
	void signalMSXEvent(const std::shared_ptr<const Event>& event,
	                    EmuTime::param time) override;
	// StateChangeListener
	void signalStateChange(const std::shared_ptr<StateChange>& event) override;
	void stopReplay(EmuTime::param time) override;

	MSXEventDistributor& eventDistributor;
	StateChangeDistributor& stateChangeDistributor;
	int shiftreg;
	int dialpos;
	byte buttonStatus;
	byte lastValue;
};
SERIALIZE_CLASS_VERSION(ArkanoidPad, 2);

} // namespace openmsx

#endif
