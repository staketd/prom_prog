while [ $# -gt 0 ]; do
	case "$1" in
		--input*)
			file=$2
			shift 2
			;;
		--column*)
			column=$2
			shift 2
			;;
		--folder*)
			folder=$2
			shift 2
			;;
		--workers*)
			workers=$2
			shift 2
			;;
		*)
			printf "Invalid argument $1"
			exit 1
	esac
done
rm -r $folder
mkdir $folder > /dev/null

folder=$(realpath $folder)


awk -vcol=$column '{print $col}' $file

awk -vcol=$column '{print $col}' $file | parallel -j $workers wget -q -P $folder {}
exit 0