/*
 * rtsp_common.h
 * Copyright (C) 2018 kychen <keyu.chen@yitu-inc.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef RTSP_COMMON_H
#define RTSP_COMMON_H


#include <android/log.h>

/*
 * LOG in Android
 */

#define LOG_TAG "native"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

#endif /* !RTSP_COMMON_H */
