#ifndef INPUTDATA_H
#define INPUTDATA_H
#include <iostream>
#include <vector>


class inputData
{
    public:
        inputData();
        void readtext1(std::string);

        virtual ~inputData();

        std::vector<int>wall_EdgeArray;
        std::vector<int> get_wall_EdgeArray();

        int wallSet; 
        int painting;
        int guards;
        int wallNumber;
        std::vector<std::vector<int> > wall_setVector,paint_setVector,guard_setVector;


        void set_wallSet(int);
        void set_painting(int);
        void set_guards(int);
        void set_wallNumber(int);

        int get_wallSet();
        int get_painting();
        int get_guards();
        int get_wallNumber();



        std::vector< std::vector<std::vector<int> > > get_wallSetVector(std::string);

        std::vector< std::vector<int> > get_paintVector(std::string);
        std::vector< std::vector<int> > get_guardVector(std::string);
        std::vector< std::vector<int> > get_wallNumberVector(std::string);

        void print_wallSet(std::vector< std::vector<std::vector<int> > >);
        void print_paintSet(std::vector< std::vector<int> >);
        void print_guardSet(std::vector< std::vector<int> >);





};

#endif // INPUTDATA_H
