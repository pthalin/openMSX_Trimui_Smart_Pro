#ifndef POLLER_HH
#define POLLER_HH

#include <atomic>

namespace openmsx {

/** Polls for events on a given file descriptor.
  * It is possible to abort this poll from another thread.
  * This class exists because in POSIX there is no straightforward way to
  * abort a blocking I/O operation.
  */
class Poller
{
public:
	Poller();
	~Poller();

#ifndef _WIN32
	/** Waits for an event to occur on the given file descriptor.
	  * Returns true iff abort() was called or an error occurred.
	  */
	[[nodiscard]] bool poll(int fd);
#endif

	/** Returns true iff abort() was called.
	  */
	[[nodiscard]] bool aborted() {
		return abortFlag;
	}

	/** Aborts a poll in progress and any future poll attempts.
	  */
	void abort();

private:
#ifndef _WIN32
	int wakeupPipe[2];
#endif
	std::atomic_bool abortFlag;
};

} // namespace openmsx

#endif
