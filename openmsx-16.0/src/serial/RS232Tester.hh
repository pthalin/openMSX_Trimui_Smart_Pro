#ifndef RS232TESTER_HH
#define RS232TESTER_HH

#include "RS232Device.hh"
#include "EventListener.hh"
#include "FilenameSetting.hh"
#include "FileOperations.hh"
#include "openmsx.hh"
#include "circular_buffer.hh"
#include "Poller.hh"
#include <fstream>
#include <mutex>
#include <thread>
#include <cstdio>

namespace openmsx {

class EventDistributor;
class Scheduler;
class CommandController;

class RS232Tester final : public RS232Device, private EventListener
{
public:
	RS232Tester(EventDistributor& eventDistributor, Scheduler& scheduler,
	            CommandController& commandController);
	~RS232Tester() override;

	// Pluggable
	void plugHelper(Connector& connector, EmuTime::param time) override;
	void unplugHelper(EmuTime::param time) override;
	const std::string& getName() const override;
	std::string_view getDescription() const override;

	// input
	void signal(EmuTime::param time) override;

	// output
	void recvByte(byte value, EmuTime::param time) override;

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	void run();

	// EventListener
	int signalEvent(const std::shared_ptr<const Event>& event) override;

	EventDistributor& eventDistributor;
	Scheduler& scheduler;
	std::thread thread;
	FileOperations::FILE_t inFile;
	cb_queue<byte> queue;
	std::mutex mutex; // to protect queue
	Poller poller;

	std::ofstream outFile;

	FilenameSetting rs232InputFilenameSetting;
	FilenameSetting rs232OutputFilenameSetting;
};

} // namespace openmsx

#endif
