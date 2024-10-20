#include "DiskImageCLI.hh"
#include "CommandLineParser.hh"
#include "GlobalCommandController.hh"
#include "TclObject.hh"
#include "MSXException.hh"

using std::string;

namespace openmsx {

DiskImageCLI::DiskImageCLI(CommandLineParser& parser_)
	: parser(parser_)
{
	parser.registerOption("-diska", *this);
	parser.registerOption("-diskb", *this);
	parser.registerFileType({"di1", "di2", "dmk", "dsk", "xsa", "fd1", "fd2"}, *this);
	driveLetter = 'a';
}

void DiskImageCLI::parseOption(const string& option, span<string>& cmdLine)
{
	string filename = getArgument(option, cmdLine);
	parse(std::string_view(option).substr(1), filename, cmdLine);
}
std::string_view DiskImageCLI::optionHelp() const
{
	return "Insert the disk image specified in argument";
}

void DiskImageCLI::parseFileType(const string& filename, span<string>& cmdLine)
{
	parse(strCat("disk", driveLetter), filename, cmdLine);
	++driveLetter;
}

std::string_view DiskImageCLI::fileTypeHelp() const
{
	return "Disk image";
}

std::string_view DiskImageCLI::fileTypeCategoryName() const
{
	return "disk";
}

void DiskImageCLI::parse(std::string_view drive, std::string_view image,
                         span<string>& cmdLine)
{
	if (!parser.getGlobalCommandController().hasCommand(drive)) { // TODO WIP
		throw MSXException("No disk drive ", char(::toupper(drive.back())), " present to put image '", image, "' in.");
	}
	TclObject command = makeTclList(drive, image);
	while (peekArgument(cmdLine) == "-ips") {
		cmdLine = cmdLine.subspan(1);
		command.addListElement(getArgument("-ips", cmdLine));
	}
	command.executeCommand(parser.getInterpreter());
}

} // namespace openmsx
