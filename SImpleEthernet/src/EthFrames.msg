packet EthFrame {
    name = "EthFrame";
    string nome;
    string dst;
    string src;
    int ethertype;
    byteLength = 26;
    simtime_t deadlineA; //priorità
    simtime_t deadlineR;
    int priority;
    bool sw1;
    bool sw2;
    bool sw3;
    bool sw4;
    bool sw5;
    bool sw6;
    
    simtime_t period;
    int payload;
    int burst;
    int pri; //priorita inserita dell'utente
     simtime_t e2eMax;
    simtime_t e2eAvg;
    
    
    //int flagSwitch;
    
    //simtime_t priority; //priorità
};