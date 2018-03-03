/*
 * our_rtsp_client.h
 * Copyright (C) 2018 kychen <keyu.chen@yitu-inc.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef OUR_RTSP_CLIENT_H
#define OUR_RTSP_CLIENT_H


#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "stream_client_state.h"
/*
 * rtspclient的子类
 * 从demo移植过来的
 */
class OurRTSPClient: public RTSPClient 
{
public:
  static OurRTSPClient* createNew(UsageEnvironment& env, char const* rtspURL,
				  int verbosityLevel = 0,
				  char const* applicationName = NULL,
				  portNumBits tunnelOverHTTPPortNum = 0);

protected:
  OurRTSPClient(UsageEnvironment& env, char const* rtspURL,
		int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum);
    // called only by createNew();
  virtual ~OurRTSPClient();

public:
  StreamClientState scs;
};

#endif /* !OUR_RTSP_CLIENT_H */
