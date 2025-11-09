#!/bin/sh

set -eux

cat /dev/ttyACM0 | tee temp.log