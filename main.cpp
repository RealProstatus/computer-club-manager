#include"Parser.h"
#include"Club.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Right input: main.exe input.txt" << std::endl;
        return 1;
    }

    try {
        Parser parser(argv[1]);
        parser.parse();

        Club club(parser.tableCount, 
                parser.openTime, 
                parser.closeTime, 
                parser.price
        );

        for(const auto& e : parser.events)
            club.processEvent(e);

        club.closeClub();
        club.printResults();
    }
    catch(const ClubException& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    catch(const ParsingException& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    catch(const std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }

    return 0;
}