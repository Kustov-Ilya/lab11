#include <print.hpp>
#include <cstdlib>
#include <boost/program_options.hpp>


namespace po = boost::program_options;

void PrintFile(const std::string &path)
{
	std::string text;
	while(std::cin >> text) {
		std::ofstream out(path, std::ios_base::app);
		print(text, out);
		out << std::endl;
	}
}

/*void ReadFile(po::options_description &desc,
							po::variables_map& vm)
{
	std::ifstream configfile("~/.config/demo.cfg");
	vm = po::variables_map();
	po::store(po::parse_config_file(configfile, desc), vm);
	po::notify(vm);
}*/

int main(int argc, char** argv)
{
	std::string pathfile;
	std::string name;
	po::options_description desc("Allowed optins");
	desc.add_options()
			("output", po::value<std::string>(), "set name to logfile")
			("variable", po::value<std::string>(&pathfile))
			("name", po::value<std::string>(&name), "from config file")
	;

	po::variables_map vm;
	std::string pathconf = std::getenv("HOME");
	pathconf += "/.config/demo.cfg";

	std::ifstream configfile(pathconf);
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::store(po::parse_environment(desc,
		[](const std::string &env_var)
		{
			return env_var == "DEMO_OUTPUT" ? "variable" : "";
		}),
		vm);
	po::store(po::parse_config_file(configfile, desc), vm);
	po::notify(vm);

	if (vm.count("output")) {
		PrintFile(vm["output"].as<std::string>());
	} else if (!pathfile.empty()) {
		PrintFile(pathfile);
	} else if (!name.empty()) {
		PrintFile(name);
	} else {
		PrintFile("default.log");
	}
	configfile.close();
	return 0;
}
