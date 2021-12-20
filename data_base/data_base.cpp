#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class DataBase {
protected:

    string colums_students[6] = { "id", "surname", "name", "patronymic", "age", "class" };
    vector<int> ids_students;
    vector<string> surname_students;
    vector<string> name_students;
    vector<string> patronymic_students;
    vector<int> age_students;
    vector<string> group_students;

    string colums_subjects[2] = { "id", "name" };
    vector<int> ids_subjects;
    vector<string> name_subjects;

    string colums_appraisals[4] = { "id", "id_st", "id_it", "appr" };
    vector<int> ids_appraisals;
    vector<int> ids_students_appraisals;
    vector<int> ids_items_appraisals;
    vector<int> appraisals;

    void save() {
        ofstream fin1, fin2, fin3;
        fin1.open("Students.txt");
        fin2.open("Subjects.txt");
        fin3.open("Appraisals.txt");
        for (int i = 0; i < this->ids_students.size(); i++) {
            fin1 << ids_students[i] << " " << surname_students[i] << " " << name_students[i] << " " << patronymic_students[i] << " " << age_students[i] << " " << group_students[i] << endl;
        }
        for (int i = 0; i < this->ids_subjects.size(); i++) {
            fin2 << ids_subjects[i] << " " << name_subjects[i] << endl;
        }
        for (int i = 0; i < this->ids_appraisals.size(); i++) {
            fin3 << ids_appraisals[i] << " " << ids_students_appraisals[i] << " " << ids_items_appraisals[i] << " " << appraisals[i]<< endl;
        }
        fin1.close();
        fin2.close();
        fin3.close();
    }

public:
    
    DataBase() {
        ifstream fin1, fin2, fin3;
        fin1.open("Students.txt");
        fin2.open("Subjects.txt");
        fin3.open("Appraisals.txt");
        if (fin1.is_open() && fin2.is_open() && fin3.is_open()) {
            fin1.close();
            fin2.close();
            fin3.close();
            load_data_students("Students.txt");
            load_data_subjects("Subjects.txt");
            load_data_appraisals("Appraisals.txt");
        }
        else {
            ofstream fout1, fout2, fout3;
            fout1.open("Students.txt");
            fout2.open("Subjects.txt");
            fout3.open("Appraisals.txt");
            fout1.close();
            fout2.close();
            fout3.close();
        }
        

    }
    
    void set_data_students(string surname, string name, string patronymic, int age, string group) {
        int id;
        if (this->ids_students.size()) {
            id = this->ids_students[this->ids_students.size() - 1] + 1;

        }
        else {
            id = 0;
        }
        this->ids_students.push_back(id);
        this->surname_students.push_back(surname);
        this->name_students.push_back(name);
        this->patronymic_students.push_back(patronymic);
        this->age_students.push_back(age);
        this->group_students.push_back(group);
        save();
    }

    void set_data_subjects(string name) {
        int id;
        if (this->ids_subjects.size()) {
            id = this->ids_subjects[this->ids_subjects.size() - 1] + 1;
        }
        else {
            id = 0;
        }
        this->ids_subjects.push_back(id);
        this->name_subjects.push_back(name);
        save();

    }

    void set_data_appraisals(int ids_students, int ids_items, int appraisals) {
        int id;
        if (this->ids_appraisals.size()) {
            id = this->ids_appraisals[this->ids_appraisals.size() - 1] + 1;
        }
        else {
            id = 0;
        }
        this->ids_appraisals.push_back(id);
        this->ids_students_appraisals.push_back(ids_students);
        this->ids_items_appraisals.push_back(ids_items);
        this->appraisals.push_back(appraisals);
        save();

    }

    void load_data_students(string s) {
        ifstream test;
        test.open(s.c_str());
        string s1;
        int count = 0;
        if (test.is_open()) {
            while (!test.eof()) {
                test >> s1;
                count++;
            }
            if (s1 != "") {
                if (count % 5 == 0) {
                    ifstream fin;
                    fin.open(s.c_str());
                    for (int i = 0; i < count / 5; i++) {
                        string surname, name, patronymic, group;
                        int age;
                        fin >> surname >> name >> patronymic >> age >> group;
                        set_data_students(surname, name, patronymic, age, group);
                    }
                    fin.close();
                }
                else {
                    cout << "can't read file with students" << endl;
                }
            }
        }
        else {
            cout << "invalid path" << endl;
        }
        test.close();
        save();

    }

    void load_data_subjects(string s) {
        ifstream test;
        test.open(s);
        if (test.is_open()) {
            int count = 0;
            while (!test.eof()) {
                string s;
                test >> s;
                if (s != "") {
                    set_data_subjects(s);
                }
            }
        }
        else {
            cout << "invalid path" << endl;
        }
        test.close();
        save();

    }

    void load_data_appraisals(string s1) {
        ifstream test;
        test.open(s1);
        int count = 0;
        string s="";
        if (test.is_open()) {
            while (!test.eof()) {
                
                test >> s;
                count++;
            }
            if(s!=""){
                if (count % 5 == 0) {
                
                        ifstream fin;
                        fin.open(s1);
                        for (int i = 0; i < count / 5; i++) {
                            string surname, name, pathronimic, subject;
                            int ap;
                            fin >> surname >> name >> pathronimic >> subject >> ap;
                            int id = -1;
                            int ids_s = -1;
                            for (int i = 0; i < ids_students.size(); i++) {
                                if (name == this->name_students[i] && surname == this->surname_students[i] && pathronimic == this->patronymic_students[i]) {
                                    id = this->ids_students[i];
                                    break;
                                }

                            }
                            for (int i = 0; i < this->ids_subjects.size(); i++) {
                                if (name_subjects[i] == subject) {
                                    ids_s = this->ids_subjects[i];
                                }
                            }
                            if (id != -1 && ids_s != -1) {
                                set_data_appraisals(id, ids_s, ap);
                            }

                        }
                }else {
                        cout << "can't read file with appraisals" << endl;

                }
            }
        }
        else {
            cout << "invalid path" << endl;
        }
        save();

    }

    void clear() {
        ids_students.clear();
        surname_students.clear();
        name_students.clear();
        patronymic_students.clear();
        age_students.clear();
        group_students.clear();

        ids_subjects.clear();
        name_subjects.clear();

        ids_appraisals.clear();
        ids_students_appraisals.clear();
        ids_items_appraisals.clear();
        appraisals.clear();
        save();

    }

    void view_students() {
        for (int i = 0; i < 6; i++) {
            if (i == 0 || i == 4 || i == 5) {
                cout.setf(ios::left);
                cout.width(5);
            }
            else {
                cout.setf(ios::left);
                cout.width(30);
            }
            cout << colums_students[i];
        }
        cout << endl;
        for (int i = 0; i < this->ids_students.size(); i++) {
            cout.setf(ios::left);
            cout.width(5);
            cout << this->ids_students[i];
            cout.setf(ios::left);
            cout.width(30);
            cout << this->surname_students[i];
            cout.setf(ios::left);
            cout.width(30);
            cout << name_students[i];
            cout.setf(ios::left);
            cout.width(30);
            cout << patronymic_students[i];
            cout.setf(ios::left);
            cout.width(5);
            cout << this->age_students[i];
            cout.setf(ios::left);
            cout.width(5);
            cout << this->group_students[i];
            cout << endl;
        }
    }

    void view_subjects() {
        for (int i = 0; i < 2; i++) {
            cout.setf(ios::left);
            if (i == 0 || i == 4 || i == 5) {
                cout.width(5);
            }
            else {
                cout.width(20);
            }
            cout << colums_subjects[i];
        }
        cout << endl;
        for (int i = 0; i < this->ids_subjects.size(); i++) {
            cout.setf(ios::left);
            cout.width(5);
            cout << this->ids_subjects[i];
            cout.setf(ios::left);
            cout.width(20);
            cout << name_subjects[i];
            cout << endl;
        }
    }
    void view_appraisals() {
        for (int i = 0; i < 4; i++) {
            cout.setf(ios::left);
            cout.width(10);
            cout << colums_appraisals[i];
        }
        cout << endl;
        for (int i = 0; i < ids_appraisals.size(); i++) {
            cout.setf(ios::left);
            cout.width(10);
            cout << ids_appraisals[i];

            cout.setf(ios::left);
            cout.width(10);
            cout << ids_students_appraisals[i];

            cout.setf(ios::left);
            cout.width(10);
            cout << ids_items_appraisals[i];

            cout.setf(ios::left);
            cout.width(10);
            cout << appraisals[i];
            cout << endl;
        }
    }

    void get_sr_ball() {
        ofstream fout;
        fout.open("C:/Users/Default/Desktop/output.txt");
        for (int i = 1; i < 4; i++) {
            fout.setf(ios::left);
            fout.width(30);
            fout << colums_students[i];
            cout.setf(ios::left);
            cout.width(30);
            cout << colums_students[i];
        }
        for (int i = 0; i < ids_subjects.size();i++) {
            fout.setf(ios::left);
            fout.width(30);
            fout << name_subjects[i];
            cout.setf(ios::left);
            cout.width(30);
            cout << name_subjects[i];
        }
        fout << endl;
        cout << endl;
        for (int i = 0; i < ids_students.size(); i++) {
            vector<int> sum(name_subjects.size()), count(name_subjects.size());
            for (int j = 0; j < ids_appraisals.size(); j++) {
                if (ids_students_appraisals[j] == ids_students[i]) {
                    sum[ids_items_appraisals[j]] += appraisals[j];
                    count[ids_items_appraisals[j]] += 1;
                }
            }
            fout.setf(ios::left);
            fout.width(30);
            fout << surname_students[i];
            fout.setf(ios::left);
            fout.width(30);
            fout << name_students[i];
            fout.setf(ios::left);
            fout.width(30);
            fout << patronymic_students[i];
            for (int j = 0; j < name_subjects.size(); j++) {
                fout.setf(ios::left);
                fout.width(30);
                if (count[j] != 0) {
                    fout << 1.0 * int(1.0 * 100 * sum[j] / count[j]) / 100;
                }
                else {
                    fout << "-";
                }
            }
            fout << endl;
            cout.setf(ios::left);
            cout.width(30);
            cout << surname_students[i];
            cout.setf(ios::left);
            cout.width(30);
            cout << name_students[i];
            cout.setf(ios::left);
            cout.width(30);
            cout << patronymic_students[i];
            for (int j = 0; j < name_subjects.size(); j++) {
                cout.setf(ios::left);
                cout.width(30);
                if (count[j] != 0) {
                    cout << 1.0 * int(1.0 * 100 * sum[j] / count[j]) / 100;
                }
                else {
                    cout << "-";
                }
            }
            cout << endl;
        }
        fout.close();
        cout << "was saved to 'C:/Users/Default/Desktop/output.txt'" << endl;
    }
};

void print_info() {
    cout << "help - getting list of commands" << endl;
    cout << "clear - delete all data" << endl;
    cout << "stop - stop work of programm" << endl;
    cout << "load_data_students <path> - getting data of students from file" << endl;
    cout << "load_data_subjects <path> - getting data of subjects from file" << endl;
    cout << "load_data_appraisals <path> - getting data of appraisals from file" << endl;
    cout << "view_students - getting all data about students" << endl;
    cout << "view_subjects - getting all data about subjects" << endl;
    cout << "view_appraisals - getting all data about appraisals" << endl;
    cout << "get_sr_ball - getting average ball" << endl;

}
int main()
{

    DataBase *data_base = new DataBase();
    string s;
    while (true) {
        getline(cin, s);
        if (s == "help") {
            print_info();
            continue;
        }
        if (s == "stop") {
            return 0;
        }
        if (s.find("load_data_students") != -1) {
            s = s.substr(s.find(' ')+1);
            data_base->load_data_students(s);
            continue;
            
        }
        if (s.find("load_data_subjects") != -1) {
            s = s.substr(s.find(' ') + 1);
            data_base->load_data_subjects(s);
            continue;

        }
        if (s.find("load_data_appraisals") != -1) {
            s = s.substr(s.find(' ') + 1);
            data_base->load_data_appraisals(s);
            continue;

        }
        if (s == "clear") {
            data_base->clear();
            continue;
        }

        if (s.find("view_students") != -1) {
            data_base->view_students();
            continue;
        }

        if (s.find("view_subjects") != -1) {
            data_base->view_subjects();
            continue;
        }

        if (s.find("view_appraisals") != -1) {
            data_base->view_appraisals();
            continue;
        }
        if (s == "get_sr_ball") {
            data_base->get_sr_ball();
            continue;

        }

        cout << "wrong command" << endl;
        cout << "write 'help' to get instruction" << endl;
    }
}