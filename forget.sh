#!/bin/bash
command=$1' '$2
echo $command
$command > $2'-512' &
disown %1
