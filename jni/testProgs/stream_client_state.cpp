/*
 * stream_client_state.cpp
 * Copyright (C) 2018 kychen <keyu.chen@yitu-inc.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "stream_client_state.h"



StreamClientState::StreamClientState()
  : iter(NULL), session(NULL), subsession(NULL), streamTimerTask(NULL), duration(0.0) {
}

StreamClientState::~StreamClientState() {
  delete iter;
  if (session != NULL) {
    // We also need to delete "session", and unschedule "streamTimerTask" (if set)
    UsageEnvironment& env = session->envir(); // alias

    env.taskScheduler().unscheduleDelayedTask(streamTimerTask);
    Medium::close(session);
  }
}

