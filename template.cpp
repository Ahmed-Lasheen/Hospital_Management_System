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
    Patient(int pid, string n, int a, string c);
    
    void admitPatient(RoomType type);
    void dischargePatient();
    void addMedicalRecord(string record);
    void requestTest(string testName);
    string performTest();
    void displayHistory();
    
    int getId();
    string getName();
    bool getAdmissionStatus();
};

// ========== DOCTOR CLASS ========== //
class Doctor {
private:
    int id;
    string name;
    Department department;
    queue<int> appointmentQueue;
    
public:
    Doctor(int did, string n, Department d);
    
    void addAppointment(int patientId);
    int seePatient();
    
    int getId();
    string getName();
    string getDepartment();
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
        return patientCounter;
    }
    ///////////////////////////
    int addDoctor(string name, Department dept)
    {
        doctors.push_back(Doctor(++doctorCounter,name,dept));
        cout<<"Successfully added a new doctor\n";
        return doctorCounter;
    }
    //////////////////////////
    void admitPatient(int patientId, RoomType type)
    {
        if(patientId<patients.size()&&patientId>0)
        {
            if(patients[patientId-1].getAdmissionStatus())
            {
                cout<<patients[patientId-1].getName()<<" is already admitted to a room"<<endl;
            }
            else
            {
                patients[patientId-1].admitPatient(type);
                cout<<"Successfully addmited "<<patients[patientId-1].getName()<<endl;
            }
            return;
            
        }
        else
        {
            cout<<"invalid Patient ID"<<endl;
            return;            
        }    

    }
    ///////////////////////
    void addEmergency(int patientId)
    {

        if(patientId<patients.size()&&patientId>0)
        {
            emergencyQueue.enqueue(patientId);
        }
        else
        {
            cout<<"invalid Patient ID"<<endl;
            return;            
        }    

    }
    ///////////////////////
    int handleEmergency()
    {

    }
    ///////////////////////
    void bookAppointment(int doctorId, int patientId)
    {

    }
    ///////////////////////
    void displayPatientInfo(int patientId)
    {

    }
    ///////////////////////
    void displayDoctorInfo(int doctorId)
    {

    }
    ///////////////////////
};

// ========== MAIN PROGRAM ========== //
int main() {
    Hospital hospital;
    
    // Test Case 1: Registering patients
    int p1 = hospital.registerPatient("John Doe", 35, "555-1234");
    int p2 = hospital.registerPatient("Jane Smith", 28, "555-5678");
    int p3 = hospital.registerPatient("Mike Johnson", 45, "555-9012");
    
    // Test Case 2: Adding doctors
    int d1 = hospital.addDoctor("Dr. Smith", CARDIOLOGY);
    int d2 = hospital.addDoctor("Dr. Brown", NEUROLOGY);
    int d3 = hospital.addDoctor("Dr. Lee", PEDIATRICS);
    
    // Test Case 3: Admitting patients
    hospital.admitPatient(p1, PRIVATE_ROOM);
    hospital.admitPatient(p2, ICU);
    // Try admitting already admitted patient
    hospital.admitPatient(p1, SEMI_PRIVATE);
    
    // Test Case 4: Booking appointments
    hospital.bookAppointment(d1, p1);
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