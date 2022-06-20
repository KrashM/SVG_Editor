#pragma once

#include "ShapeCollection.h"

class IO{

    public:
        static void menu();

        static void writeToFile();
        static void readFromFile();

        static void print();
        static void create();
        static void erase();
        static void translate();
        static void within();
        static void pointIn();
        static void areas();
        static void pers();

    private:
        static ShapeCollection collection;
        static String currentFile;

};