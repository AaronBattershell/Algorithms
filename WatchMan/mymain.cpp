#include "inputData.h"

int main(){

    inputData d;

    std::vector < std::vector<int> > y,z;
    std::string s = "/home/chuka/Documents/test1/ss.txt";
    d.readtext1(s);
    auto x = d.get_wallSetVector(s);
    y = d.get_paintVector(s);
    z = d.get_guardVector(s);

    d.print_wallSet(x);
    d.print_paintSet(y);
    d.print_guardSet(z);

    auto h = d.get_wall_EdgeArray();
    std::cout<<std::endl;
    for(auto i:h){
        std::cout<<i<<" ";
    }



    return 0;

}
