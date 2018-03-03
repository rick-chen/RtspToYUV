/*
 * RTSPDecoder.h
 * Copyright (C) 2018 kychen <keyu.chen@yitu-inc.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef RTSPDECODER_H
#define RTSPDECODER_H

#include "our_rtsp_client.h"
#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"

class RTSPDecoder
{
public:
    RTSPDecoder();
    virtual ~RTSPDecoder();
    int OpenURL(char const* progName, char const* rtspURL);
    void StartDecode();
private:
    TaskScheduler* mpScheduler;
    UsageEnvironment* mpEnv;
};

#endif /* !RTSPDECODER_H */
