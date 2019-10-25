all: debug release

debug:
	g++ -std=c++11 settings.cpp -g -o settings_debug

release:
	g++ -std=c++11 settings.cpp -Ofast -DNDEBUG -o settings_release

clean:
	rm settings_debug settings_release
