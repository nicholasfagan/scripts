#!/bin/bash
tmpf=`mktemp`
outf=`mktemp`
onexit() {
	rm $tmpf $outf
	clear
	exit 0
}
trap onexit 2
	columns="$(tput cols)"
	rows="$(tput lines)"
	clear
	fortune -o > "$tmpf"
	tput bold>$outf
	nlines=0
	maxlen=0
	while IFS= read -r line; do
		if [ $maxlen -lt ${#line} ]; then
			maxlen=${#line}
		fi
		((nlines += 1))
	done <$tmpf
	padleft=$(( (columns - maxlen) / 2 ))
	padtop=$(( (rows - nlines) / 2 ))
	for _i in $(seq $padtop); do echo >>$outf; done
	while IFS= read -r line; do
		printf "%*s%s\n" $padleft " " "$line" >>$outf
	done <$tmpf
	lolcat $outf
	tput cup $rows $columns
while true; do
	columns="$(tput cols)"
	rows="$(tput lines)"
	fortune -o > "$tmpf"
	tput bold>$outf
	nlines=0
	maxlen=0
	while IFS= read -r line; do
		if [ $maxlen -lt ${#line} ]; then
			maxlen=${#line}
		fi
		((nlines += 1))
	done <$tmpf
	padleft=$(( (columns - maxlen) / 2 ))
	padtop=$(( (rows - nlines) / 2 ))
	for _i in $(seq $padtop); do echo >>$outf; done
	while IFS= read -r line; do
		printf "%*s%s\n" $padleft " " "$line" >>$outf
	done <$tmpf
#	cat $outf > $tmpf
#	lolcat -f $tmpf > $outf
	read read
	clear
	cat $outf
	tput cup $rows $columns
done
onexit
