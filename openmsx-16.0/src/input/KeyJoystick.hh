#ifndef KEYJOYSTICK_HH
#define KEYJOYSTICK_HH

#include "JoystickDevice.hh"
#include "MSXEventListener.hh"
#include "StateChangeListener.hh"
#include "KeyCodeSetting.hh"
#include "serialize_meta.hh"

namespace openmsx {

class CommandController;
class MSXEventDistributor;
class StateChangeDistributor;

class KeyJoystick final : public JoystickDevice, private MSXEventListener
                        , private StateChangeListener
{
public:
	KeyJoystick(CommandController& commandController,
	            MSXEventDistributor& eventDistributor,
	            StateChangeDistributor& stateChangeDistributor,
	            std::string name);
	~KeyJoystick() override;

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	// Pluggable
	const std::string& getName() const override;
	std::string_view getDescription() const override;
	void plugHelper(Connector& connector, EmuTime::param time) override;
	void unplugHelper(EmuTime::param time) override;

	// KeyJoystickDevice
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
	const std::string name;
	KeyCodeSetting up;
	KeyCodeSetting down;
	KeyCodeSetting left;
	KeyCodeSetting right;
	KeyCodeSetting trigA;
	KeyCodeSetting trigB;

	byte status;
	bool pin8;
};
SERIALIZE_CLASS_VERSION(KeyJoystick, 2);

} // namespace openmsx

#endif
