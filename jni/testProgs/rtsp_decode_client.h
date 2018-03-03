/*
 * rtsp_decode_client.h
 * Copyright (C) 2018 kychen <keyu.chen@yitu-inc.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef RTSP_DECODE_CLIENT_H
#define RTSP_DECODE_CLIENT_H

#include "our_rtsp_client.h"
#include "rtsp_decode_sink.h"
#include <string>

class RtspDecodeClient
{
public:
    RtspDecodeClient();
    virtual ~RtspDecodeClient();
    void OpenUrl(const std::string& progName, const std::string& rtspUrl);
};

#endif /* !RTSP_DECODE_CLIENT_H */
