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

    int getBlockedTime() { return blocked_time_restante; }

    //parte FCFS

    int tiempo_hasta_siguiente_event(){
        int tiempo_ejecutando = time_remaining;
        if (debe_bloquear && !ya_bloqueado && time_restante_antes_blocked < tiempo_ejecutando){
            tiempo_ejecutando = time_restante_antes_blocked;
        }
        return tiempo_ejecutando;
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

    void esperar_bloqueados(int tiempo){              // ahora en vez de hacer lo en el algoritmo estq directeamente en scheduler
        while(tiempo > 0 && !blocked.empty()){
            int tiempo_paso = tiempo;
            int cantidad_bloqueados = blocked.size();
            for(int i = 0; i < cantidad_bloqueados; i++){
                Process proceso_bloqueado = blocked.front();
                blocked.pop();
                if(proceso_bloqueado.getBlockedTime() < tiempo_paso){
                    tiempo_paso = proceso_bloqueado.getBlockedTime();
                }
                blocked.push(proceso_bloqueado);
            }
            for(int i = 0; i < cantidad_bloqueados; i++){
                Process proceso_bloqueado = blocked.front();
                blocked.pop();
                proceso_bloqueado.esperar(tiempo_paso);

                if(proceso_bloqueado.puede_desbloquearse()){
                    ready.push(proceso_bloqueado);
                    cout << "Proceso : " << proceso_bloqueado.getId() << " vuelve a estado READY" << endl;
                }
                else {
                    blocked.push(proceso_bloqueado);
                }
            }
            tiempo -= tiempo_paso;
        }
    }

                                            // Simula el scheduler ejecutando procesos con Round-Robin
    void simulate_round_robin() {
        while (!ready.empty() || !blocked.empty()) {

            
            if (ready.empty ()){
                cout << "CPU bloquado" << endl;
                int cantidad_bloqueados = blocked.size();
                for(int i = 0; i < cantidad_bloqueados; i++){          // Bucle para recorrer todos los procesos bloqueados y aplicar el esperar o volver a ponerlos el estado ready
                Process proceso_bloqueado = blocked.front();
                blocked.pop();
                proceso_bloqueado.esperar(quantum);

                if(proceso_bloqueado.puede_desbloquearse()){
                    ready.push(proceso_bloqueado);
                    cout << "Proceso : " << proceso_bloqueado.getId() << " vuelve a estado READY" << endl; 
                }
                else {
                    blocked.push(proceso_bloqueado);
                }
                }
            }

            if (ready.empty()){
                continue;
            }

            Process p = ready.front();
            ready.pop();

            cout << "Proceso " << p.getId() << " - RUNNING" << endl;
            p.execute(quantum);                      // Usa quantum unidades de tiempo
            int cantidad_bloqueados = blocked.size();
            for(int i = 0; i < cantidad_bloqueados; i++){          // Bucle para recorrer todos los procesos bloqueados y aplicar el esperar o volver a ponerlos el estado ready
                Process proceso_bloqueado = blocked.front();
                blocked.pop();
                proceso_bloqueado.esperar(quantum);

                if(proceso_bloqueado.puede_desbloquearse()){
                    ready.push(proceso_bloqueado);
                    cout << "Proceso : " << proceso_bloqueado.getId() << " vuelve a estado READY" << endl; 
                }
                else {
                    blocked.push(proceso_bloqueado);
                }
            }

            cout << "Tiempo restante: " << p.getTime() << endl;

            if (p.getTime() > 0) {
                if (p.debe_bloquear_eje()){                                                               // Si aún tiene tiempo, vuelve a la cola (Preemption)
                p.marcar_bloqueado();
                cout << "Blocked  proceso : " << p.getId() << " Estado update a bloqueado hasta el tiempo restante" << endl;
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

                                                                                // Nuevo algoritmo de first come first served  
    void simulate_fcfs(){
        while (!ready.empty() || !blocked.empty()) {              
            if (ready.empty()){        
                cout << "CPU bloquado" << endl;
                int tiempo_espera = blocked.front().getBlockedTime();
                int cantidad_bloqueados = blocked.size();
                for(int i = 0; i < cantidad_bloqueados; i++){
                    Process proceso_bloqueado = blocked.front();
                    blocked.pop();
                    if(proceso_bloqueado.getBlockedTime() < tiempo_espera){
                        tiempo_espera = proceso_bloqueado.getBlockedTime();
                    }
                    blocked.push(proceso_bloqueado);
                }
                esperar_bloqueados(tiempo_espera);
            }             // aca nos ocupamos de los procesos que estab bloqueados

            Process p = ready.front();
            ready.pop();                                                    
            cout<<"Proceso " << p.getId() << " - RUNNING" << endl;              
            int tiempo_ejecutando = p.tiempo_hasta_siguiente_event();              // llamando a tiempo hastas siguiente event antes del exec y despues comprobar si se tiene que acabar
            p.execute(tiempo_ejecutando);
            esperar_bloqueados(tiempo_ejecutando);
            cout << "Tiempo restante: " << p.getTime() << endl;
            if(p.getTime() == 0){
                cout << "Proceso " << p.getId() << " TERMINADO" << endl;
            }
            else if(p.debe_bloquear_eje()){             // bloquear
                p.marcar_bloqueado();
                cout << "Blocked  proceso : " << p.getId() << " Estado update a bloqueado hasta el tiempo restante" << endl;
                blocked.push(p);
            }
        }
    }
};

int main() {
    int quantum = 1, numProcesses, algoritmo;
                                                                            // comienzo del output en la terminal
    cout << "     SCHEDULER SIMULADOR    " << endl;
    cout << "Algoritmo (1 = Round-Robin, 2 = FCFS): ";
    cin >> algoritmo;
    if (!cin || (algoritmo != 1 && algoritmo != 2)){
        cout << "Algoritmo invalido" << endl;
        return 1;
    }
    if (algoritmo == 1){
        cout << "Ingrese el Quantum: ";
        cin >> quantum;
        if (!cin || quantum <= 0){
            cout << "Quantum invalido" << endl;
            return 1;
        }
    }
    cout << "Ingrese el numero de procesos: ";
    cin >> numProcesses;
    if (!cin || numProcesses < 0){
        cout << "Numero de procesos invalido" << endl;
        return 1;
    }

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
        cout << "  Debe bloquearse ? (0 = no, 1 = si): ";
        cin >> will_bloque;
        if (!cin){
            cout << "Datos del proceso invalidos" << endl;
            return 1;
        }
        if (will_bloque) {
            cout << "  Tiempo antes de bloquearse: ";
            cin >> time_antes;
            cout << "  Duracion del bloqueo: ";
            cin >> time_block_res;
        }
        if (!cin || time <= 0 || (will_bloque && (time_antes < 0 || time_block_res <= 0))){
            cout << "Datos del proceso invalidos" << endl;
            return 1;
        }
        sched.addProcess(Process(id, time, will_bloque, time_antes, time_block_res));
    }

    cout << "" << endl;
    if (algoritmo == 1){
        sched.simulate_round_robin();
    }
    else {
        sched.simulate_fcfs();
    }
    return 0;
}
