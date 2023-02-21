#!/bin/bash

./ioparse ${1} & ./perfparse ${1} & ./raplparse ${1}
