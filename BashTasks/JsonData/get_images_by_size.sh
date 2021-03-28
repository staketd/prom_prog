while [ $# -gt 0 ]; do
	case "$1" in
		--input*)
			file=$2
			shift 2
			;;
		--width*)
			width=$2
			shift 2
			;;
		--height*)
			height=$2
			shift 2
			;;
		*)
			printf "Invalid argument $1"
			exit 1
	esac
done

jq ".images[] | select(.width >= $width and .height >= $height)" $file