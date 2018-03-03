/*
 * stream_client_state.h
 * Copyright (C) 2018 kychen <keyu.chen@yitu-inc.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef STREAM_CLIENT_STATE_H
#define STREAM_CLIENT_STATE_H

#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"

class StreamClientState {
public:
  StreamClientState();
  virtual ~StreamClientState();

public:
  MediaSubsessionIterator* iter;
  MediaSession* session;
  MediaSubsession* subsession;
  TaskToken streamTimerTask;
  double duration;
};


#endif /* !STREAM_CLIENT_STATE_H */
