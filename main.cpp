#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


std::map<std::string, std::vector<std::string>> map;

void printEveryBody() {
    for (auto i = map.begin(); i != map.end(); i++) {
        std::cout << i->first << " ";
//        std::vector<std::string> locations = i->second;
//        for (int i = 0; i < locations.size(); i++) {
//            std::cout << locations.at(i) << " ";
//        }
        std::cout << std::endl;
    }
}

int main() {

    /**
     * Reads the file and construct courses, then store into map
     */
    std::ifstream file;
    file.open("../peoplePlaces.txt");
    std::string line;
    while(getline(file, line)) {
        std::vector<std::string> locations;
        std::istringstream iss(line);
        std::string name;
        std::string location;
        iss >> name;
        while(iss >> location) {
            locations.push_back(location);
        }
        map.insert(std::pair<std::string, std::vector<std::string>>(name, locations));
    }

    std::cout << "Everybody in the city" << std::endl;
    printEveryBody();

    /**
     * Print Krusty-Burger and Tavern
     */
    std::cout << "\nVisited both Krusty-Burger and Tavern" << std::endl;
    auto KB = [](std::string name) { return name == "Krusty-Burger"; };
    auto T = [](std::string name) { return name == "Tavern"; };
    auto printKBnT = [=](std::pair<std::string, std::vector<std::string>> pair) {
        auto it1 = std::find_if(pair.second.begin(), pair.second.end(), KB);
        auto it2 = std::find_if(pair.second.begin(), pair.second.end(), T);
        if(it1 != pair.second.end() && it2 != pair.second.end()) {
            std::cout << pair.first << std::endl;
        }
    };

    for_each(map.begin(), map.end(), printKBnT);

    /**
     * Print NOT Krusty_Burger and NOT Home
     */
    std::cout << "\nDid NOT visit Krusty-Burger and Home" << std::endl;
    auto H = [](std::string name) { return name == "Home"; };
    auto printNKBnNH = [=](std::pair<std::string, std::vector<std::string>> pair) {
        auto it1 = std::find_if(pair.second.begin(), pair.second.end(), KB);
        auto it2 = std::find_if(pair.second.begin(), pair.second.end(), H);
        if(it1 == pair.second.end() && it2 == pair.second.end()) {
            std::cout << pair.first << std::endl;
        }
    };

    for_each(map.begin(), map.end(), printNKBnNH);

    /**
     * Print (KB and School) and NOT(Tavern and Home)
     */
    std::cout << "\nVisited Krusty-Burger and School but did NOT visit Tavern and Home" << std::endl;
    auto S = [](std::string name) { return name == "School"; };
    auto printNKBnSbNTnH = [=](std::pair<std::string, std::vector<std::string>> pair) {
        auto it1 = std::find_if(pair.second.begin(), pair.second.end(), KB);
        auto it2 = std::find_if(pair.second.begin(), pair.second.end(), S);
        auto it3 = std::find_if(pair.second.begin(), pair.second.end(), T);
        auto it4 = std::find_if(pair.second.begin(), pair.second.end(), H);

        if((it1 != pair.second.end() && it2 != pair.second.end())
            && (it3 == pair.second.end() && it4 == pair.second.end())) {
            std::cout << pair.first << std::endl;
        }
    };

    for_each(map.begin(), map.end(), printNKBnSbNTnH);

    /**
     * Removing people who visited all locations
     */
    std::cout << "\nRemoving visited all locations" << std::endl;
    std::vector<std::string> toDelete;

    auto getRemovable = [&](std::pair<std::string, std::vector<std::string>> pair) {
        auto it1 = std::find_if(pair.second.begin(), pair.second.end(), KB);
        auto it2 = std::find_if(pair.second.begin(), pair.second.end(), S);
        auto it3 = std::find_if(pair.second.begin(), pair.second.end(), T);
        auto it4 = std::find_if(pair.second.begin(), pair.second.end(), H);

        if(it1 != pair.second.end() && it2 != pair.second.end() && it3 != pair.second.end() && it4 != pair.second.end()) {
            toDelete.push_back(pair.first);
        }
    };

    for_each(map.begin(), map.end(), getRemovable);

    for(auto item : toDelete) {
        map.erase(item);
    }

    printEveryBody();

    return 0;
}
