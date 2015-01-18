#ifndef POINTS_H
#define POINTS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>

struct Points{
     Points();

     //..............I will fix it into a class structure tommorow.....Just showing work so far


    //Input file can also be read at runtime from a string s like this : std::ifstream infile(s.c_str()); 
    std::ifstream infile("/home/chuka/Documents/test1/s.txt");

    //variables for text file's first and second line...
    int wall_set,paint_set,guard_set,noOfwall;

    std::vector<int> val;
    int temp ;
    std::string line;
    std::stringstream ss;

    std::getline(infile,line);

    if(line.size() != 0){
        ss.clear();
        ss.str(line);
        while(ss>>temp){
            val.push_back(temp);
        }

    }
    wall_set = val[0];
    paint_set = val[1];
    guard_set = val[2];

    //number of walls...
    std::getline(infile,line);
    ss.clear();
    ss.str(line);
    while(ss>>temp){
        noOfwall = temp;
    }

    //Stored the x,y co-ordinates of th wall corners,paintings and guard positions and ranks as vectors of vectors
    std::vector<std::vector<int> > wall_setVector,paint_setVector,guard_setVector;


    //returns the wall set x,y co-ordinates...
    std::vector< std::vector<int> > get_wallVector(){

        for(int i = 0; i < noOfwall; ++i){
            std::vector<int> inner_vec;
            size_t f;

            std::getline(infile,line);

            if((line.find("s")) != std::string::npos){
                f = line.find("s");
                line.erase(f, std::string("s").length());
            }else{
                f = line.find("c");
                line.erase(f, std::string("c").length());
            }


            if(line.size() != 0){

                ss.clear();
                ss.str(line);
                while(ss>>temp){
                    inner_vec.push_back(temp);
                }
            }

            std::cout<<std::endl;

            wall_setVector.push_back(inner_vec);

        }
        return wall_setVector;
    }


    //debugging purposes....i will attach a test case txt file

   /* for(std::vector< std::vector<int> >::iterator it = wall_setVector.begin();it != wall_setVector.end();++it){
        for(std::vector<int>::iterator jt = it->begin(); jt != it->end(); ++jt){
            std::cout<<*jt<<" ";
        }
        std::cout<<std::endl;
    } */


    //-------------paintings function-----------
    std::vector< std::vector<int> > get_paintingVector(){

        for(int i = 0; i < paint_set; ++i){
            std::vector<int> inner_vec;

            std::getline(infile,line);
            ss.clear();
            ss.str(line);
            while(ss>>temp){
                inner_vec.push_back(temp);
            }

            paint_setVector.push_back(inner_vec);

        }
        return paint_setVector;

    }


   /* for(std::vector< std::vector<int> >::iterator it = paint_setVector.begin();it != paint_setVector.end();++it){
        for(std::vector<int>::iterator jt = it->begin(); jt != it->end(); ++jt){
            std::cout<<*jt<<" ";
        }
        std::cout<<std::endl;
    } */



    //------Guards function--------
    std::vector< std::vector<int> > get_paintingVector(){

        for(int i = 0; i < guard_set; ++i){
            std::vector<int> inner_vec;

            std::getline(infile,line);
            ss.clear();
            ss.str(line);
            while(ss>>temp){
                inner_vec.push_back(temp);
            }

            guard_setVector.push_back(inner_vec);

        }
        return guard_setVector;
    }


    /*for(std::vector< std::vector<int> >::iterator it = guard_setVector.begin();it != paint_setVector.end();++it){
        for(std::vector<int>::iterator jt = it->begin(); jt != it->end(); ++jt){
            std::cout<<*jt<<" ";
        }
        std::cout<<std::endl;
    } */


	  
}