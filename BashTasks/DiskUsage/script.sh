#!/bin/bash

ls -Rla $1 | awk -f script.awk
