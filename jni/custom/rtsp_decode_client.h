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
#include "rtsp_common.h"
#include <mutex>
/*
 * 用于JNI传递binary数据
 */
struct CData
{
    const void* data;
    int len;
};
/*
 * C++ to Android
 * OpenUrl启动解码rtsp为H264
 * GetNALU拿到每一个H264 NALU
 * 一定不要一个client打开不同的rtsp流，要打开新的就生成一个新的client对象完成
 */
class RtspDecodeClient
{
    public:
        RtspDecodeClient();
        virtual ~RtspDecodeClient();
        /*
         * @param progName tag符号
         * @param rtspUrl rtsp地址
         */
        void OpenUrl(const char* progName, const char* rtspUrl);
        /*
         * @param out data
         * 输出H264的基本单元
         */ 
        void GetNALU(CData& data);
        RtspDecodeSink* mpSink;
        char* mBuffer;
        int mBufferPos;
        bool mReadyToSend;
        clientId mId;
};

#endif /* !RTSP_DECODE_CLIENT_H */
