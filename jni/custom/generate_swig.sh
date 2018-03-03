#! /bin/sh
#
# generate_swig.sh
# Copyright (C) 2018 kychen <keyu.chen@yitu-inc.com>
#
# Distributed under terms of the MIT license.
#


swig -c++ -java -package com.example.zgzhu.rstptoyuvdemo -outdir /home/kychen/RSTPtoYUVDemo/app/src/main/java/com/example/zgzhu/rstptoyuvdemo -o rtsp_decode_client_swig.cpp rtsp_decode_client.i
