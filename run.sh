if [ -e build/Vision2016 ]; then
	rm build/Vision2016
fi

(cd build && make)
./build/Vision2016
