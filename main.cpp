#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
using namespace std;


// ========== ENUMERATIONS ========== //
enum Department {
    CARDIOLOGY,
    NEUROLOGY,
    ORTHOPEDICS,
    PEDIATRICS,
    EMERGENCY,
    GENERAL
};

enum RoomType {
    GENERAL_WARD,
    ICU,
    PRIVATE_ROOM,
    SEMI_PRIVATE
};

void displayMainMenu();
Department selectDepartment();
RoomType selectRoomType();



// ========== PATIENT CLASS ========== //
class Patient {
private:
    int id;
    string name;
    int age;
    string contact;
    stack<string> medicalHistory;
    queue<string> testQueue;
    bool isAdmitted;
    RoomType roomType;

public:
    Patient(int pid, string n, int a, string c){
      id= pid;
      name = n;
      age = a;
      contact =c;
      isAdmitted=0;
        roomType =GENERAL_WARD;
    }
    //Ask about loging in the medical history stack and ask should i write sentences?

    void admitPatient(RoomType type){
      isAdmitted = true;
      roomType = type;
        string roomTypes[4] = {"GENERAL_WARD","ICU","PRIVATE_ROOM","SEMI_PRIVATE"};
      string record = "Patient admitted in " + roomTypes[type];
        medicalHistory.push(record);
    }
    void dischargePatient() {
        isAdmitted = false;
        string dischargeRecord = "Patient is discharged";
        medicalHistory.push(dischargeRecord);
    }
    void addMedicalRecord(string record) {
        medicalHistory.push(record);
    }
    void requestTest(string testName) {
        testQueue.push(testName);
        medicalHistory.push("the patient should perform test: " + testName);
    }
    string performTest() {
        if (testQueue.empty()) {
            return"No tests should be performed";
        }
        else {
            medicalHistory.push("the patient performed test: " + testQueue.front());
            string test = testQueue.front();
            testQueue.pop();
            return test;
        }
    }
    void displayHistory() {
        stack<string> tempStack;
        while (!medicalHistory.empty()) {
            tempStack.push(medicalHistory.top());
            medicalHistory.pop();
        }

        while (!tempStack.empty()) {
            cout<<tempStack.top()<<endl;
            tempStack.pop();
        }
    }

    int getId() {
        return id;
    }
    string getName() {
        return name;
    }
    bool getAdmissionStatus() {
        return isAdmitted;
    }
};

// ========== DOCTOR CLASS ========== //
class Doctor {
private:
    int id;
    string name;
    Department department;
    queue<int> appointmentQueue;

public:
    Doctor(int did, string n, Department d){
        id = did;
        name = n;
        department = d;
    }

    void addAppointment(int patientId){
        appointmentQueue.push(patientId);
        cout << "Patient " << patientId << " Booked with " << name << endl;
    }

    int seePatient(){
        if(appointmentQueue.empty()){
            cout << "No patients in the queue for " << name << endl;
            return -1;
        }
        int patientId = appointmentQueue.front();
        appointmentQueue.pop();
        cout << name << " is now seeing patient " << patientId << endl;
        return patientId;
    }

    int getId(){
        return id;
    }

    string getName(){
        return name;
    }

    string getDepartment(){
        switch(department){
            case CARDIOLOGY: return "Cardiology";
            case NEUROLOGY: return "Neurology";
            case ORTHOPEDICS: return "Orthopedics";
            case PEDIATRICS: return "Pediatrics";
            case EMERGENCY: return "Emergency";
            case GENERAL: return "General";
            default: return "Unknown";
        }
    }
};

// ========== HOSPITAL CLASS ========== //
class Hospital {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    queue<int> emergencyQueue;
    int patientCounter;
    int doctorCounter;

public:
    Hospital()
    {
        patientCounter=0;
        doctorCounter=0;
    }

    int registerPatient(string name, int age, string contact)
    {
        patients.push_back(Patient(++patientCounter,name,age,contact));
        cout<<"Successfully added a new patient\n";
        cout<<"======================================"<<endl;
        return patientCounter;
    }
    ///////////////////////////
    int addDoctor(string name, Department dept)
    {
        doctors.push_back(Doctor(++doctorCounter,name,dept));
        cout<<"Successfully added a new doctor\n";
        cout<<"======================================"<<endl;
        return doctorCounter;
    }
    //////////////////////////
    void admitPatient(int patientId, RoomType type)
    {
        if(patients.empty())
        {
            cout<<"No patients found to display"<<endl;
        }
        else if(patientId<=patients.size()&&patientId>0)
        {
            if(patients[patientId-1].getAdmissionStatus())
            {
                cout<<patients[patientId-1].getName()<<" is already admitted to a room"<<endl;
            }
            else
            {
                patients[patientId-1].admitPatient(type);
                cout<<"Successfully addmited "<<patients[patientId-1].getName()<<" to a room"<<endl;
            }

        }
        else
        {
            cout<<"invalid Patient ID"<<endl;
        }
        cout<<"======================================"<<endl;
        return;

    }
    ///////////////////////
    void addEmergency(int patientId)
    {

        if(patientId<=patients.size()&&patientId>0)
        {
            cout<<"Successfully added "<<patients[patientId-1].getName()<<" to emeregency"<<endl;
            emergencyQueue.push(patientId);
        }
        else
        {
            cout<<"invalid Patient ID"<<endl;
        }
        cout<<"======================================"<<endl;
        return;

    }
    ///////////////////////
    int handleEmergency() {
        if (emergencyQueue.empty())
            {
                cout<<"No Emergency Found"<<endl;
                cout<<"======================================"<<endl;
                return -1;
            }

        int id = emergencyQueue.front();
        emergencyQueue.pop();
        cout << "Emergency Treated: " <<id<<" : "<< patients[id-1].getName() << endl;
        cout<<"======================================"<<endl;
        return id;
    }
    ///////////////////////
    void bookAppointment(int doctorId, int patientId)
    {
        if(doctorId>0&&doctorId<=doctors.size())
        {
            if(patientId<=patients.size()&&patientId>0)
            {
                doctors[doctorId-1].addAppointment(patientId);
                cout << "Successfully reserved appointment for Patient "<< patients[patientId-1].getName() << " with Doctor " << doctors[doctorId-1].getName() << endl;
            }
            else
            {
                cout<<"invalid Patient ID"<<endl;
            }
        }
        else
        {
                cout<<"invalid Doctor ID"<<endl;

        }
        cout<<"======================================"<<endl;
        return;
    }
    ///////////////////////
    void displayPatientInfo(int patientId)
    {
        if(patients.empty())
        {
            cout<<"No patients found to display"<<endl;
        }
        else if(patientId<=patients.size()&&patientId>0)
        {
            cout<<"patient ID: "<<patients[patientId-1].getId()<<endl;
            cout<<"patient Name: "<<patients[patientId-1].getName()<<endl;
            cout<<"patient Admission: "<<patients[patientId-1].getAdmissionStatus()<<endl;
            cout<<"patient Medical History:";
            patients[patientId-1].displayHistory();
            cout<<endl;
        }
        else
        {
            cout<<"this ID isn't Valid, Please enter a Valid ID"<<endl;
        }
        cout<<"======================================"<<endl;
        return;
    }
    ///////////////////////
    void displayDoctorInfo(int doctorId)
    {
        if(doctors.empty())
        {
            cout<<"No doctors found to display"<<endl;
        }
        else if(doctorId<=doctors.size()&&doctorId>0)
        {
            cout<<"Doctor ID: "<<doctors[doctorId-1].getId()<<endl;
            cout<<"Doctor Name: "<<doctors[doctorId-1].getName()<<endl;
            cout<<"Doctor Department: "<<doctors[doctorId-1].getDepartment()<<endl;

        }
        else
        {
            cout<<"this ID isn't Valid, Please enter a Valid ID"<<endl;
        }
        cout<<"======================================"<<endl;
        return;
    }
    ///////////////////////


};

void displayMainMenu() {
    cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====" << endl;
    cout << "1. Register Patient" << endl;
    cout << "2. Add Doctor" << endl;
    cout << "3. Admit Patient" << endl;
    cout << "4. Book Appointment" << endl;
    cout << "5. Add Emergency" << endl;
    cout << "6. Handle Emergency" << endl;
    cout << "7. Display Patient Information" << endl;
    cout << "8. Display Doctor Information" << endl;
    cout << "9. Exit" << endl;
    cout << "Please enter your choice (1-9): ";
}

Department selectDepartment() {
    int deptChoice;
    cout << "Select Department:" << endl;
    cout << "1. Cardiology" << endl;
    cout << "2. Neurology" << endl;
    cout << "3. Orthopedics" << endl;
    cout << "4. Pediatrics" << endl;
    cout << "5. Emergency" << endl;
    cout << "6. General" << endl;
    cout << "Enter choice (1-6): ";
    cin >> deptChoice;

    switch(deptChoice) {
        case 1: return CARDIOLOGY;
        case 2: return NEUROLOGY;
        case 3: return ORTHOPEDICS;
        case 4: return PEDIATRICS;
        case 5: return EMERGENCY;
        case 6: return GENERAL;
        default:
            cout << "Invalid choice, defaulting to General." << endl;
        return GENERAL;
    }
}

RoomType selectRoomType() {
    int roomChoice;
    cout << "Select Room Type:" << endl;
    cout << "1. General Ward" << endl;
    cout << "2. ICU" << endl;
    cout << "3. Private Room" << endl;
    cout << "4. Semi-Private" << endl;
    cout << "Enter choice (1-4): ";
    cin >> roomChoice;

    switch(roomChoice) {
        case 1: return GENERAL_WARD;
        case 2: return ICU;
        case 3: return PRIVATE_ROOM;
        case 4: return SEMI_PRIVATE;
        default:
            cout << "Invalid choice, defaulting to General Ward." << endl;
        return GENERAL_WARD;
    }
}


// ========== MAIN PROGRAM ========== //
int main() {
    Hospital hospital;
    int choice;

    do {
        displayMainMenu();
        cin >> choice;

        switch(choice) {
            case 1: { // Register Patient
                string name, contact;
                int age;
                cout << "Enter patient name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter patient age: ";
                cin >> age;
                cout << "Enter patient contact: ";
                cin.ignore();
                getline(cin, contact);

                int patientId = hospital.registerPatient(name, age, contact);
                cout << "Patient registered with ID: " << patientId << endl;
                break;
            }

            case 2: { // Add Doctor
                string name;
                cout << "Enter doctor name: ";
                cin.ignore();
                getline(cin, name);

                Department dept = selectDepartment();
                int doctorId = hospital.addDoctor(name, dept);
                cout << "Doctor added with ID: " << doctorId << endl;
                break;
            }

            case 3: { // Admit Patient
                int patientId;
                cout << "Enter patient ID to admit: ";
                cin >> patientId;

                RoomType room = selectRoomType();
                hospital.admitPatient(patientId, room);
                break;
            }

            case 4: { // Book Appointment
                int doctorId, patientId;
                cout << "Enter doctor ID: ";
                cin >> doctorId;
                cout << "Enter patient ID: ";
                cin >> patientId;

                hospital.bookAppointment(doctorId, patientId);
                break;
            }

            case 5: { // Add Emergency
                int patientId;
                cout << "Enter patient ID for emergency: ";
                cin >> patientId;

                hospital.addEmergency(patientId);
                break;
            }

            case 6: { // Handle Emergency
                hospital.handleEmergency();
                break;
            }

            case 7: { // Display Patient Information
                int patientId;
                cout << "Enter patient ID: ";
                cin >> patientId;

                hospital.displayPatientInfo(patientId);
                break;
            }

            case 8: { // Display Doctor Information
                int doctorId;
                cout << "Enter doctor ID: ";
                cin >> doctorId;

                hospital.displayDoctorInfo(doctorId);
                break;
            }

            case 9: { // Exit
                cout << "Thank you for using the Hospital Management System. Goodbye!" << endl;
                break;
            }

            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }


    } while (choice != 9);















    // // Test Case 1: Registering patients
    // int p1 = hospital.registerPatient("John Doe", 35, "555-1234");  //patient constructor + patient vector
    // int p2 = hospital.registerPatient("Jane Smith", 28, "555-5678");
    // int p3 = hospital.registerPatient("Mike Johnson", 45, "555-9012");
    //
    // // Test Case 2: Adding doctors
    // int d1 = hospital.addDoctor("Dr. Smith", CARDIOLOGY); //doctor constructor + doctor vector
    // int d2 = hospital.addDoctor("Dr. Brown", NEUROLOGY);
    // int d3 = hospital.addDoctor("Dr. Lee", PEDIATRICS);
    //
    // // Test Case 3: Admitting patients
    // hospital.admitPatient(p1, PRIVATE_ROOM); //is admitted // room
    // hospital.admitPatient(p2, ICU);
    // // Try admitting already admitted patient
    // hospital.admitPatient(p1, SEMI_PRIVATE);  //cout<<is already admitted
    //
    // // Test Case 4: Booking appointments
    // hospital.bookAppointment(d1, p1);     //connect patient to his doctor queue
    // hospital.bookAppointment(d1, p2);
    // hospital.bookAppointment(d2, p3);
    // // Try booking with invalid doctor/patient
    // hospital.bookAppointment(999, p1); // Invalid doctor
    // hospital.bookAppointment(d1, 999); // Invalid patient
    //
    // // Test Case 5: Handling medical tests
    // // These would normally be called on Patient objects
    // // In a real implementation, we'd need a way to access patients
    //
    // // Test Case 6: Emergency cases
    // hospital.addEmergency(p3);
    // hospital.addEmergency(p1);
    // int emergencyPatient = hospital.handleEmergency();
    // emergencyPatient = hospital.handleEmergency();
    // emergencyPatient = hospital.handleEmergency(); // No more emergencies
    //
    // // Test Case 7: Discharging patients
    // // Would normally call dischargePatient() on Patient objects
    //
    // // Test Case 8: Displaying information
    // hospital.displayPatientInfo(p1);
    // hospital.displayPatientInfo(p2);
    // hospital.displayPatientInfo(999); // Invalid patient
    //
    // hospital.displayDoctorInfo(d1);
    // hospital.displayDoctorInfo(d2);
    // hospital.displayDoctorInfo(999); // Invalid doctor
    //
    // // Test Case 9: Doctor seeing patients
    // // These would normally be called on Doctor objects
    // // In a real implementation, we'd need a way to access doctors
    //
    // // Test Case 10: Edge cases
    // Hospital emptyHospital;
    // emptyHospital.displayPatientInfo(1); // No patients
    // emptyHospital.displayDoctorInfo(1);  // No doctors
    // emptyHospital.handleEmergency();     // No emergencies

    return 0;
}