//
// Created by netanel on 20/01/2020.
//

#include "MatrixBuilder.h"
#include <mutex>
MatrixBuilder::MatrixBuilder(size_t rows, int cols) {
    this->rows = rows;
    this->cols = cols;
}


State<Point> ***MatrixBuilder::build(string line) {

     line.erase(line.rfind('e'), line.length() - line.rfind('e'));
    string x = line.substr(line.rfind(',') + 1, line.rfind('\n') - line.rfind(',') - 1);
    line.erase(line.rfind(',') + 1, line.length() - line.rfind(',') + 1);
    string y = line.substr(line.rfind('\n') + 1, line.length() - line.rfind('\n') - 2);
    Point *exitPoint = new Point(stoi(x), stoi(y));
    line.erase(line.rfind('\n'), line.length() - line.rfind('\n'));
    x = line.substr(line.rfind(',') + 1, line.rfind('\n') - line.rfind(',') - 1);
    line.erase(line.rfind(',') + 1, line.length() - line.rfind(',') + 1);
    y = line.substr(line.rfind('\n') + 1, line.length() - line.rfind('\n') - 2);
    Point *startPoint = new Point(stoi(x), stoi(y));
    line.erase(line.rfind('\n') + 1, line.length() - line.rfind('\n') + 1);
    State<Point> ***matrix = new State<Point> **[rows + 2];
    for (int i = 0; i <= rows; ++i)
        matrix[i] = new State<Point> *[cols + 2];
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
            if (line[k] == '\n' && temp.length() > 0) {
                flag = 1;
                auto *p = new Point(i, j);
                matrix[i][j] = new State<Point>(stod(temp), p);
                j = 0;
                i++;
                break;
            }
        }
        if (flag == 0 && temp.length() > 0) {
            auto *p = new Point(i, j);
            matrix[i][j] = new State<Point>(stod(temp), p);
        }
        temp = "";
        if (line[k] == ',')
            j++;
        if (i == cols + 1 && j == 0)
        break;
        k++;
    }
    double startCost = matrix[startPoint->getX()][startPoint->getY()]->getCost();
    this->setInitalState(new State<Point>(startCost, startPoint));
    double endCost = matrix[exitPoint->getX()][exitPoint->getY()]->getCost();
    this->setGoalState(new State<Point>(endCost, exitPoint));
    this->current = matrix[0][0];
    this->matrix = matrix;
    return matrix;
}


void MatrixBuilder::setGoalState(State<Point> *endPoint) {
    this->goalState = endPoint;
}

void MatrixBuilder::setInitalState(State<Point> *startPoint) {
    this->initialState = startPoint;
}

State<Point> *MatrixBuilder::getInitialState() {
    return this->initialState;
}

bool MatrixBuilder::isGoalState(State<Point> *state) {
    if ((state->getState()->getX() == this->goalState->getState()->getX()) &&
        (state->getState()->getY() == this->goalState->getState()->getX()))
        return true;
    return false;
}


list<State<Point> *> MatrixBuilder::getAllPossibleStates(State<Point> *s, char type) {
    list<State<Point> *> adj;
    int x = s->getState()->getX();
    int y = s->getState()->getY();
    State<Point> *left = nullptr;
    State<Point> *right = nullptr;
    State<Point> *up = nullptr;
    State<Point> *down = nullptr;
    if (y - 1 >= 0 && matrix[x][y - 1]->getCost() >= 0) {
        left = matrix[x][y - 1];
    }
    if (y + 1 <= cols && matrix[x][y + 1]->getCost() >= 0) {
        right = matrix[x][y + 1];
    }
    if (x - 1 >= 0 && matrix[x - 1][y]->getCost() >= 0) {
        up = matrix[x - 1][y];
    }
    if (x + 1 <= rows && matrix[x + 1][y]->getCost() >= 0) {
        down = matrix[x + 1][y];
    }
    if (right != nullptr) {
        adj.push_back(right);
    }
    if (down != nullptr) {
        adj.push_back(down);
    }
    if (left != nullptr) {
        adj.push_back(left);
    }
    if (up != nullptr) {
        adj.push_back(up);
    }
    /*} else {
        if (down != nullptr) {
            adj.push_back(down);
        }
        if (right != nullptr) {
            adj.push_back(right);
        }
        if (left != nullptr) {
            adj.push_back(left);
        }
        if (up != nullptr) {
            adj.push_back(up);
        }
    }*/

    return adj;
}


void MatrixBuilder::setCurr(State<Point> *curr) {
    this->current = curr;
}

double MatrixBuilder::calculateHValue(State<Point> *cur) {
    int xCur = cur->getState()->getX();
    int yCur = cur->getState()->getY();
    int xGoal = this->getGoalState()->getState()->getX();
    int yGoal = this->getGoalState()->getState()->getY();
    double disMan = abs(xCur - xGoal) +
                    abs(yCur - yGoal);
    double total = disMan + cur->getCost() + cur->getParent()->getDistance();
    //cur->setHeur(total);
    return total;

}


void MatrixBuilder::initDis() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j]->initDis();
        }

    }
}

State<Point> *MatrixBuilder::getGoalState() {
    return this->goalState;
}


vector<vector<string>> MatrixBuilder::toString() {
    vector<vector<string>> all;
    vector<string> eachRow;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            string x = to_string(int(matrix[i][j]->getCost()));
            eachRow.emplace_back(x);
        }
        all.emplace_back(eachRow);
        eachRow.clear();
    }
    return all;

}