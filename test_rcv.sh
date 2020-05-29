#!/bin/bash

echo ""
echo "TEST #4 Receiving message"
(
    echo -ne "START_COMM\r\n/login\r\nchase\r\nEND_COMM\r\n"
    sleep 10
    echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
) | nc 127.0.0.1 4242