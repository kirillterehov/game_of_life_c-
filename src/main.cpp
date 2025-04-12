#include "../include/Game_Of_Life.h"
#include <boost/program_options.hpp>
#include "../include/Variable.h"

using namespace Variable;

namespace po = boost::program_options; // Simplifies the use of the Boost.Program_options library by allowing you to write po::value instead of boost::program_options::value

int main(int argc, char* argv[]) {
    try {
        po::options_description desc("Using:"); // Creates a desc object to describe the options. Line “Using:” will be displayed before the list of options when the user requests help.
        desc.add_options() // Adds options
            ("help", "show this help")
            ("width", po::value<int>()->default_value(WIDTH), "The width of the playing field")
            ("height", po::value<int>()->default_value(HEIGHT), "The height of the playing field")
            ;

            po::variables_map vm; // Creates a vm object to store option values.
            po::store(po::parse_command_line(argc, argv, desc), vm); // Parses the arguments passed to the program (argc, argv) and stores them in the vm
            po::notify(vm); // Assigns option values defined on the command line to the corresponding variables

            if (vm.count("help")) { // Checks whether the --help option was specified. If yes, displays the help and terminates the program.
                cout << desc << "\n";
                return 0;
            }


            int width = vm["width"].as<int>(); // Gets the value of the --width option as an integer.
            int height = vm["height"].as<int>(); // Gets the value of the --height option as an integer.


            Game_Of_Life a;
            a.Start(); // start game

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "Unkown Error!" << endl;
        return 1;
    }

    return 0;
}