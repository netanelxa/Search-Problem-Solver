//
// Created by netanel on 18/01/2020.
//
#include "MyClientHandler.h"

#define bufferlength 1024


void MyClientHandler::handleClient(int sockfd) {
    this->socknumber = sockfd;
    char buffer[1024] = {0};
    string line;
    string temp_buffer;
    vector<string> matrix_vec;
    // searchsolver = new OA<string, string, string>;
    cm = new FileCacheManager<string, string>();
    while (true) {
        memset(buffer, 0, bufferlength);
        int i = 0;
        read(socknumber, buffer, bufferlength);
        while (buffer[i] != '\0' && i < bufferlength) {
            line += buffer[i];
            i++;
        }
        i = 0;
        while (!isEnd(buffer)) {
            int i = 0;
            memset(buffer, 0, bufferlength);
            read(socknumber, buffer, 1024);
            while (buffer[i] != '\0' && i < bufferlength) {
                line += buffer[i];
                i++;
            }
        }
        cout << line << endl;
        MatrixBuild(line);
        if (cm->get(buffer) != "-1") {
            string n = cm->get(buffer);
            const char *nsend = n.c_str();
            send(this->socknumber, nsend, strlen(nsend), 0);
        } else {
            cout << buffer << endl;
            //       string answer = searchsolver->solve(buffer);
            //    cm->insert(buffer, answer);
            string n = cm->get(buffer);
            const char *nsend = n.c_str();
            send(this->socknumber, nsend, strlen(nsend), 0);
            // cout << cm->get(buffer) << endl;

        }
    }
    std::cout << socknumber << std::endl;
}


string MyClientHandler::MatrixBuild(string line) {
    line.erase(line.rfind(',') + 3, line.length() - line.rfind(',') + 3);
    string x = line.substr(line.rfind('\n') + 1, line.rfind(',') - line.rfind('\n') - 1);
    string y = line.substr(line.rfind(',') + 1, line.length() - line.rfind(','));
    exitPoint = new Point(stoi(x), stoi(y));
    line.erase(line.rfind('\n'), line.length() - line.rfind('\n') + 1);
    x = line.substr(line.rfind('\n') + 1, line.rfind(',') - line.rfind('\n') - 1);
    y = line.substr(line.rfind(',') + 1, line.length() - line.rfind(','));
    startPoint = new Point(stoi(x), stoi(y));
    line.erase(line.rfind('\n'), line.length() - line.rfind('\n') + 1);
    size_t rows = std::count(line.begin(), line.end(), '\n');
    int cols = 0;
    for (int i = 0; i < line.find('\n'); i++) {
        if (line[i] == ',')
            cols++;
    }
    double **matrix = new double *[rows];
    for (int i = 0; i < rows; ++i)
        matrix[i] = new double[cols];
    int i = 0;
    int j = 0;
    int k = 0;
    while (i <= cols) {
        if (line[k] == ' ')
            k++;
        matrix[i][j] = strod(line[k]);
        k++;
        if (line[k] == ',')
            j++;
        if (line[k] == '\n') {
            j = 0;
            i++;
        }
    }
    cout << "From Here" << endl;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++)
            std::cout << matrix[i][j] << " ";

        std::cout << std::endl;
    }

    for (int i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete[] matrix;
}


bool MyClientHandler::isEnd(string buffer) {
    int x = buffer.find("end");
    if (x < 0)
        return false;
    if (x >= 0) {
        buffer.erase(buffer.find("end"), 3);
        return true;
    }
}