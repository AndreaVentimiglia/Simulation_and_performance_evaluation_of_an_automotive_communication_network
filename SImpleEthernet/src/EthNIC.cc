#include "EthNIC.h"
#include "EthFrames_m.h"
#include "AppPackets_m.h"

Define_Module(EthNIC);

EthFrame *tempQueue[100];
int frame_scartate = 0;
int frame_trasmesse_nodo = 0;
int frame_trasmesse_switch = 0;
simtime_t lateness;
int deadlineMiss = 0;
int Frame_ricevute = 0;
int frame_perse_video = 0;



void EthNIC::initialize() {
    datarate = par("datarate");
    promMode = par("promMode");
    inSwitch = par("inSwitch");

    //idSw = par("idSw");
    txstate = TX_STATE_IDLE;
    limCoda = par("limCoda");
    flagV = par("flagV");


}

void EthNIC::handleMessage(cMessage *msg) {
    if(msg->isSelfMessage()) {
        if(strcmp(msg->getName(), "TxEndTimer") == 0) {
            assert(txstate == TX_STATE_TRANSMITTING);
            delete msg;
            txstate = TX_STATE_WAIT_IFG;
            double t = 96.0 / datarate;
            cMessage *ifgtim = new cMessage("IFGEndTimer");
            scheduleAt(simTime() + t, ifgtim);
            return;
        } else if(strcmp(msg->getName(), "IFGEndTimer") == 0) {
            assert(txstate == TX_STATE_WAIT_IFG);
            delete msg;
            txstate = TX_STATE_IDLE;
            transmit();
            return;
        } else if(strcmp(msg->getName(), "RxEndTimer") == 0) {
            cPacket *pkt = dynamic_cast<cPacket *>(msg->removeControlInfo());
            delete msg;
            send(pkt, "upperLayerOut");
            return;
        }
    }

    if(msg->getArrivalGate() == gate("upperLayerIn")) {

            if(inSwitch) {
                cPacket *pkt = check_and_cast<cPacket *>(msg);
                EthFrame *frame = check_and_cast<EthFrame *>(msg);

                simsignal_t sig;

                if(txqueue.length() <= limCoda) {
                    txqueue.insert(pkt);
                    reorderQueue();
                    lateness = frame->getArrivalTime() - frame->getDeadlineA();
                    EV<<"arrival time: "<<frame->getArrivalTime()<<endl;
                    EV<<"deadLineA: "<<frame->getDeadlineA()<<endl;
                    EV<<"lateness "<<lateness<<endl;

                    if(lateness > 0) {
                        deadlineMiss++;
                    }
                    EV<<"Transmit 2"<<endl;
                    frame_trasmesse_switch++;
                    EV<<"frame trasmesse_switch "<<frame_trasmesse_switch<<endl;
                    transmit();
                    return;
                }
                else {
                    EV<<"coda piena "<<txqueue.length()<<endl;
                    if(flagV) {
                        frame_perse_video++;
                        EV<<"Frame VIDEO scartate "<<frame_perse_video<<endl;
                    }
                    frame_scartate++;

                    EV<<"Frame scartate"<<frame_scartate<<endl;

                    delete pkt;
                    return;
                }
            }

            AppControlInfo *ci = check_and_cast<AppControlInfo *>(msg->removeControlInfo());
            EthFrame *frame = new EthFrame();
            frame->setSrc(ci->getSrc());
            frame->setDst(ci->getDst());
//            frame->setDeadlineA(ci->getPriority() + ci->getArrivalTime()); //assegnamo la priorità alla frame
            frame->setNome(ci->getNome());

            //fatte da me
            frame->setPeriod(ci->getPeriod());
            frame->setDeadlineR(ci->getDeadlineR());

            frame->setPayload(ci->getPayload());
            frame->setBurst(ci->getBurts());

            frame->setE2eAvg(ci->getE2eAvg());
            frame->setE2eMax(ci->getE2eMax());
            frame->setPri(ci->getPri());

            delete ci;
            cPacket *app_pkt = check_and_cast<cPacket *>(msg);
            int padding = 0;


            if(app_pkt->getByteLength() < 46) {
                padding = 46 - app_pkt->getByteLength();
            } else if(app_pkt->getByteLength() > 1500) {
                delete app_pkt;
                delete frame;
                EV << "AppPacket oversize: dropping..." << endl;
                frame_scartate++;
                if(flagV) {
                   frame_perse_video++;
                   EV<<"Frame VIDEO scartate "<<frame_perse_video<<endl;
               }
                return;
            }
            frame->addByteLength(padding);

            frame->encapsulate(app_pkt);


            AppPacket *pkt = check_and_cast<AppPacket *>(msg);

            if(txqueue.length() <= limCoda) {
                txqueue.insert(frame);
                reorderQueue();
                EV<<"Transmit 1"<<endl;
                frame_trasmesse_nodo++;
                EV<<"frame trasmesse_nodo "<<frame_trasmesse_nodo<<endl;
                transmit();

                lateness = simTime() - frame->getDeadlineA();
                if(lateness > 0) {
                    deadlineMiss++;
                }
                return;

            }
            else {
                EV<<"coda piena "<<txqueue.length()<<endl;
                frame_scartate++;
                if(flagV) {
                   frame_perse_video++;
                   EV<<"Frame VIDEO scartate "<<frame_perse_video<<endl;
               }
                EV<<"Frame scartate "<<frame_scartate<<endl;
                delete frame;
                return;
            }
        }

        //Ricezione
        EthFrame *frame = check_and_cast<EthFrame *>(msg);
        frame->setDeadlineA(frame->getDeadlineR() + frame->getArrivalTime()); //assegnamo la priorità alla frame

        if(strcmp(frame->getDst(), "CC") == 0) {
            if((strcmp(frame->getSrc(), "LD1") == 0) || (strcmp(frame->getSrc(), "CM1") == 0) || (strcmp(frame->getSrc(), "DC") == 0) || (strcmp(frame->getSrc(), "ZC1") == 0) || (strcmp(frame->getSrc(), "US1") == 0) || (strcmp(frame->getSrc(), "RD1") == 0)) {
                frame->setSw1(true);
                frame->setSw2(false);
                frame->setSw3(false);
                frame->setSw4(true);
                frame->setSw5(false);
                   frame->setSw6(false);
            }
        }

        if(strcmp(frame->getDst(), "CC") == 0) {
            if((strcmp(frame->getSrc(), "LD2") == 0) || (strcmp(frame->getSrc(), "CM2") == 0) || (strcmp(frame->getSrc(), "RD2") == 0) || (strcmp(frame->getSrc(), "ZC2") == 0) || (strcmp(frame->getSrc(), "US2") == 0) || (strcmp(frame->getSrc(), "CU") == 0)) {
                frame->setSw1(false);
                frame->setSw2(false);
                frame->setSw3(true);
                frame->setSw4(true);
                frame->setSw5(false);
               frame->setSw6(false);
            }
        }

        if((strcmp(frame->getDst(), "CC") == 0) || (strcmp(frame->getDst(), "HU") == 0) || (strcmp(frame->getDst(), "RS1") == 0) || (strcmp(frame->getDst(), "RS2") == 0)) {
            if((strcmp(frame->getSrc(), "TLM") == 0)) {
                frame->setSw1(true);
                frame->setSw2(true);
                frame->setSw3(false);
                frame->setSw4(true);
                frame->setSw5(false);
               frame->setSw6(false);
            }
        }

        if((strcmp(frame->getDst(), "CC") == 0) || (strcmp(frame->getDst(), "S1") == 0)) {
           if((strcmp(frame->getSrc(), "CC") == 0) || (strcmp(frame->getSrc(), "ME") == 0) || (strcmp(frame->getSrc(), "MC1") == 0)) {
               frame->setSw1(true);
               frame->setSw2(false);
               frame->setSw3(true);
               frame->setSw4(true);
               frame->setSw5(false);
               frame->setSw6(false);
           }
       }

        if((strcmp(frame->getDst(), "RS1") == 0) || (strcmp(frame->getDst(), "S3") == 0) || (strcmp(frame->getDst(), "S4") == 0)) {
               if((strcmp(frame->getSrc(), "CC") == 0) || (strcmp(frame->getSrc(), "ME") == 0)) {
                   frame->setSw1(true);
                   frame->setSw2(true);
                   frame->setSw3(false);
                   frame->setSw4(false);
                   frame->setSw5(false);
                   frame->setSw6(true);
               }
           }

        if(strcmp(frame->getDst(), "CC") == 0) {
                if((strcmp(frame->getSrc(), "LD4") == 0) || (strcmp(frame->getSrc(), "RD4") == 0) || (strcmp(frame->getSrc(), "CM4") == 0) || (strcmp(frame->getSrc(), "ZC4") == 0) || (strcmp(frame->getSrc(), "US4") == 0)) {
                    frame->setSw1(false);
                    frame->setSw2(false);
                    frame->setSw3(false);
                    frame->setSw4(true);
                    frame->setSw5(true);
                    frame->setSw6(false);
                }
            }

        if(strcmp(frame->getDst(), "CC") == 0) {
            if((strcmp(frame->getSrc(), "US3") == 0) || (strcmp(frame->getSrc(), "RD3") == 0) || (strcmp(frame->getSrc(), "LD3") == 0) || (strcmp(frame->getSrc(), "CM3") == 0) || (strcmp(frame->getSrc(), "ZC3") == 0)|| (strcmp(frame->getSrc(), "RC") == 0)) {
                frame->setSw1(false);
                frame->setSw2(false);
                frame->setSw3(false);
                frame->setSw4(true);
                frame->setSw5(false);
                frame->setSw6(true);
            }
        }

        if(strcmp(frame->getDst(), "CU") == 0) {
                    if((strcmp(frame->getSrc(), "CC") == 0)) {
                        frame->setSw1(false);
                        frame->setSw2(false);
                        frame->setSw3(true);
                        frame->setSw4(true);
                        frame->setSw5(false);
                        frame->setSw6(false);
                    }
                }



        double t = frame->getBitLength() / datarate;
        cMessage *rxtim = new cMessage("RxEndTimer");

        if(inSwitch) {
            rxtim->setControlInfo(frame);
            scheduleAt(simTime()+t, rxtim);
            Frame_ricevute++;
            return;
        }



        cPacket *app_pkt = frame->decapsulate();
        AppControlInfo *ci = new AppControlInfo();

        ci->setSrc(frame->getSrc());
        ci->setDst(frame->getDst());
        app_pkt->setControlInfo(ci);

        rxtim->setControlInfo(app_pkt);
        Frame_ricevute++;
        scheduleAt(simTime()+t, rxtim);

        EV<<"deadline miss "<<deadlineMiss<<endl;
        EV<<"denominatore"<<(frame_trasmesse_nodo + frame_trasmesse_switch)<<endl;
        double dd =deadlineMiss/(frame_trasmesse_nodo + frame_trasmesse_switch);
        //EV<<"formulazza "<<dd<<endl;


        FILE *f;
        f = fopen("risultati.csv","a+");
            if(f != NULL)  {
               EV<<"file aperto"<<endl;
              fprintf(f,  "%s; %s; %s; %f; %f; %d; %d; %d; %d; %d; %d; %d; %d; %d; %f; %f; %f; %d\n",
                      frame->getNome(),
                      frame->getSrc(),
                      frame->getDst(),
                      frame->getPeriod().dbl(),
                      frame->getDeadlineR().dbl(),
                      frame->getPayload(),
                      frame->getBurst(),
                      frame->getSw1(),
                      frame->getSw2(),
                      frame->getSw3(),
                      frame->getSw4(),
                      frame->getSw5(),
                      frame->getSw6(),
                      frame->getPri(),
                      dd,
                      frame->getE2eMax().dbl(),
                      frame->getE2eAvg().dbl(),
                      Frame_ricevute
                      );
              fclose(f);
            } else
              EV<<"Errore apertura file"<<endl;
             delete frame;

    }



void EthNIC::reorderQueue() {
    int txLength = 0;
    int dimCoda = txqueue.length();

    if(dimCoda > 1) {
        for(int i=0; i<dimCoda; i++) {
            cPacket *frame = txqueue.pop();
            tempQueue[i] = check_and_cast<EthFrame *>(frame);
            txLength++;
        }

        EthFrame *t = new EthFrame;

        for(int i=0; i<(txLength-1); i++) {
            int min = i;
            for(int j=i+1; j<txLength; j++) {

                if(tempQueue[j]->getPriority() < tempQueue[min]->getPriority()) {
                    min = j;
                }
            }
            t = tempQueue[i];
            tempQueue[i] = tempQueue[min];
            tempQueue[min] = t;
}

        txqueue.insert(tempQueue[txLength-1]);
        for(int i=0; i<txLength-1; i++) {
            txqueue.insertAfter(txqueue.back(), tempQueue[i]);
        }
    }
}

void EthNIC::transmit() {
    if(txstate == TX_STATE_IDLE) {
        if(!txqueue.empty()) {



            cPacket *frame = txqueue.pop();
            send(frame, "channelOut");
            txstate = TX_STATE_TRANSMITTING;
            double t = frame->getBitLength() / datarate;
            cMessage *txtimer = new cMessage("TxEndTimer");
            scheduleAt(t + simTime(), txtimer);
        }



        simsignal_t sig;
        sig = registerSignal("FLR");
        emit(sig, frame_scartate/(frame_trasmesse_nodo + frame_trasmesse_switch));

        sig = registerSignal("Frame_trasmesse");
        emit(sig, (frame_trasmesse_nodo + frame_trasmesse_switch));

        sig = registerSignal("Frame_scartate");
        emit(sig, frame_scartate);

        sig = registerSignal("DMR");
        emit(sig, deadlineMiss/(frame_trasmesse_nodo + frame_trasmesse_switch));

    }
}
