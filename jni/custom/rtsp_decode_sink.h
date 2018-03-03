/*
 * rtsp_decode_sink.h
 * Copyright (C) 2018 kychen <keyu.chen@yitu-inc.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef RTSP_DECODE_SINK_H
#define RTSP_DECODE_SINK_H

#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "rtsp_common.h"

typedef void (*Frame_Callback)(char* pFrame, int size, const clientId& clientId);

class RtspDecodeSink : public MediaSink {
    public:
        static RtspDecodeSink* createNew(UsageEnvironment& env,
                MediaSubsession& subsession, // identifies the kind of data that's being received
                Frame_Callback callBack, const clientId& clientId, char const* streamId = NULL); // identifies the stream itself (optional)

    private:
        RtspDecodeSink(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId, Frame_Callback callBack, const clientId& clientId);
        // called only by "createNew()"
        virtual ~RtspDecodeSink();

        static void afterGettingFrame(void* clientData, unsigned frameSize,
                unsigned numTruncatedBytes,
                struct timeval presentationTime,
                unsigned durationInMicroseconds);
        void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
                struct timeval presentationTime, unsigned durationInMicroseconds);

    private:
        // redefined virtual functions:
        virtual Boolean continuePlaying();
        Frame_Callback mOnFrameCallback;

    private:
        u_int8_t* fReceiveBuffer;
        MediaSubsession& fSubsession;
        char* fStreamId;
        clientId mClientId;
};


#endif /* !RTSP_DECODE_SINK_H */
