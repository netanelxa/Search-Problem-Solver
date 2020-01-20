//
// Created by netanel on 20/01/2020.
//

#include "MatrixBuilder.h"

vector<State<Point>*> MatrixBuilder::build(string line) {
    line.erase(line.rfind(',') + 3, line.length() - line.rfind(',') + 3);
    string x = line.substr(line.rfind('\n') + 1, line.rfind(',') - line.rfind('\n') - 1);
    string y = line.substr(line.rfind(',') + 1, line.length() - line.rfind(','));
    Point *exitPoint = new Point(stoi(x), stoi(y));
    line.erase(line.rfind('\n'), line.length() - line.rfind('\n') + 1);
    x = line.substr(line.rfind('\n') + 1, line.rfind(',') - line.rfind('\n') - 1);
    y = line.substr(line.rfind(',') + 1, line.length() - line.rfind(','));
    Point *startPoint = new Point(stoi(x), stoi(y));
    line.erase(line.rfind('\n') + 1, line.length() - line.rfind('\n') + 1);
    size_t rows = std::count(line.begin(), line.end(), '\n');
    int cols = 0;
    for (int i = 0; i < line.find('\n'); i++) {
        if (line[i] == ',')
            cols++;
    }
    string **matrix = new string *[rows + 2];
    for (int i = 0; i <= rows; ++i)
        matrix[i] = new string[cols + 2];
    int i = 0;
    int j = 0;
    int k = 0;
    string temp = "";
    while (i <= cols) {
        int flag = 0;
        while (line[k] != ',') {
            flag = 0;
            if (line[k] == ' ')
                k++;
            temp += line[k];
            k++;
            if (line[k] == '\n') {
                flag = 1;
                matrix[i][j] = temp;
                j = 0;
                i++;
                break;
            }
        }
        if (flag == 0)
            matrix[i][j] = temp;

        temp = "";
        if (line[k] == ',')
            j++;
        if (i == cols + 1 && j == 0)
            break;
        k++;
    }
    vector<State<Point>*> StateVec;
    cout << "From Here" << endl;
    for (int i = 0; i <= cols; i++) {
        for (int j = 0; j < rows; j++) {
            auto *p=new Point(i,j);
            State<Point> *x = new State<Point>(stod(matrix[i][j]),p);
            StateVec.push_back(x);
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete[] matrix;
    return StateVec;
}
