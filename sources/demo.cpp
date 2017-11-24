#include <print.hpp>
#include <fstream>
#include <cstring>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

using namespace boost::filesystem;
using namespace boost::program_options;

void Print(const std::string &path)
{
	std::string text;
	while (std::cin >> text) {
		std::ofstream out(path, std::ios_base::app);
		print(text, out);
		out << std::endl;
	}
}

int main(int argc, char** argv) {
	try {
		std::string text;
		std::string pathfile;
		std::string name;
		options_description desc{ "Options" };
		desc.add_options()
			("output", value<std::string>(), "set name to logfile")
			("variable", value<std::string>(&pathfile))
			("name", value<std::string>(&name), "from config file")
			;

		variables_map vm_console;
		variables_map vm_file;

		store(parse_command_line(argc, argv, desc), vm_console);
		notify(vm_console);

		std::string gAddress = getenv("HOME");
		gAddress += "/.config/demo.cfg";
		const char* _gAddress = gAddress.c_str();

		if (exists(gAddress))
			store(parse_config_file<char>(_gAddress, desc), vm_file);

		notify(vm_file);

		if (vm_console.count("help") || vm_file.count("help")) {
			std::cout << desc << '\n';
		}
		else if (vm_console.count("output")) {
			Print(vm_console["output"].as<std::string>());
		}
		else if (getenv("DEMO_OUTPUT") != nullptr) {
			Print(getenv("DEMO_OUTPUT"));
		}
		else if (vm_file.count("output")) {
			Print(vm_file["output"].as<std::string>());
		}
		else {
			Print("default.log");
		}

	}
	catch (const error &ex) {
		std::cerr << ex.what() << '\n';
	}
}
