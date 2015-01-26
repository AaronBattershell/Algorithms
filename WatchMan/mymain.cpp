#include "inputData.h"

int main(){
    std::vector < std::vector<int> > y,z;
    std::string s = "ss.txt";
	
    inputData d("ss.txt");    

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
