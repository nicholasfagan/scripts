
if [ ! -f "$1" ]; then
	echo "'$1' is not a file" >&2
	exit 1
fi



fn=$(basename -- "$1")
ex="${fn##*.}"
bn="${fn%.*}"

case "$ex" in
	"c") gcc -o "$bn" "$1" -lm ;;
	"tex") pdflatex "$1" && biber "$1" && pdflatex "$1" && pdflatex "$1" ;;
esac

echo done
