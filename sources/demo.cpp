#include <print.hpp>
#include <fstream>
#include <cstring>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

using namespace boost::filesystem;
using namespace boost::program_options;

int main(int argc, char** argv) {
    try {
        std::string text;

        options_description desc{"Options"};
        desc.add_options()
        ("help,h", "Help screen")
        ("output", value<std::string>()/*->notifier(out_func)*/, "Output");

        variables_map vm_console;
        variables_map vm_file;
        
        store(parse_command_line(argc, argv, desc), vm_console);
        notify(vm_console);

        std::string gAddress = getenv("HOME");
        gAddress += "/.config/demo.cfg";
        const char* _gAddress = gAddress.c_str();

        if(exists(gAddress))
            store(parse_config_file<char>( _gAddress, desc ), vm_file);

        notify(vm_file);

        if (vm_console.count("help") || vm_file.count("help")) {
            std::cout << desc << '\n';
        } else if(vm_console.count("output")) {

            std::cout << "Output in >> " << vm_console["output"].as<std::string>() << '\n';
            std::ofstream out(vm_console["output"].as<std::string>(), std::ios_base::app);
            while(std::cin >> text) {
                print(text, out);
                out << std::endl;
            }
            out.close();

        } else if (getenv("DEMO_OUTPUT") != nullptr) {
            std::cout << "ENV" << std::endl;
            std::string _trAddress = getenv("DEMO_OUTPUT");
            std::ofstream out(_trAddress, std::ios_base::app);
            while(std::cin >> text) {
                print(text, out);
                out << std::endl;
            }
            out.close();
        } else if (vm_file.count("output")) {
            std::cout << "Output in >> " << vm_file["output"].as<std::string>() << '\n';
            std::ofstream out(vm_file["output"].as<std::string>(), std::ios_base::app);
            while(std::cin >> text) {
                print(text, out);
                out << std::endl;
            }
            out.close();
        } else {
            std::cout << "DEFAULT" << std::endl;
            std::ofstream out("default.log", std::ios_base::app);
            while(std::cin >> text) {
                print(text, out);
                out << std::endl;
            }
            out.close();
        }

    } catch (const error &ex) {
        std::cerr << ex.what() << '\n';
    }
}
