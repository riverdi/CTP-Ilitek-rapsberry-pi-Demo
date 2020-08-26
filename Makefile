FORCE:
	mkdir build && \
	cd build/ && \
	cmake ../ && \
	make
	mv ilitek_on_raspberry_pi_demo ../

clean:
	rm -r build
