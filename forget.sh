#!/bin/bash
command=$1' '$2
echo $command
$command > $2'-consecutive' &
disown %1
