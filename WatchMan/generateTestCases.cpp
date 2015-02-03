#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <iterator>

//Function to generate a graph of eight points,and none of the points are connected to itself
//
void genIntegers(std::vector<std::vector<int> >& myVec ){


    int x;
    srand (time(NULL));
    for(int i = 0; i < 8; i++){
        std::vector<int> h;
        if(i%2 != 0){

            if(i < 6){
               h.push_back(i+1);
            }else{
                h.push_back(i-1);
            }
            for(int j = 1; j < 10; j++){

                    x = rand()%9 + 2;
                    h.push_back(x);
            }
            myVec.push_back(h);
        }else{


            if(i < 6){
               h.push_back(i+1);
            }else{
                h.push_back(i-1);
            }



            for(int j = 1; j < 12; j++){
                if(j%2 == 0 ){
                    h.push_back(j);
                }else{
                    x = rand()%11 + 2;
                    h.push_back(x);
                }

        }
        myVec.push_back(h);

    }

  }
}

void printVec(std::vector<std::vector<int> >& myVec){
    for(auto it = myVec.begin(); it != myVec.end(); it++){
        for(auto jt= it->begin();jt != it->end(); jt++){
            std::cout<<*jt<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;


}

//Function to write vector of vector array to an output file.
//the destination fo file can be changed to anything you want when method is called
void writeToFile(std::string s,std::vector<std::vector<int> > myVec){

    std::ofstream outfile(s.c_str());

    for(auto it = myVec.begin(); it != myVec.end(); it++){
        for(auto jt= it->begin();jt != it->end(); jt++){
            outfile<<*jt<<" ";
        }
        outfile<<"\n";
    }
    std::cout<<"done!";
    outfile.close();
}


int main()
{
    std::vector<std::vector<int> > myVec;

    genIntegers(myVec);
    printVec(myVec);

    writeToFile("/home/chuka/Documents/testtext.txt",myVec);

    return 0;
}

