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
    bool debe_bloquear;
    bool ya_bloqueado;

public:
    Process(string id, int time, bool will_bloque, int time_antes, int time_block_res) : 
    id(id), time_remaining(time), time_restante_antes_blocked(time_antes), blocked_time_restante(time_block_res), debe_bloquear(will_bloque), ya_bloqueado(false){}                     // logica del scheduler, un processo puede esta bloqueado nada mas una vez, el usuaria cin time_restantes_anes_blocked y blocked_time_restante

    string getId() { return id; }
    int getTime() { return time_remaining; }
                                                                        // El proceso usa la CPU por "quantum" unidades de tiempo
    void execute(int quantum) {
        time_remaining -= quantum;
        if (time_remaining < 0) {
            time_remaining = 0;
        }
        if (debe_bloquear && !ya_bloqueado){                    // bajar el tiempo de blocked con el quantum 
            time_restante_antes_blocked -= quantum;
            if (time_restante_antes_blocked < 0){
                time_restante_antes_blocked = 0;
            }
        }
    }

    void marcar_bloqueado(){
        ya_bloqueado = true;
    }

    bool debe_bloquear_eje(){                                                                                
            return debe_bloquear && time_restante_antes_blocked <= 0 && blocked_time_restante > 0 && !ya_bloqueado;        // update de los valores para blocked        
    }

    void esperar(int quantum){
        blocked_time_restante -= quantum;
        if(blocked_time_restante < 0){
            blocked_time_restante = 0;
        }
    }
    bool puede_desbloquearse(){
        return blocked_time_restante == 0;
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
        while (!ready.empty() || !blocked.empty()) {

            int cantidad_bloqueados = blocked.size();

            for(int i = 0, i < cantidad_bloqueados, i++){
                Process proceso_bloqueado = blocked.front();
                blocked.pop();
                proceso_bloqueado.esperar(quantum);

                if(proceso_bloqueado.puede_desbloquearse()){
                    ready.push(proceso_bloqueado);
                    cout << "Proceso" << proceso_bloqueado.getId() << "vuelve a estado READY" << endl; 
                }
                else {
                    blocked.push(proceso_bloqueado);
                }
            }
            if (ready.empty ()){
                cout << "CPU bloquado" << endl;
                continue;
            }

            Process p = ready.front();
            ready.pop();

            cout << "Proceso " << p.getId() << " - RUNNING" << endl;
            p.execute(quantum);                                                                     // Usa quantum unidades de tiempo
            cout << "Tiempo restante: " << p.getTime() << endl;

            if (p.getTime() > 0) {
                if (p.debe_bloquear_eje()){                                                               // Si aún tiene tiempo, vuelve a la cola (Preemption)
                p.marcar_bloqueado();
                cout << "Blocked - Estado update a bloqueado hasta el tiempo restante";
                blocked.push(p);
                }
                else {
                    cout << "Preemption - volviendo a  estado READY" << endl;
                    ready.push(p);
                }
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
        bool will_bloque;
        int time_antes = 0;
        int time_block_res = 0;
        cout << "Proceso " << (i + 1) << ":" << endl;
        cout << "  ID (numero): ";
        cin >> id;
        cout << "  Tiempo de ejecucion: ";
        cin >> time;
        cout << "  Debe bloquearse? (0 = no, 1 = si): ";
        cin >> will_bloque;
        if (will_bloque) {
            cout << "  Tiempo antes de bloquearse: ";
            cin >> time_antes;
            cout << "  Duracion del bloqueo: ";
            cin >> time_block_res;
        }
        sched.addProcess(Process(id, time, will_bloque, time_antes, time_block_res));
    }

    cout << "" << endl;
    sched.simulate();

    cout << "Presione cualquier tecla para salir...";
    system("pause");
    return 0;
}