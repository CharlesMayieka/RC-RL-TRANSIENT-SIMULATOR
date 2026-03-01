//This code simulates the transient response of RC(Resistor-Capacitor)
//and RL(Resistor-Indicator) circuits when subjected to a step input
//(usually a DC voltage source switched on at t=0)
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    int choice; //stores users choice;either RC or RL circuit

    double R, C, L, Vs;
    double t, dt, T;
    double voltage;
    double current;
    double tau;

    cout << "======================================" << endl;
    cout << "   RC / RL TRANSIENT SIMULATOR" << endl;
    cout << "======================================" << endl;
    cout << "1. RC Circuit" << endl;
    cout << "2. RL Circuit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    cout << "\nEnter Resistance , R (Ohms): ";
    cin >> R;

    cout << "Enter Supply Voltage , Vs (Volts): ";
    cin >> Vs;

    cout << "Enter time step dt (seconds): ";
    cin >> dt;

    cout << "Enter total simulation time , T (seconds): ";
    cin >> T;

    // Open CSV in append mode (remembers previous data)
    ofstream file("transient_output.csv", ios::app);

    // Write a run header so each simulation is identifiable
    file << "\n=====================================\n";
    if (choice == 1)
        file << "RC CIRCUIT SIMULATION\n";
    else
        file << "RL CIRCUIT SIMULATION\n";

    file << "R=" << R << ", Vs=" << Vs << ", dt=" << dt << ", T=" << T << "\n";
    file << "Time(s),Voltage(V),Current(A)\n";

    cout << "\nTime(s)\tVoltage(V)\tCurrent(A)" << endl;
    cout << "----------------------------------------" << endl;

    if (choice == 1)   // RC circuit
    {
        cout << "Enter Capacitance C (Farads): ";
        cin >> C;

        tau = R * C;

        for (t = 0; t <= T; t += dt)
        {
            voltage = Vs * (1 - exp(-t / tau));
            current = (Vs / R) * exp(-t / tau);

            cout << fixed << setprecision(4)
                 << t << "\t" << voltage << "\t\t" << current << endl;

            file << t << "," << voltage << "," << current << "\n";
        }
    }
    else if (choice == 2)   // RL circuit
    {
        cout << "Enter Inductance , L (Henrys): ";
        cin >> L;

        tau = L / R;

        for (t = 0; t <= T; t += dt) //Loop over time from 0 to t
        {
            current = (Vs / R) * (1 - exp(-t / tau));
            voltage = Vs * exp(-t / tau);

            cout << fixed << setprecision(4)
                 << t << "\t" << voltage << "\t\t" << current << endl;

            file << t << "," << voltage << "," << current << "\n"; //Writes values to the CSV file
        }
    }
    else //Executes if invalid choice is entered
    {
        cout << "Invalid choice!" << endl;
        file.close();
        return 0;
    }

    file.close();

    cout << "\nSimulation completed successfully." << endl;
    cout << "Results appended to transient_output.csv" << endl;

    return 0;
}
