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
    }
    //Ask about loging in the medical history stack and ask should i write sentences?

    void admitPatient(RoomType type){
      isAdmitted = true;
      roomType = type;
        string roomTypes[4] = {"GENERAL_WARD","ICU","PRIVATE_ROOM","SEMI_PRIVATE"};
      string record = "Patient admitted in" + roomTypes[type];
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
        cout << "Patient " << patientId << " Booked with Dr. " << name << endl;
    }

    int seePatient(){
        if(appointmentQueue.empty()){
            cout << "No patients in the queue for De. " << name << endl;
            return -1;
        }
        int patientId = appointmentQueue.front();
        appointmentQueue.pop();
        cout << "Dr. " << name << " is now seeing patient " << patientId << endl;
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
    int patientCounter=0;
    int doctorCounter=0;
    
public:
    Hospital();
    
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
        if(patientId<=patients.size()&&patientId>0)
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
        if (emergencyQueue.empty()) return -1;

        int id = emergencyQueue.front();
        emergencyQueue.pop();
        cout << "Emergency Treated: " << id << endl;
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
                cout << "Successfully reserved appointment for Patient "<< patientId << " with Doctor " << doctorId << endl;
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
        if(patientId<=patients.size()&&patientId>0)
        {
            cout<<"patient ID: "<<patients[patientId-1].getId()<<endl;
            cout<<"patient Name: "<<patients[patientId-1].getName()<<endl;
            cout<<"patient Admission: "<<patients[patientId-1].getAdmissionStatus()<<endl;
            cout<<"patient Medical History:";
            patients[patientId-1].displayHistory();
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
        if(doctorId<=doctors.size()&&doctorId>0)
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
// ========== MAIN PROGRAM ========== //
int main() {
    Hospital hospital;
    
    // Test Case 1: Registering patients
    int p1 = hospital.registerPatient("John Doe", 35, "555-1234");  //patient constructor + patient vector
    int p2 = hospital.registerPatient("Jane Smith", 28, "555-5678");
    int p3 = hospital.registerPatient("Mike Johnson", 45, "555-9012");
    
    // Test Case 2: Adding doctors
    int d1 = hospital.addDoctor("Dr. Smith", CARDIOLOGY); //doctor constructor + doctor vector
    int d2 = hospital.addDoctor("Dr. Brown", NEUROLOGY);
    int d3 = hospital.addDoctor("Dr. Lee", PEDIATRICS);
    
    // Test Case 3: Admitting patients
    hospital.admitPatient(p1, PRIVATE_ROOM); //is admitted // room
    hospital.admitPatient(p2, ICU);
    // Try admitting already admitted patient
    hospital.admitPatient(p1, SEMI_PRIVATE);  //cout<<is already admitted
    
    // Test Case 4: Booking appointments
    hospital.bookAppointment(d1, p1);     //connect patient to his doctor queue    
    hospital.bookAppointment(d1, p2);
    hospital.bookAppointment(d2, p3);
    // Try booking with invalid doctor/patient
    hospital.bookAppointment(999, p1); // Invalid doctor
    hospital.bookAppointment(d1, 999); // Invalid patient
    
    // Test Case 5: Handling medical tests
    // These would normally be called on Patient objects
    // In a real implementation, we'd need a way to access patients
    
    // Test Case 6: Emergency cases
    hospital.addEmergency(p3);      
    hospital.addEmergency(p1);
    int emergencyPatient = hospital.handleEmergency();
    emergencyPatient = hospital.handleEmergency();
    emergencyPatient = hospital.handleEmergency(); // No more emergencies
    
    // Test Case 7: Discharging patients
    // Would normally call dischargePatient() on Patient objects
    
    // Test Case 8: Displaying information
    hospital.displayPatientInfo(p1);
    hospital.displayPatientInfo(p2);
    hospital.displayPatientInfo(999); // Invalid patient
    
    hospital.displayDoctorInfo(d1);
    hospital.displayDoctorInfo(d2);
    hospital.displayDoctorInfo(999); // Invalid doctor
    
    // Test Case 9: Doctor seeing patients
    // These would normally be called on Doctor objects
    // In a real implementation, we'd need a way to access doctors
    
    // Test Case 10: Edge cases
    Hospital emptyHospital;
    emptyHospital.displayPatientInfo(1); // No patients
    emptyHospital.displayDoctorInfo(1);  // No doctors
    emptyHospital.handleEmergency();     // No emergencies
    
    return 0;
}