#include <print.hpp>
#include <cstdlib>
#include <boost/program_options.hpp>


namespace po = boost::program_options;

void Save(const std::string &path)
{
	std::string text;
	while(std::cin >> text) {
		std::ofstream out(path, std::ios_base::app);
		print(text, out);
		out << std::endl;
	}
}


int main(int argc, char** argv)
{
	std::string pathfile;
	std::string name;
	po::options_description desc("List of arguments");
	desc.add_options()
			("output", po::value<std::string>(), "Name of log file")
			("variable", po::value<std::string>(&pathfile))
			("name", po::value<std::string>(&name), "get name from config file")
	;

	po::variables_map vm;
	
	//получаем переменную окружения $HOME - текущую директорию
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

	//если есть --output
	if (vm.count("output")) {
		Save(vm["output"].as<std::string>());
	//если есть переменная окружения
	} else if (!pathfile.empty()) {
		Save(pathfile);
	} else if (!name.empty()) {
		Save(name);
	} else {
		Save("default.log");
	}
	configfile.close();
	return 0;
}
