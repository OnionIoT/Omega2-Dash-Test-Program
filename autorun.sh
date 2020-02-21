#!/bin/sh

# disable the blinking cursor
echo 0 > /sys/class/graphics/fbcon/cursor_blink

# path to test program
path="/mnt/sd*/o2dash-test"

# execute the test program
echo "" > /dev/ttyS0
echo "Running Omega2 Dash Test Program!" > /dev/ttyS0
echo "" > /dev/ttyS0

$($path)
