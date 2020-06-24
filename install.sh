

PARENT_DIR="$(pwd)"
mkdir -p lib

cd ./lib/

if ! [ -x "$(command -v gcc)" ]; then
	echo "Error: GCC is not installed." >&2
	echo "Please install GCC before continue!"
	exit 1
fi

if ! [ -x "$(command -v make)" ]; then
	echo "Error: GNU Make is not installed." >&2
	echo "Please install GNU make before continue!"
	exit 1
fi

make
make install

case "$(uname -s)" in
	CYGWIN*|MINGW32*|MINGW64*|MSYS*)
		echo "Configuring PATH for CYGWIN"
		source ~/.bashrc
		;;
	Darwin)
		echo 'Mac OS X'
		echo "Configuring LD_LIBRARY_PATH for MACOS"
		source ~/.bashrc
		;;
	Linux)
		echo 'Linux'
		echo "Configuring LD_LIBRARY_PATH for Ubuntu"
		source ~/.bashrc
		;;
	*)
		echo "Other OS. Skip"
		;;
esac

cd $PARENT_DIR