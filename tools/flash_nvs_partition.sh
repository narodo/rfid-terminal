#!/bin/bash
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
cd $SCRIPT_DIR

ESPTOOL=$HOME/.platformio/packages/framework-arduinoespressif32/tools/esptool.py
USB_PORT=/dev/ttyUSB0

NVS_PARTITION_KEYS="../nvs_partition.cvs"
NVS_PARTITION_FILE="./temp/nvs_settings.bin"
NVS_PART_START=0x9000
NVS_PART_SIZE=0x4000

python3 -m venv ./venv
source ./venv/bin/activate 
pip3 install future protobuf cryptography pyserial

python ./nvs_partition_gen.py generate $NVS_PARTITION_KEYS $NVS_PARTITION_FILE $NVS_PART_SIZE

python $ESPTOOL --port $USB_PORT write_flash $NVS_PART_START $NVS_PARTITION_FILE 
