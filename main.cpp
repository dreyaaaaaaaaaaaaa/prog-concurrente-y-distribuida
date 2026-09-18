#include <iostream>
#include <queue>
#include <string>
using namespace std;

                                                                // Representa un proceso con su identificador y tiempo total de ejecución
class Process {
private:
    string id;
    int time_remaining;
    int time_restante_antes_blocked;
    int blocked_time_restante;
    bool bloqueado;

public:
    Process(string id, int time) : 
    id(id), time_remaining(time), time_restante_antes_blocked(time), blocked_time_restante(time), bloqueado() {}

    string getId() { return id; }
    int getTime() { return time_remaining; }
                                                                        // El proceso usa la CPU por "quantum" unidades de tiempo
    void execute(int quantum) {
        time_remaining -= quantum;
        if (time_remaining < 0) time_remaining = 0;
    }
};

                                                                    // El scheduler gestiona la cola de procesos READY y el algoritmo Round-Robin
class Scheduler {
private:
    queue<Process> ready, blocked;                       // Cola de procesos esperando CPU
    int quantum;                        // Máximo tiempo que cada proceso puede usar CPU

public:
    Scheduler(int q) : quantum(q) {}

    void addProcess(const Process& p) {   // para evitar una copia no necesaria
        ready.push(p);                    // aca le dejo crear una copia para que se quede con un process despues del fin d addprocess
    }

                                            // Simula el scheduler ejecutando procesos con Round-Robin
    void simulate() {
        while (!ready.empty()) {
            Process p = ready.front();
            ready.pop();

            cout << "Proceso " << p.getId() << " - RUNNING" << endl;
            p.execute(quantum);                                                                     // Usa quantum unidades de tiempo
            cout << "Tiempo restante: " << p.getTime() << endl;

            if (p.getTime() > 0) {
                                                                                // Si aún tiene tiempo, vuelve a la cola (Preemption)
                cout << "Preemption - volviendo a  estado READY" << endl;
                ready.push(p);
            } 
            elif (p.{

            }
            else {
                                                                                // Si terminó, se elimina
                cout << "Proceso " << p.getId() << " TERMINADO" << endl;
            }
        }
    }
};

int main() {
    int quantum, numProcesses;

    cout << "     SCHEDULER SIMULADOR    " << endl;
    cout << "Ingrese el Quantum: ";
    cin >> quantum;

    cout << "Ingrese el numero de procesos: ";
    cin >> numProcesses;

    Scheduler sched(quantum);

                                                            // Leer datos de cada proceso
    for (int i = 0; i < numProcesses; i++) {
        string id;
        int time;  // str asi no se produce error al meter un id como p1 ect....
        cout << "Proceso " << (i + 1) << ":" << endl;
        cout << "  ID (numero): ";
        cin >> id;
        cout << "  Tiempo de ejecucion: ";
        cin >> time;
        sched.addProcess(Process(id, time));
    }

    cout << "" << endl;
    sched.simulate();

    cout << "Presione cualquier tecla para salir...";
    system("pause");
    return 0;
}