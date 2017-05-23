#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct PatientInfo
{
	string ID;
	string Name;
	string LastName;
	string Phone;
	string BirthDay;
};

struct AppointmentInfo
{
	string Date;
	string Time;
	string Doctor;
	string Diagnosis;
	string Drug;
	string Assay;
};

bool CheckRecord(string id);
bool CheckAppointment(string id);

void NewPatient();
void EditPatient(string id);
void DeletePatient(string id);

void NewAppointment();
void DeleteAppointment(string id);
void EditAppointment(string id);

void SearchPatient(string id);
void ListPatient();

void Examination(string id);

void Menu();

int main()
{
	while (true)
	{
		system("cls");
		Menu();
		system("pause");
	}
	return 0;
}

bool CheckRecord(string id)
{
	ifstream ReadFile;	ReadFile.open("Patient.txt");
	PatientInfo Patient;
	bool check = 0;

	while (!ReadFile.eof())
	{
		ReadFile >> Patient.ID >> Patient.Name >> Patient.LastName >> Patient.BirthDay >> Patient.Phone;
		if (Patient.ID == id)
			check = 1;
	}

	return check;
}

bool CheckAppointment(string id)
{
	ifstream ReadFile;	ReadFile.open("Appointment.txt");
	PatientInfo Patient;
	AppointmentInfo Appointment;
	bool check = 0;

	while (!ReadFile.eof())
	{
		ReadFile >> Patient.ID >> Appointment.Date >> Appointment.Time >> Appointment.Doctor >> Appointment.Diagnosis >> Appointment.Drug >> Appointment.Assay;
		if (Patient.ID == id)
			check = 1;
	}

	return check;
}

void NewPatient()
{
	ofstream WriteFile;	WriteFile.open("Patient.txt", ios::app);
	string id;
	PatientInfo Patient;

	cout << "New Patient" << endl << "Personal Identity..: "; cin >> id;

	if (CheckRecord(id) == 1)
	{
		cout << "There is such a person!" << endl;
	}
	else
	{
		Patient.ID = id;
		cout << "Name...............: "; cin >> Patient.Name;
		cout << "Lastname...........: "; cin >> Patient.LastName;
		cout << "Birthday...........: "; cin >> Patient.BirthDay;
		cout << "Phone..............: "; cin >> Patient.Phone;

		WriteFile << Patient.ID << "\t" << Patient.Name << "\t" << Patient.LastName << "\t" << Patient.BirthDay << "\t" << Patient.Phone << endl;
		cout << "Successful!" << endl;
	}
	WriteFile.close();
}

void EditPatient(string id)
{
	ifstream ReadFile;	ReadFile.open("Patient.txt");
	ofstream WriteFile;	WriteFile.open("EditPatient.txt", ios::app);
	PatientInfo Patient;
	bool check = 0;

	while (!ReadFile.eof())
	{
		ReadFile >> Patient.ID >> Patient.Name >> Patient.LastName >> Patient.BirthDay >> Patient.Phone;
		if (Patient.ID == id)
		{
			if (ReadFile.eof())	break;
			cout << "Identy................: " << Patient.ID << endl;
			cout << "Name..................: " << Patient.Name << endl;
			cout << "Lastname..............: " << Patient.LastName << endl;
			cout << "Birthday..............: " << Patient.BirthDay << endl;
			cout << "Phone.................: " << Patient.Phone << endl << endl;

			cout << "New Info" << endl;
			cout << "Name..................: "; cin >> Patient.Name;
			cout << "Lastname..............: "; cin >> Patient.LastName;
			cout << "Birthday..............: "; cin >> Patient.BirthDay;
			cout << "Phone.................: "; cin >> Patient.Phone;

			WriteFile << Patient.ID << "\t" << Patient.Name << "\t" << Patient.LastName << "\t" << Patient.BirthDay << "\t" << Patient.Phone << endl;
			check = 1;
		}
		else
		{
			if (ReadFile.eof())	break;
			WriteFile << Patient.ID << "\t" << Patient.Name << "\t" << Patient.LastName << "\t" << Patient.BirthDay << "\t" << Patient.Phone << endl;
		}
	}

	ReadFile.close();
	WriteFile.close();

	if (check == 1)
	{
		remove("Patient.txt");
		rename("EditPatient.txt", "Patient.txt");
	}
	else
	{
		cout << "There is not such a ID!" << endl;
		remove("EditPatient.txt");
	}
}

void DeletePatient(string id)
{
	ifstream ReadFile;	ReadFile.open("Patient.txt");
	ofstream WriteFile;	WriteFile.open("DeletePatient.txt", ios::app);
	PatientInfo Patient;
	bool check = 0;

	if (CheckRecord(id) == 0)
	{
		cout << "There is not such a ID!" << endl;
	}
	else
	{
		check = 1;
		while (!ReadFile.eof())
		{
			if (ReadFile.eof())	break;
			ReadFile >> Patient.ID >> Patient.Name >> Patient.LastName >> Patient.BirthDay >> Patient.Phone;
			if (Patient.ID != id)
			{
				if (ReadFile.eof())	break;
				WriteFile << Patient.ID << "\t" << Patient.Name << "\t" << Patient.LastName << "\t" << Patient.BirthDay << "\t" << Patient.Phone << endl;
			}
		}
	}
	ReadFile.close();
	WriteFile.close();

	if (check == 1)
	{
		remove("Patient.txt");
		rename("DeletePatient.txt", "Patient.txt");
		cout << "Patient deleted!" << endl;
	}
	else
	{
		remove("DeletePatient.txt");
	}
}

void NewAppointment()
{
	ifstream ReadFile;	ReadFile.open("Patient.txt");
	ofstream WriteFile;	WriteFile.open("Appointment.txt", ios::app);
	string id;
	PatientInfo Patient;
	AppointmentInfo Appointment;

	cout << "New Appointment" << endl << "Identy................: "; cin >> id;
	if (CheckRecord(id) == 0)
	{
		cout << "There is not such a Patient. Create new Patient: " << endl;
		NewPatient();
	}

	cout << "Appointment Date......: "; cin >> Appointment.Date;
	cout << "Appointment Time......: "; cin >> Appointment.Time;

	Patient.ID = id;
	Appointment.Doctor = "-";
	Appointment.Diagnosis = "-";
	Appointment.Drug = "-";
	Appointment.Assay = "-";
	WriteFile << Patient.ID << "\t" << Appointment.Date << "\t" << Appointment.Time << "\t" << Appointment.Doctor << "\t" << Appointment.Diagnosis << "\t" << Appointment.Drug << "\t" << Appointment.Assay << endl;

	WriteFile.close();
	ReadFile.close();
	cout << "Appointment created!" << endl;
}

void DeleteAppointment(string id)
{
	ifstream ReadFile;	ReadFile.open("Appointment.txt");
	ofstream WriteFile;	WriteFile.open("DeleteAppointment.txt", ios::app);
	PatientInfo Patient;
	AppointmentInfo Appointment;
	bool check = 0;

	if (CheckAppointment(id) == 0)
	{
		cout << "Appointment not found!" << endl;
	}
	else
	{
		check = 1;
		while (!ReadFile.eof())
		{
			if (ReadFile.eof())	break;
			ReadFile >> Patient.ID >> Appointment.Date >> Appointment.Time >> Appointment.Doctor >> Appointment.Diagnosis >> Appointment.Drug >> Appointment.Assay;

			if (Patient.ID != id)
			{
				if (ReadFile.eof())	break;
				WriteFile << Patient.ID << "\t" << Appointment.Date << "\t" << Appointment.Time << "\t" << Appointment.Doctor << "\t" << Appointment.Diagnosis << "\t" << Appointment.Drug << "\t" << Appointment.Assay << endl;
			}
		}
	}
	ReadFile.close();
	WriteFile.close();

	if (check == 1)
	{
		remove("Appointment.txt");
		rename("DeleteAppointment.txt", "Appointment.txt");
		cout << "Appointment deleted!" << endl;
	}
	else
	{
		remove("DeleteAppointment.txt");
	}
}

void EditAppointment(string id)
{
	ifstream ReadFile;	ReadFile.open("Appointment.txt");
	ofstream WriteFile;	WriteFile.open("EditAppointment.txt", ios::app);
	PatientInfo Patient;
	AppointmentInfo Appointment;
	bool check = 0;

	while (!ReadFile.eof())
	{
		ReadFile >> Patient.ID >> Appointment.Date >> Appointment.Time >> Appointment.Doctor >> Appointment.Diagnosis >> Appointment.Drug >> Appointment.Assay;
		if (Patient.ID == id)
		{
			if (ReadFile.eof())	break;
			cout << "Identy................: " << Patient.ID << endl;
			cout << "Appointment Date......: " << Appointment.Date << endl;
			cout << "Appointment Time......: " << Appointment.Time << endl;

			cout << "New Info" << endl;
			cout << "Appointment Date......: "; cin >> Appointment.Date;
			cout << "Appointment Time......: "; cin >> Appointment.Time;

			WriteFile << Patient.ID << "\t" << Appointment.Date << "\t" << Appointment.Time << "\t" << Appointment.Doctor << "\t" << Appointment.Diagnosis << "\t" << Appointment.Drug << "\t" << Appointment.Assay << endl;
			check = 1;
		}
		else
		{
			if (ReadFile.eof())	break;
			WriteFile << Patient.ID << "\t" << Appointment.Date << "\t" << Appointment.Time << "\t" << Appointment.Doctor << "\t" << Appointment.Diagnosis << "\t" << Appointment.Drug << "\t" << Appointment.Assay << endl;
		}
	}

	ReadFile.close();
	WriteFile.close();

	if (check == 1)
	{
		remove("Appointment.txt");
		rename("EditAppointment.txt", "Appointment.txt");
		cout << "Appointment updated!" << endl;
	}
	else
	{
		cout << "There is not such a Appointment!" << endl;
		remove("EditAppointment.txt");
	}
}

void SearchPatient(string id)
{
	ifstream ReadFileP;	ReadFileP.open("Patient.txt");
	ifstream ReadFileA;	ReadFileA.open("Appointment.txt");
	PatientInfo Patient;
	AppointmentInfo Appointment;

	if (CheckRecord(id) == 0)
	{
		cout << "Patient not found." << endl;
	}
	else
	{
		while (!ReadFileP.eof())
		{
			ReadFileP >> Patient.ID >> Patient.Name >> Patient.LastName >> Patient.BirthDay >> Patient.Phone;
			if (Patient.ID == id)
			{
				if (ReadFileP.eof()) break;
				cout << "Identy................: " << Patient.ID << endl;
				cout << "Name..................: " << Patient.Name << endl;
				cout << "Lastname..............: " << Patient.LastName << endl;
				cout << "Birthday..............: " << Patient.BirthDay << endl;
				cout << "Phone.................: " << Patient.Phone << endl << endl;
			}
		}

		if (CheckAppointment(id) == 1)
		{
			while (!ReadFileA.eof())
			{
				ReadFileA >> Patient.ID >> Appointment.Date >> Appointment.Time >> Appointment.Doctor >> Appointment.Diagnosis >> Appointment.Drug >> Appointment.Assay;
				if (Patient.ID == id)
				{
					cout << "Date..................: " << Appointment.Date << endl;
					cout << "Time..................: " << Appointment.Time << endl;
					cout << "Doctor................: " << Appointment.Doctor << endl;
					cout << "Diagnosis.............: " << Appointment.Diagnosis << endl;
					cout << "Drug..................: " << Appointment.Drug << endl;
					cout << "Assay.................: " << Appointment.Assay << endl;

					if (ReadFileP.eof()) break;
				}
			}
		}
		else
		{
			cout << "The patient's appointment is not available." << endl;
		}
	}
	ReadFileA.close();
	ReadFileP.close();
}

void ListPatient()
{
	PatientInfo Patient;
	ifstream ReadFile; ReadFile.open("Patient.txt");

	cout << "ID" << "\t" << "Name" << "\t" << "Lastname" << "\t" << "Birthday" << "\t" << "Phone" << endl;
	while (!ReadFile.eof())
	{
		ReadFile >> Patient.ID >> Patient.Name >> Patient.LastName >> Patient.BirthDay >> Patient.Phone;
		if (ReadFile.eof())	break;
		cout << Patient.ID << "\t" << Patient.Name << "\t" << Patient.LastName << "\t\t" << Patient.BirthDay << "\t" << Patient.Phone << endl;
	}
	ReadFile.close();
}

void Examination(string id)
{
	ifstream ReadFile;	ReadFile.open("Appointment.txt");
	ofstream WriteFile;	WriteFile.open("Examination.txt", ios::app);
	PatientInfo Patient;
	AppointmentInfo Appointment;
	bool check = 0;


	if (CheckAppointment(id) == 0)
	{
		cout << "Appointment must be made for examination!" << endl;
	}
	else
	{
		while (!ReadFile.eof())
		{
			ReadFile >> Patient.ID >> Appointment.Date >> Appointment.Time >> Appointment.Doctor >> Appointment.Diagnosis >> Appointment.Drug >> Appointment.Assay;
			if (Patient.ID == id)
			{
				if (ReadFile.eof())	break;
				Patient.ID = id;
				cout << "Date..................: "; cin >> Appointment.Date;
				cout << "Time..................: "; cin >> Appointment.Time;
				cout << "Doctor................: "; cin >> Appointment.Doctor;
				cout << "Diagnosis.............: "; cin >> Appointment.Diagnosis;
				cout << "Drug..................: "; cin >> Appointment.Drug;
				cout << "Assay.................: "; cin >> Appointment.Assay;

				WriteFile << Patient.ID << "\t" << Appointment.Date << "\t" << Appointment.Time << "\t" << Appointment.Doctor << "\t" << Appointment.Diagnosis << "\t" << Appointment.Drug << "\t" << Appointment.Assay << endl;
				check = 1;
				break;
			}
			else
			{
				if (ReadFile.eof())	break;
				WriteFile << Patient.ID << "\t" << Appointment.Date << "\t" << Appointment.Time << "\t" << Appointment.Doctor << "\t" << Appointment.Diagnosis << "\t" << Appointment.Drug << "\t" << Appointment.Assay << endl;
			}
		}
	}
	ReadFile.close();
	WriteFile.close();

	if (check == 1)
	{
		remove("Appointment.txt");
		rename("Examination.txt", "Appointment.txt");
		cout << "Examination created!" << endl;
	}
	else
	{
		remove("Examination.txt");
	}

}

void Menu()
{
	int choose;
	string id = "";

	cout << "1. New Patient" << endl;
	cout << "2. Edit Patient" << endl;
	cout << "3. Delete Patient" << endl;
	cout << "4. New Appointment" << endl;
	cout << "5. Delete Appointment" << endl;
	cout << "6. Update Appointment" << endl;
	cout << "7. Search Patient" << endl;
	cout << "8. Patient List" << endl;
	cout << "9. Create Examination\n" << endl;

	cout << "Choose: "; cin >> choose;
	cout << endl;

	switch (choose)
	{
	case 1:
	{
		NewPatient();
		break;
	}
	case 2:
	{
		cout << "Edit Patient" << endl << "Identity: "; cin >> id;
		EditPatient(id);
		break;
	}
	case 3:
	{
		cout << "Delete Patient" << endl << "Identity: "; cin >> id;
		DeletePatient(id);

		if (CheckAppointment(id) == 1)
			DeleteAppointment(id);

		break;
	}
	case 4:
	{
		NewAppointment();
		break;
	}
	case 5:
	{
		cout << "Delete Appointment" << endl << "Identity: "; cin >> id;
		DeleteAppointment(id);
		break;
	}
	case 6:
	{
		cout << "Edit Appointment" << endl << "Identity: "; cin >> id;
		EditAppointment(id);
		break;
	}
	case 7:
	{
		cout << "Search Patient" << endl << "Identity: "; cin >> id;
		SearchPatient(id);
		break;
	}
	case 8:
	{
		ListPatient();
		break;
	}
	case 9:
	{
		cout << "Create Examination" << endl << "Identity: "; cin >> id;
		Examination(id);
		break;
	}
	default:
	{
		cout << "Wrong choice!" << endl;
		break;
	}
	}
}