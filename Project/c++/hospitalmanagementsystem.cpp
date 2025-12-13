#include <bits/stdc++.h>
using namespace std;

// ---------------- Patient Class ----------------
class Patient {
public:
    int id;
    string name;
    int age;
    string gender;
    string disease;
    string admitDate;
    string dischargeDate;
    double bill;

    Patient() {
        id = 0;
        bill = 0;
    }

    string serialize() {
        // id|name|age|gender|disease|admit|discharge|bill
        return to_string(id) + "|" + name + "|" + to_string(age) + "|" + gender + "|" + disease + "|" + admitDate + "|" + dischargeDate + "|" + to_string(bill);
    }

    static Patient deserialize(const string &line) {
        Patient p;
        stringstream ss(line);
        string temp;
        getline(ss, temp, '|'); p.id = stoi(temp);
        getline(ss, p.name, '|');
        getline(ss, temp, '|'); p.age = stoi(temp);
        getline(ss, p.gender, '|');
        getline(ss, p.disease, '|');
        getline(ss, p.admitDate, '|');
        getline(ss, p.dischargeDate, '|');
        getline(ss, temp, '|'); p.bill = stod(temp);
        return p;
    }

    void display() {
        cout << "ID: " << id << "\nName: " << name << "\nAge: " << age << "\nGender: " << gender
             << "\nDisease: " << disease << "\nAdmit Date: " << admitDate << "\nDischarge Date: " 
             << (dischargeDate.empty() ? "NA" : dischargeDate) << "\nBill: " << bill << "\n\n";
    }
};

// ---------------- Hospital Management ----------------
class Hospital {
private:
    vector<Patient> patients;
    const string fileName = "patients.txt";

public:
    Hospital() { loadFromFile(); }

    void loadFromFile() {
        patients.clear();
        ifstream in(fileName);
        if (!in) return;
        string line;
        while (getline(in, line)) {
            if (!line.empty())
                patients.push_back(Patient::deserialize(line));
        }
        in.close();
    }

    void saveToFile() {
        ofstream out(fileName);
        for (auto &p : patients)
            out << p.serialize() << "\n";
        out.close();
    }

    int generateId() {
        int maxId = 0;
        for (auto &p : patients)
            if (p.id > maxId) maxId = p.id;
        return maxId + 1;
    }

    void addPatient() {
        Patient p;
        p.id = generateId();
        cout << "Enter Name: "; cin >> ws; getline(cin, p.name);
        cout << "Enter Age: "; cin >> p.age;
        cout << "Enter Gender: "; cin >> p.gender;
        cout << "Enter Disease: "; cin >> ws; getline(cin, p.disease);
        cout << "Enter Admit Date (DD-MM-YYYY): "; cin >> ws; getline(cin, p.admitDate);
        p.dischargeDate = "";
        p.bill = 0;

        patients.push_back(p);
        saveToFile();
        cout << "\nPatient added with ID: " << p.id << "\n";
    }

    void searchPatient() {
        int pid;
        cout << "Enter Patient ID to search: ";
        cin >> pid;
        for (auto &p : patients) {
            if (p.id == pid) {
                cout << "\nPatient Details:\n";
                p.display();
                return;
            }
        }
        cout << "Patient not found!\n";
    }

    void dischargePatient() {
        int pid;
        cout << "Enter Patient ID to discharge: ";
        cin >> pid;

        for (auto &p : patients) {
            if (p.id == pid) {
                if (!p.dischargeDate.empty()) {
                    cout << "Patient already discharged on " << p.dischargeDate << "\n";
                    return;
                }
                cout << "Enter Discharge Date (DD-MM-YYYY): "; cin >> ws; getline(cin, p.dischargeDate);
                cout << "Enter Bill Amount: "; cin >> p.bill;
                saveToFile();
                cout << "Patient discharged successfully.\n";
                return;
            }
        }
        cout << "Patient not found!\n";
    }

    void listAllPatients() {
        cout << "\n--- All Patients ---\n";
        for (auto &p : patients) p.display();
    }
};

// ---------------- Main Function ----------------
int main() {
    Hospital hospital;
    int choice;

    while (true) {
        cout << "\n=== Hospital Management System ===\n";
        cout << "1. Add Patient\n";
        cout << "2. Search Patient\n";
        cout << "3. Discharge Patient\n";
        cout << "4. List All Patients\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: hospital.addPatient(); break;
            case 2: hospital.searchPatient(); break;
            case 3: hospital.dischargePatient(); break;
            case 4: hospital.listAllPatients(); break;
            case 5: cout << "Exiting... Goodbye!\n"; exit(0);
            default: cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
