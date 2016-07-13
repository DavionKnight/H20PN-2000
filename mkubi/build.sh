#!/bin/bash
#
#  COPYRIGHT NOTICE
#  Copyright (C) 2016 HuaHuan Electronics Corporation, Inc. All rights reserved
#
#  Author       	:Kevin_fzs
#  File Name        	:/home/kevin/works/projects/H20PN-2000/mkubi\build.sh
#  Create Date        	:2016/07/13 10:11
#  Last Modified      	:2016/07/13 10:11
#  Description    	:
#

mkfs.ubifs -r ./bin -m 2048 -e 126976  -c  6979 -o p2000-ubi.fs 

cp p2000-ubi.fs /tftpboot/p2000-ubi.fs
