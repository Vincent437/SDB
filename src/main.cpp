#include<iostream>
#include<string>
#include<unordered_map>

std::unordered_map<std::string, int> cmdMap = {
    {"--help", 1}
};

int main(int argc, char** argv){
    std::cout<<"sdb 0.1.0"<<std::endl;

    if(argc>0){
        switch (cmdMap[argv[i]]) {
            case 1:
                std::cout<<"usage to be developed"<<std::endl;
            
            default:
                break;
        }
    }

    return 0;
}