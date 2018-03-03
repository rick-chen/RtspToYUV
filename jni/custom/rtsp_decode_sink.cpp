/*
 * rtsp_decode_sink.cpp
 * Copyright (C) 2018 kychen <keyu.chen@yitu-inc.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "rtsp_decode_sink.h"


#define DUMMY_SINK_RECEIVE_BUFFER_SIZE 100000

RtspDecodeSink* RtspDecodeSink::createNew(UsageEnvironment& env, MediaSubsession& subsession, char* buffer, Frame_Callback callBack, char const* streamId) {
  return new RtspDecodeSink(env, subsession, streamId, buffer, callBack);
}

RtspDecodeSink::RtspDecodeSink(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId, char* buffer, Frame_Callback callBack)
  : MediaSink(env),
    fSubsession(subsession),
    mpUnit(buffer),
    mOnFrameCallback(callBack)
{
  fStreamId = strDup(streamId);
  fReceiveBuffer = new u_int8_t[DUMMY_SINK_RECEIVE_BUFFER_SIZE];
}

RtspDecodeSink::~RtspDecodeSink() {
    LOGD("###sink destruct");
  delete[] fReceiveBuffer;
  delete[] fStreamId;
}

void RtspDecodeSink::afterGettingFrame(void* clientData, unsigned frameSize, unsigned numTruncatedBytes,
				  struct timeval presentationTime, unsigned durationInMicroseconds) {
  RtspDecodeSink* sink = (RtspDecodeSink*)clientData;
  sink->afterGettingFrame(frameSize, numTruncatedBytes, presentationTime, durationInMicroseconds);
}

// If you don't want to see debugging output for each received frame, then comment out the following line:
#define DEBUG_PRINT_EACH_RECEIVED_FRAME 1

void RtspDecodeSink::afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
				  struct timeval presentationTime, unsigned /*durationInMicroseconds*/) {
  // We've just received a frame of data.  (Optionally) print out information about it:
    LOGD("####after getting frame");
#ifdef DEBUG_PRINT_EACH_RECEIVED_FRAME
  mpUnit[0] = 0x00;
  mpUnit[1] = 0x00;
  mpUnit[2] = 0x00;
  mpUnit[3] = 0x01;
  memcpy(mpUnit+4, fReceiveBuffer, frameSize); 
  LOGD("### size : %d", frameSize);
  mOnFrameCallback(mpUnit, frameSize);
  /*
  fout.open("test.image", std::ios::binary);
  fout.write((char *)buffer, frameSize + 4);
  */
  LOGD("####ready to write frames");
  /*
  FILE *f = fopen("/sdcard/test.image", "a");
  fwrite(buffer, 1, frameSize + 4, f);
  fclose(f);
  */ 
  if (fStreamId != NULL) envir() << "Stream \"" << fStreamId << "\"; ";
  envir() << fSubsession.mediumName() << "/" << fSubsession.codecName() << ":\tReceived " << frameSize << " bytes " ;
  if (numTruncatedBytes > 0) envir() << " (with " << numTruncatedBytes << " bytes truncated)";
  char uSecsStr[6+1]; // used to output the 'microseconds' part of the presentation time
  sprintf(uSecsStr, "%06u", (unsigned)presentationTime.tv_usec);
  envir() << ".\tPresentation time: " << (int)presentationTime.tv_sec << "." << uSecsStr;
  if (fSubsession.rtpSource() != NULL && !fSubsession.rtpSource()->hasBeenSynchronizedUsingRTCP()) {
    envir() << "!"; // mark the debugging output to indicate that this presentation time is not RTCP-synchronized
  //free(buffer);
  }
#ifdef DEBUG_PRINT_NPT
  envir() << "\tNPT: " << fSubsession.getNormalPlayTime(presentationTime);
#endif
  envir() << "\n";
#endif
  
  // Then continue, to request the next frame of data:
  continuePlaying();
}

void RtspDecodeSink::GetNALU(char** data)
{
    LOGD("#####before get nalu");
    *data = (char*)malloc(sizeof(fReceiveBuffer));
    if (fReceiveBuffer == NULL) return;
    memcpy(*data, fReceiveBuffer, sizeof(fReceiveBuffer));
}
Boolean RtspDecodeSink::continuePlaying() {
  if (fSource == NULL) return False; // sanity check (should not happen)

  // Request the next frame of data from our input source.  "afterGettingFrame()" will get called later, when it arrives:
  fSource->getNextFrame(fReceiveBuffer, DUMMY_SINK_RECEIVE_BUFFER_SIZE,
                        afterGettingFrame, this,
                        onSourceClosure, this);
  return True;
}
