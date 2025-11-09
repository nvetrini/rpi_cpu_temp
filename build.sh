#!/bin/sh

set -eux

. ../.venv/bin/activate

west build -b rpi_pico

deactivate