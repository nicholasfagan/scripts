#!/bin/bash
if [ ! -f "$1" ]; then
	echo "'$1' is not a file" >&2
	exit 1
fi


real=$(realpath "$1")
fn=$(basename -- "$1")
ex="${fn##*.}"
bn="${fn%.*}"

case "$ex" in
	"c")  $real "${@:2}";;
	"py") python "$real" "${@:2}" ;;
	"js") node "$real" "${@:2}" ;;
	"sh") $real "${@:2}";;
	"html") chromium $real "${@:2}";;
	"pdf") zathura $real "${@:2}";;
	*) $real "${@:2}";;
esac

