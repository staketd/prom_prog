# Counts number of different words in column
reducers=1
rm result >/dev/null
rm groupped >/dev/null
rm mapped >/dev/null
while [ $# -gt 0 ]; do
	case "$1" in
		--input*)
			file=$2
			shift 2
			;;
		--y_column*)
			y_column=$2
			shift 2
			;;
		--reducers*)
			reducers=$2
			shift 2
			;;
		*)
			printf "Invalid argument $1"
			exit 1
	esac
done


column_no=$(head -n 1 $file | awk 'BEGIN {RS=","} {print NR " " $1 "\n"}' | awk -v stat=$y_column 'BEGIN{IGNORECASE = 1;} $2 ~ stat {print $1}')

tail -n +2 $file | awk -vcol=$column_no -vFPAT="([^,]*)|(\".*\")" '{count[$col]++} END{for (word in count) {print word, count[word];}}' >> mapped 

awk '{mapped[$1]=mapped[$1] " " $2} END{for (key in mapped) {print key, mapped[key];}}' mapped > groupped # in case we have multiple mappers

cat groupped | parallel --pipe -j $reducers awk --file=reduce.awk >>result
