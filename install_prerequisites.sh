#!/bin/bash
username=${username:-root}

git clone https://github.com/DaveGamble/cJSON.git
cd cJSON && make all && sudo -u $username make install
cd .. && rm -rf cJSON
sudo -u $username /sbin/ldconfig -v