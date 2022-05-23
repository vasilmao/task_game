all: Makefile Game.out 

Game.out: Makefile obj/Game.o obj/CollisionManager.o obj/Tools.o obj/Scene.o obj/Registry.o obj/Api.o obj/EntityHandle.o obj/PlayerDrawer.o obj/Vector.o obj/Engine.o obj/Renderer.o 
	g++ obj/Game.o obj/CollisionManager.o obj/Tools.o obj/Scene.o obj/Registry.o obj/Api.o obj/EntityHandle.o obj/PlayerDrawer.o obj/Vector.o obj/Engine.o obj/Renderer.o -rdynamic -lm -lX11 -o Game.out

obj/CollisionManager.o: src/collision/CollisionManager.cpp \
 include/collision/CollisionManager.hpp \
 include/collision/CollisionTypes.hpp include/Vector.hpp \
 include/Tools.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/collision/CollisionManager.cpp -o obj/CollisionManager.o

obj/Tools.o: src/Tools.cpp include/Tools.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/Tools.cpp -o obj/Tools.o

obj/Scene.o: src/Scene.cpp include/Scene.hpp include/ecs/EntityHandle.hpp \
 include/ecs/Registry.hpp include/ecs/ComponentHolder.hpp \
 include/ecs/Generator.hpp include/ecs/Generator.ipp \
 include/ecs/ComponentHolder.ipp include/ecs/Registry.ipp \
 include/ecs/EntityHandle.ipp include/ecs/Api.hpp include/ecs/View.hpp \
 include/ecs/View.ipp include/ecs/Api.ipp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/Scene.cpp -o obj/Scene.o

obj/Registry.o: src/ecs/Registry.cpp include/ecs/Registry.hpp \
 include/ecs/ComponentHolder.hpp include/ecs/Generator.hpp \
 include/ecs/Generator.ipp include/ecs/ComponentHolder.ipp \
 include/ecs/Registry.ipp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/ecs/Registry.cpp -o obj/Registry.o

obj/Api.o: src/ecs/Api.cpp include/ecs/Api.hpp \
 include/ecs/EntityHandle.hpp include/ecs/Registry.hpp \
 include/ecs/ComponentHolder.hpp include/ecs/Generator.hpp \
 include/ecs/Generator.ipp include/ecs/ComponentHolder.ipp \
 include/ecs/Registry.ipp include/ecs/EntityHandle.ipp \
 include/ecs/View.hpp include/ecs/View.ipp include/ecs/Api.ipp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/ecs/Api.cpp -o obj/Api.o

obj/EntityHandle.o: src/ecs/EntityHandle.cpp include/ecs/EntityHandle.hpp \
 include/ecs/Registry.hpp include/ecs/ComponentHolder.hpp \
 include/ecs/Generator.hpp include/ecs/Generator.ipp \
 include/ecs/ComponentHolder.ipp include/ecs/Registry.ipp \
 include/ecs/EntityHandle.ipp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/ecs/EntityHandle.cpp -o obj/EntityHandle.o

obj/PlayerDrawer.o: src/drawers/PlayerDrawer.cpp \
 include/drawers/PlayerDrawer.hpp include/ecs/Api.hpp \
 include/ecs/EntityHandle.hpp include/ecs/Registry.hpp \
 include/ecs/ComponentHolder.hpp include/ecs/Generator.hpp \
 include/ecs/Generator.ipp include/ecs/ComponentHolder.ipp \
 include/ecs/Registry.ipp include/ecs/EntityHandle.ipp \
 include/ecs/View.hpp include/ecs/View.ipp include/ecs/Api.ipp \
 include/Renderer.hpp include/Engine.h include/Vector.hpp \
 include/Tools.hpp include/Components.hpp include/EntityTypes.hpp \
 include/collision/CollisionTypes.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/drawers/PlayerDrawer.cpp -o obj/PlayerDrawer.o

obj/Vector.o: src/Vector.cpp include/Vector.hpp include/Tools.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/Vector.cpp -o obj/Vector.o

obj/Engine.o: src/Engine.cpp include/Engine.h Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/Engine.cpp -o obj/Engine.o

obj/Renderer.o: src/Renderer.cpp include/Renderer.hpp include/Engine.h \
 include/Vector.hpp include/Tools.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/Renderer.cpp -o obj/Renderer.o

obj/Game.o: src/Game.cpp include/Engine.h include/Scene.hpp \
 include/ecs/EntityHandle.hpp include/ecs/Registry.hpp \
 include/ecs/ComponentHolder.hpp include/ecs/Generator.hpp \
 include/ecs/Generator.ipp include/ecs/ComponentHolder.ipp \
 include/ecs/Registry.ipp include/ecs/EntityHandle.ipp \
 include/ecs/Api.hpp include/ecs/View.hpp include/ecs/View.ipp \
 include/ecs/Api.ipp include/Components.hpp include/Vector.hpp \
 include/Tools.hpp include/Renderer.hpp include/EntityTypes.hpp \
 include/collision/CollisionTypes.hpp include/drawers/Drawers.hpp \
 include/drawers/PlayerDrawer.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c src/Game.cpp -o obj/Game.o

