
packet AppPacket {
    name = "AppPacket";
    simtime_t genTime;
    bool lastBurstPacket = false;    
    int idx;
    int idBurst;
    bool video; 
    
};

message AppControlInfo {
    string dst;
    string src;    
    simtime_t priority;
    int priorita_esteso;
    simtime_t period;
    int payload;
    int burts;
    string nome;
    simtime_t e2eMax;
    simtime_t e2eAvg;
    
    int pri;//priorità inserita dall'utente
    
    simtime_t deadlineR;
};
