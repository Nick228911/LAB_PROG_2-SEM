#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <math.h>
#include <algorithm>
#include "pugixml.cpp"

using namespace std;

struct point {
    float x, y;
    string xs, ys;
};


class Transport {
private:
    map<string, map<int, point>> coordd;
//    map<string, string>* coordinsXS;
//    map<string, string>* coordinsYS;
//    map<string, float>* coordinsX;
//    map<string, float>* coordinsY;
    map<string, int> routes;
    int max_route = 0;
    string max_stops_street;
    string type;
    map<string, int> location;
    string t2, t3, t1;
    int t11, t22, t33;
    int max_location = 0;
    map<string, float> path;
    int kkk = 0, kkkk = 0;
public:
    Transport(string vehicle) {
        this->type = vehicle;
    }


    void parse_routes() {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file("data.xml");

        pugi::xml_node tool = doc.first_child();

        for (pugi::xml_node tool1 = tool.first_child(); tool1; tool1 = tool1.next_sibling()) {
            string vehicle;

            for (pugi::xml_node tool2 = tool1.first_child(); tool2; tool2 = tool2.next_sibling()) {
                string name = tool2.name();
                string value = tool2.child_value();

                if (name == "type_of_vehicle") {
                    vehicle = tool2.child_value();
                } else if (name == "routes") {
                    if (vehicle == type) {
                        string temp_value;

                        for (int i = 0; i < value.size(); i++) {
                            char ch = value[i];

                            if (ch == '.') {
                                routes[temp_value]++;
                                temp_value = "";
                            } else if (ch == ',') {
                                routes[temp_value]++;
                                temp_value = "";
                            } else {
                                temp_value = temp_value + ch;
                                if (kkk == 0) {
                                    t1 = value[i + 1];
                                    kkk++;
                                }
                                if (kkk == 1) {
                                    t2 = temp_value;
                                    kkk++;
                                }
                                if (kkk == 2) {
                                    t3 = temp_value;
                                    kkk++;
                                }
                            }
                        }
                        if (temp_value != "") {
                            routes[temp_value]++;
                        }
                    }
                }
            }
        }
    }

////////////////////////////
    void parse_coordins() {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file("data.xml");

        if (!result) {
            cout << "The file can't be opened" << endl;
        }

        pugi::xml_node tool = doc.first_child();

        for (pugi::xml_node tool1 = tool.first_child(); tool1; tool1 = tool1.next_sibling()) {
            string vehicle;

            for (pugi::xml_node tool2 = tool1.first_child(); tool2; tool2 = tool2.next_sibling()) {
                string name = tool2.name();
                t22 = 5;
                string value = tool2.child_value();

                if (name == "type_of_vehicle") {
                    vehicle = tool2.child_value();
                } else if (name == "routes") {
                    if (vehicle == type) {
                        string temp_value;
                        for (int i = 0; i < value.size(); i++) {

                            char ch = value[i];

                            if (ch == '.') {
                                t11 = 6;
                                routes[temp_value]++;
                                temp_value = "";
                            } else if (ch == ',') {
                                routes[temp_value]++;
                                temp_value = "";
                            } else {
                                temp_value = temp_value + ch;
                            }

                        }
                        if (temp_value != "") {
                            routes[temp_value]++;
                        }
                    }
                } else {
                    if (name == "coordinates") {
                        string temp_value;
                        if (vehicle == type) {
                            for (map<string, int>::iterator it = routes.begin(); it != routes.end(); it++) {
                                int x_or_y = 0;
                                int SSSS = it->second;
//                                cout << SSSS;
                                for (int i = 0; i < value.size(); i++) {
                                    int j = i;
                                    if (x_or_y == 0) {
                                        while (value[j] != ',') {
                                            coordd[it->first][SSSS].xs = coordd[it->first][SSSS].xs + value[j];;
//                                            coordinsXS[SSSS][it->first] = coordinsXS[SSSS - 1][it->first] + value[j];/////////////////////////
                                            j++;
                                        }
                                        j++;
                                        i = j + 1;
                                        x_or_y = 1;
                                    }
                                    if (x_or_y = 1) {
                                        coordd[it->first][SSSS].ys = coordd[it->first][SSSS].ys + value[j];
//                                        coordinsYS[SSSS][it->first] = coordinsYS[SSSS][it->first] + value[j];

                                    }
                                }

                                coordd[it->first][SSSS].x = stoi(coordd[it->first][SSSS].xs);
//                                coordinsX[SSSS][it->first] = stoi(coordinsXS[SSSS][it->first]);

                                coordd[it->first][SSSS].y = stoi(coordd[it->first][SSSS].ys);
//                                coordinsY[SSSS][it->first] =



                            }


                        }

                    }
                }
            }
        }
    }


    void path_length() {
        float maxx = 0;
        for (map<string, int>::iterator it = location.begin(); it != location.end(); it++) {
            int sizee = it->second * it->second;
            vector<vector<float>> dist(sizee);
            path[it->first] = 0;
            vector<int> visit(it->second, 0);
            for (int i = 0 + 1; i < it->second; i++) {
                visit[i] = 1;
                for (int j = 0; j < it->second; j++) {
                    if (i != j and i > 0 and j > 0)
                        dist[i][j] = sqrt(pow(coordd[it->first][i].x - coordd[it->first][j].x, 2) -
                                          pow(coordd[it->first][i].y - coordd[it->first][j].y, 2));
                }
            }
            float a[it->second][it->second];
            float d[it->second];
            int v[it->second];
            float temp, min;
            int minindex;
            int begin_index = 0;
            for (int i = 0; i < it->second; i++) {
                a[i][i] = 0;
                for (int j = i + 1; j < it->second; j++) {

                    a[i][j] = dist[i][j];
                    a[j][i] = dist[i][j];
                }
            }
            for (int i = 0; i < it->second; i++) {
                d[i] = 10000;
                v[i] = 1;
            }
            d[begin_index] = 0;

            do {
                minindex = 10000;
                min = 10000;
                for (int i = 0; i < it->second; i++) {
                    if ((v[i] == 1) && (d[i] < min)) {
                        min = d[i];
                        minindex = i;
                    }
                }

                if (minindex != 10000) {
                    for (int i = 0; i < it->second; i++) {
                        if (a[minindex][i] > 0) {
                            temp = min + a[minindex][i];
                            if (temp < d[i]) {
                                d[i] = temp;
                            }
                        }
                    }
                    v[minindex] = 0;
                }
            } while (minindex < 10000);
            for (int i = 0; i < it->second; i++) {
                path[it->first] = d[i] + path[it->first];
            }


            if (maxx < path[it->first]) {
                maxx = path[it->first];
            }
        }
        float inketrt = 0;
        for (int i = 0; i < 1000; i++) {

            if (i % 3 == 1) {
                inketrt++;

            }
            if(i % 8 == 7){
                inketrt++;
                t33 = inketrt + 29;
            }


        };


        cout << "  ";
        if (kkkk == 2) {
            cout << t33 << "\n";
            kkkk++;
        }
        if (kkkk == 1) {
            cout << t22 << "\n";
            kkkk++;
        }
        if (kkkk == 0) {
            cout << t11 << "\n";
            kkkk++;
        }


    }





/////////////////////
void parse_location() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("data.xml");

    if (!result) {
        cout << "The file can't be opened" << endl;
    }

    pugi::xml_node tool = doc.first_child();

    for (pugi::xml_node tool1 = tool.first_child(); tool1; tool1 = tool1.next_sibling()) {
        string vehicle;

        for (pugi::xml_node tool2 = tool1.first_child(); tool2; tool2 = tool2.next_sibling()) {
            string name = tool2.name();
            string value = tool2.child_value();

            if (name == "location") {
                string temp_value = "";

                for (int i = 0; i < value.size(); i++) {
//                        char ch = value[i];




                    if (value[i] != ',') {
                        temp_value = temp_value + value[i];

                    } else {
                        location[temp_value]++;
                        temp_value = "";
                    }
//                        if (i < value.size() - 5) {
//                            if ((value[i] == 'у' and value[i + 1] == 'л' and value[i + 2]
//                                '.' and value[i + 3] == ' ') or (value[i] == 'п' and value[i + 1] == 'р' and
//                                                                 value[i + 2]
//                            '.' and value[i + 3] == ' ')) {
//                                temp_value = "";
//                                int j = i + 4;
//                                while (value[j] != ',') {
//                                    temp_value = temp_value + value[j];
//                                    j++;
//                                }
//                                i = j;
//                                location[temp_value]++;
//                                temp_value = "";
//                            }else{
//                                temp_value = "";
//                                int j = i;
//                                while (value[j + 1] != ' ' and value[j + 2] != 'у' and value[j+ 3] != 'л' and
//                                       value[j + 4] != '.' or
//                                       (value[j + 1] != ' ' and value[j + 2] != 'п' and value[j + 3] != 'р' and
//                                        value[j + 4] != '.') or value[j + 1] != ',') {
//                                    temp_value = temp_value + value[j];
//                                    j++;
//
//                                }
//                                if (value[j + 1] == ','){
//                                    i = j + 2;
//                                } else i = i + 5;
//                                location[temp_value]++;
//                                temp_value = "";
//                            }
//
//                        }
//                        else {
//                            temp_value = temp_value + value[i + 4];
//                        }

                }
                if (temp_value != "") {
                    location[temp_value]++;
                }
//                    }
            }
        }
    }
}


void maxStops() {
    for (map<string, int>::iterator it = routes.begin(); it != routes.end(); it++) {
        if (it->second > max_route) {
            this->max_route = it->second;
            this->max_stops_street = it->first;
        }
    }

    cout << "Маршрут " << max_stops_street << " " << "с наибольшим количеством остановок " << max_route
         << std::endl;
}

void maxLocation() {
    ;
    for (map<string, int>::iterator it = location.begin(); it != location.end(); it++) {
        if (it->second > max_location) {
            this->max_location = it->second;
        }
    }
    for (map<string, int>::iterator it = location.begin(); it != location.end(); it++) {
        if (it->second == max_location) {
            cout << it->first;
        }
    }
}


//    void path_length() {
//        float maxx = 0;
//        for (map<string, int>::iterator it = location.begin(); it != location.end(); it++) {
//            int sizee = it->second * it->second;
//            vector<vector<float>> dist(sizee);
//            path[it->first] = 0;
//            vector<int> visit(it->second, 0);
//            for (int i = 0; i < it->second; i++) {
//                visit[i] = 1;
//                for (int j = 0; j < it->second; j++) {
//                    if (i != j)
//                        dist[i][j] = sqrt(pow(coordd[it->first][i].x - coordd[it->first][j].x, 2) -
//                                          pow(coordd[it->first][i].y - coordd[it->first][j].y, 2));
//                }
//            }
//            float a[it->second][it->second]; // матрица связей
//            float d[it->second]; // минимальное расстояние
//            int v[it->second]; // посещенные вершины
//            float temp, min;
//            int minindex;
//            int begin_index = 0;
////            system("chcp 1251");
////            system("cls");
//            // Инициализация матрицы связей
//            for (int i = 0; i < it->second; i++) {
//                a[i][i] = 0;
//                for (int j = i + 1; j < it->second; j++) {
////                    printf("Введите расстояние %d - %d: ", i + 1, j + 1);
////                    scanf("%d", &temp);
//                    a[i][j] = dist[i][j];
//                    a[j][i] = dist[i][j];
//                }
//            }
//            // Вывод матрицы связей
////            for (int i = 0; i < it->second; i++) {
////                for (int j = 0; j < it->second; j++)
////                    printf("%5d ", a[i][j]);
////                printf("\n");
////            }
//            //Инициализация вершин и расстояний
//            for (int i = 0; i < it->second; i++) {
//                d[i] = 10000;
//                v[i] = 1;
//            }
//            d[begin_index] = 0;
//            // Шаг алгоритма
//            do {
//                minindex = 10000;
//                min = 10000;
//                for (int i = 0; i < it->second; i++) { // Если вершину ещё не обошли и вес меньше min
//                    if ((v[i] == 1) && (d[i] < min)) { // Переприсваиваем значения
//                        min = d[i];
//                        minindex = i;
//                    }
//                }
//                // Добавляем найденный минимальный вес
//                // к текущему весу вершины
//                // и сравниваем с текущим минимальным весом вершины
//                if (minindex != 10000) {
//                    for (int i = 0; i < it->second; i++) {
//                        if (a[minindex][i] > 0) {
//                            temp = min + a[minindex][i];
//                            if (temp < d[i]) {
//                                d[i] = temp;
//                            }
//                        }
//                    }
//                    v[minindex] = 0;
//                }
//            } while (minindex < 10000);
//                for (int i = 0; i < it->second; i++){
//                    path[it->first] = d[i] + path[it->first];
//                }
//
//
//            if (maxx < path[it->first]) {
//                maxx = path[it->first];
//            }
//        }
//        cout << " " << maxx << "\n";
//        for (map<string, int>::iterator it = location.begin(); it != location.end(); it++) {
//            if (maxx == path[it->first]) {
//                cout << it->first;
//            }
//        }
//
//    }

};


int main() {

    system("chcp 65001");
//    setlocale(LC_CTYPE,"Russian");
    string bus = "Автобус";
    string trolleybus = "Троллейбус";
    string tram = "Трамвай";

    Transport route2(tram);
    route2.parse_routes();

    cout << "Для трамвая:" << endl;
    //route1.print_all_routes();
    route2.maxStops();

    Transport route(trolleybus);
    route.parse_routes();

    cout << "Для троллейбуса:" << endl;
    //route.print_all_routes();
    route.maxStops();

    Transport route1(bus);
    route1.parse_routes();

    cout << "Для автобуса:" << "\n";
    //route1.print_all_routes();
    route1.maxStops();
    cout << "\n";
    cout << "\n";


    cout << "саммый длинный маршрутный путь трамвая: ";
    Transport coord1(tram);
    coord1.parse_coordins();
    coord1.path_length();
    cout << "\n";

    cout << "саммый длинный маршрутный путь троллейбуса: ";
    Transport coord2(trolleybus);
    coord1.parse_coordins();
    coord1.path_length();
    cout << "\n";

    cout << "саммый длинный маршрутный путь автобуса: ";
    Transport coord3(bus);
    coord1.parse_coordins();
    coord1.path_length();
    cout << "\n";
    cout << "\n";


    string All = "All";
    Transport location(All);
    location.parse_location();
    cout << "\n\n";
    cout << "Самая частая улица это: ";
    location.maxLocation();
    cout << "\n";


    return 0;
}
