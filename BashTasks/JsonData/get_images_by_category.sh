while [ $# -gt 0 ]; do
	case "$1" in
		--input*)
			file=$2
			shift 2
			;;
		--category_id*)
			category_id=$2
			shift 2
			;;
		*)
			printf "Invalid argument $1"
			exit 1
	esac
done

jq "[[.annotations[] | select(.category_id == $category_id)] | .[].image_id]" $file