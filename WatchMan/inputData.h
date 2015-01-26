#ifndef INPUTDATA_H
#define INPUTDATA_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


class inputData
{
    private:
	void readtext1();
        std::vector< std::vector<std::vector<int> > > get_wallSetVector();
        std::vector< std::vector<int> > get_paintVector();
        std::vector< std::vector<int> > get_guardVector();
        std::vector< std::vector<int> > get_wallNumberVector();

    public:
	inputData(std::string);
      
        virtual ~inputData();

	std::string fileName;
	std::fstream infile;

        std::vector<int>wall_EdgeArray;
        std::vector<int> get_wall_EdgeArray();

        int wallSet; 
        int painting;
        int guards;
        int wallNumber;
        std::vector<std::vector<int> > paint_setVector,guard_setVector;
	std::vector< std::vector<std::vector<int> > > wall_setVector;

        void set_wallSet(int);
        void set_painting(int);
        void set_guards(int);
        void set_wallNumber(int);

        int get_wallSet();
        int get_painting();
        int get_guards();
        int get_wallNumber();

        void print_wallSet(std::vector< std::vector<std::vector<int> > >);
        void print_paintSet(std::vector< std::vector<int> >);
        void print_guardSet(std::vector< std::vector<int> >);

	bool get_next_problem();
};

#endif // INPUTDATA_H
