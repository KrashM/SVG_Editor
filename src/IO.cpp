#include "../headers/Rectangle.h"
#include "../headers/Circle.h"
#include "../headers/Line.h"
#include "../headers/IO.h"

#define SVGEXTENSION ".svg"

ShapeCollection IO::collection;
String IO::currentFile;

void IO::menu(){

    String command;

    while(true){

        cout << "> ";
        cin >> command;

        if(command == "exit") break;
        else if(command == "open") readFromFile();
        else if(command == "close");
        else if(command == "save") writeToFile();
        else if(command == "saveas");
        else if(command == "help");

        else if(command == "print") print();
        
        else if(command == "create") create();
        else if(command == "erase") erase();
        
        else if(command == "translate") translate();
        else if(command == "within") within();
        else if(command == "pointin") pointIn();
        else if(command == "areas") areas();
        else if(command == "pers") pers();

    }

}

void IO::writeToFile(){

    ofstream ofs(IO::currentFile.c_str(), ios::trunc);

    ofs << "<?xml version=\"1.0\" standalone=\"no\"?>\n"
        << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
        << "<svg>\n";
    for(size_t i = 0; i < IO::collection.size(); i++)
        IO::collection[i] -> serialize(ofs);
    ofs << "</svg>";

    ofs.close();
    cout << "Successfully saved the changes to " << IO::currentFile << '\n';

}

void IO::readFromFile(){

    cin >> IO::currentFile;

    String fileNameExtension = IO::currentFile.substring(IO::currentFile.length() - 4, strlen(SVGEXTENSION));

    if(fileNameExtension != SVGEXTENSION){

        cout << "File is not an svg file\n";
        return;

    }

    String type;
    ifstream ifs(IO::currentFile.c_str());

    const size_t bufferSize = 1024;
    char temp[bufferSize];
    ifs.getline(temp, bufferSize);
    ifs.getline(temp, bufferSize);
    ifs.getline(temp, bufferSize);

    while(true){

        while(ifs.get() != '<');
        ifs >> type;

        if(type == "rect"){
            
            Rectangle *rect = new Rectangle();
            rect -> deserialize(ifs);
            IO::collection.addShape(rect);
            delete rect;

        }
        else if(type == "circle"){
            
            Circle *circle = new Circle();
            circle -> deserialize(ifs);
            IO::collection.addShape(circle);
            delete circle;

        }
        else if(type == "line"){

            Line *line = new Line();
            line -> deserialize(ifs);
            IO::collection.addShape(line);
            delete line;

        }
        else if(type == "/svg>") break;
        
    }

    ifs.close();
    cout << "Successfully opened " << IO::currentFile << '\n';

}

void IO::print(){

    for(size_t i = 0; i < IO::collection.size(); i++)
        cout << i + 1 << ". " << IO::collection[i] -> toString() << '\n';

}
void IO::create(){

    String shape;

    cin >> shape;

    if(shape == "rectangle"){

        size_t x, y, width, height;
        String color;
        cin >> x >> y >> width >> height >> color;
        IO::collection.addShape(new Rectangle(x, y, width, height, color));

    }
    else if(shape == "circle"){
        
        size_t x, y, radius;
        String color;
        cin >> x >> y >> radius >> color;
        IO::collection.addShape(new Circle(x, y, radius, color));

    }
    else if(shape == "line"){
       
        size_t x1, y1, x2, y2;
        String color;
        cin >> x1 >> y1 >> x2 >> y2 >> color;
        IO::collection.addShape(new Line(x1, y1, x2, y2, color));

    }

    cout << "Successfully created " << shape << " (" << IO::collection.size() << ")\n";
    
}

void IO::erase(){

    size_t index;

    cin >> index;

    --index;

    if(IO::collection.size() <= index){

        cout << "There is no figure number " << index + 1 << "!\n";
        return;

    }

    collection.removeShape(index);
    cout << "Erased a circle (" << index + 1 << ")\n";
  
}

void IO::translate(){
    
    String input;

    cin >> input;

    cout << input << '\n';

    if(input.contains('=')){

        int index1 = input.find('=') + 1;
        input = String(input.substring(index1, input.length() - index1));

        String xTranslation;

        cin >> xTranslation;

        int index2 = xTranslation.find('=') + 1;
        xTranslation = String(xTranslation.substring(index2, xTranslation.length() - index2));

        for(size_t i = 0; i < IO::collection.size(); i++)
            IO::collection[i] -> translate(atof(input.c_str()), atof(xTranslation.c_str()));

        cout << "Translated all figures\n";

    }
    else{

        String xTranslation, yTranslation;

        cin >> yTranslation >> xTranslation;
        
        int indexX = xTranslation.find('=') + 1;
        int indexY = yTranslation.find('=') + 1;

        IO::collection[atoi(input.c_str())] -> translate(atof(xTranslation.c_str()), atof(yTranslation.c_str()));

        cout << "Translated figure at index: " << input << '\n';

    }

}

void IO::within(){

    String type;

    cin >> type;
    
    if(type == "rectangle"){

        double x, y, width, height;

        cin >> x >> y >> width >> height;
        
        for(size_t i = 0; i < IO::collection.size(); i++)
            if(IO::collection[i] -> isInsideRectangle(x, y, width, height))
                cout << i + 1 << ". " << IO::collection[i] -> toString() << '\n';

    }
    else if(type == "circle"){
        
        double x, y, radius;

        cin >> x >> y >> radius; 
        
        for(size_t i = 0; i < IO::collection.size(); i++)
            if(IO::collection[i] -> isInsideCircle(x, y, radius))
                cout << i + 1 << ". " << IO::collection[i] -> toString() << '\n';

    }

}

void IO::pointIn(){

    double x, y;

    cin >> x >> y;

    for(size_t i = 0; i < IO::collection.size(); i++)
        if(collection[i] -> isPointIn(x,y))
            cout << i + 1 << ". " << IO::collection[i] -> toString() << '\n';

}

void IO::areas(){

    for(size_t i = 0; i < IO::collection.size(); i++)
        cout << i + 1 << ". " << "Shape area: " << IO::collection[i] -> getArea() <<  '\n';

}

void IO::pers(){
    
    for(size_t i = 0; i < IO::collection.size(); i++)
        cout << i + 1 << ". " << "Shape per: " << IO::collection[i] -> getPer() <<  '\n';

}

/*

open test.svg
print
create rectangle 1000 1000 10 20 yellow
print
within circle 0 0 5
erase 2
erase 100
print
translate vertical=10 horizontal=100
print
save
exit

*/