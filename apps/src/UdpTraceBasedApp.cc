

#include "./UdpTraceBasedApp.h"

using namespace inet;

void UdpTraceBasedApp::initialize(int stage)
{
    UdpBasicApp::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {

        // take first time from array
        startTime = 0;
    }
}


void UdpTraceBasedApp::processStart(){
    EV <<  "### START" << endl;
}

void UdpTraceBasedApp::processSend()
{
    sendPacket();
    // get next time from array;
    simtime_t nextSendTime = simTime() + 0.5;
    EV <<  "### " << nextSendTime << endl;

    // make sure to handle last array entry;
    if (nextSendTime < simTime()) {
        selfMsg->setKind(SEND);
        scheduleAt(nextSendTime, selfMsg);
    }
    else {
        selfMsg->setKind(STOP);
        scheduleAt(stopTime, selfMsg);
    }
}
