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
#include <vector>

class RtspDecodeSink : public MediaSink {
public:
  static RtspDecodeSink* createNew(UsageEnvironment& env,
			      MediaSubsession& subsession, // identifies the kind of data that's being received
			      char const* streamId = NULL, std::vector<char*>& buffer); // identifies the stream itself (optional)

private:
  RtspDecodeSink(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId, std::vector<char*>& buffer);
    // called only by "createNew()"
  virtual ~RtspDecodeSink();
  std::vector<char*> mBuffer;

  static void afterGettingFrame(void* clientData, unsigned frameSize,
                                unsigned numTruncatedBytes,
				struct timeval presentationTime,
                                unsigned durationInMicroseconds);
  void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
			 struct timeval presentationTime, unsigned durationInMicroseconds);

private:
  // redefined virtual functions:
  virtual Boolean continuePlaying();

private:
  u_int8_t* fReceiveBuffer;
  MediaSubsession& fSubsession;
  char* fStreamId;
};


#endif /* !RTSP_DECODE_SINK_H */
