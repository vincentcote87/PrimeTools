#!/bin/bash
command=$1' '$2
echo $command
$command > $2'-192-catlight' &
disown %1
