#!/bin/bash

# Simple script to shudtown the raspberry pi after the robot program has been terminated
# This is a separate script from rc.local in order to be able to edit it while rc.local runs
shutdown -h now
