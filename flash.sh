#!/bin/sh

set -eux

. ../.venv/bin/activate

# Connect RPI with BOOTSEL pressed
west flash --runner uf2

deactivate