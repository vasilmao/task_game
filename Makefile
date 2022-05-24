all: Makefile game 

game: Makefile  obj/CollisionManager.o obj/CollisionResponce.o obj/Tools.o obj/InputHandler.o obj/ObjectSpawn.o obj/Scene.o obj/Registry.o obj/Api.o obj/EntityHandle.o obj/Game.o obj/EnemyDrawer.o obj/PlayerDrawer.o obj/Vector.o obj/Engine.o obj/PlayerEventHandler.o obj/Renderer.o 
	g++  obj/CollisionManager.o obj/CollisionResponce.o obj/Tools.o obj/InputHandler.o obj/ObjectSpawn.o obj/Scene.o obj/Registry.o obj/Api.o obj/EntityHandle.o obj/Game.o obj/EnemyDrawer.o obj/PlayerDrawer.o obj/Vector.o obj/Engine.o obj/PlayerEventHandler.o obj/Renderer.o -rdynamic -lm -lX11 -o game

obj/CollisionManager.o: src/collision/CollisionManager.cpp \
 include/collision/CollisionManager.hpp \
 include/collision/CollisionTypes.hpp include/Vector.hpp \
 include/Tools.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/collision/CollisionManager.cpp -o obj/CollisionManager.o

obj/CollisionResponce.o: src/collision/CollisionResponce.cpp \
 include/collision/CollisionResponce.hpp include/EntityTypes.hpp \
 include/ecs/Api.hpp include/ecs/EntityHandle.hpp \
 include/ecs/Registry.hpp include/ecs/ComponentHolder.hpp \
 include/ecs/Generator.hpp include/ecs/Generator.ipp \
 include/ecs/ComponentHolder.ipp include/ecs/Registry.ipp \
 include/ecs/EntityHandle.ipp include/ecs/View.hpp include/ecs/View.ipp \
 include/ecs/Api.ipp include/Components.hpp include/Vector.hpp \
 include/Tools.hpp include/Renderer.hpp include/Engine.h \
 include/collision/CollisionTypes.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/collision/CollisionResponce.cpp -o obj/CollisionResponce.o

obj/Tools.o: src/Tools.cpp include/Tools.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/Tools.cpp -o obj/Tools.o

obj/InputHandler.o: src/InputHandler.cpp include/InputHandler.hpp \
 include/Vector.hpp include/Tools.hpp \
 include/event_system/EventSystem.hpp include/event_system/Events.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/InputHandler.cpp -o obj/InputHandler.o

obj/ObjectSpawn.o: src/ObjectSpawn.cpp include/ObjectSpawn.hpp \
 include/ecs/Api.hpp include/ecs/EntityHandle.hpp \
 include/ecs/Registry.hpp include/ecs/ComponentHolder.hpp \
 include/ecs/Generator.hpp include/ecs/Generator.ipp \
 include/ecs/ComponentHolder.ipp include/ecs/Registry.ipp \
 include/ecs/EntityHandle.ipp include/ecs/View.hpp include/ecs/View.ipp \
 include/ecs/Api.ipp include/Vector.hpp include/Tools.hpp \
 include/Components.hpp include/Renderer.hpp include/Engine.h \
 include/EntityTypes.hpp include/collision/CollisionTypes.hpp \
 include/drawers/Drawers.hpp include/drawers/PlayerDrawer.hpp \
 include/drawers/EnemyDrawer.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/ObjectSpawn.cpp -o obj/ObjectSpawn.o

obj/Scene.o: src/Scene.cpp include/Scene.hpp include/ecs/EntityHandle.hpp \
 include/ecs/Registry.hpp include/ecs/ComponentHolder.hpp \
 include/ecs/Generator.hpp include/ecs/Generator.ipp \
 include/ecs/ComponentHolder.ipp include/ecs/Registry.ipp \
 include/ecs/EntityHandle.ipp include/ecs/Api.hpp include/ecs/View.hpp \
 include/ecs/View.ipp include/ecs/Api.ipp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/Scene.cpp -o obj/Scene.o

obj/Registry.o: src/ecs/Registry.cpp include/ecs/Registry.hpp \
 include/ecs/ComponentHolder.hpp include/ecs/Generator.hpp \
 include/ecs/Generator.ipp include/ecs/ComponentHolder.ipp \
 include/ecs/Registry.ipp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/ecs/Registry.cpp -o obj/Registry.o

obj/Api.o: src/ecs/Api.cpp include/ecs/Api.hpp \
 include/ecs/EntityHandle.hpp include/ecs/Registry.hpp \
 include/ecs/ComponentHolder.hpp include/ecs/Generator.hpp \
 include/ecs/Generator.ipp include/ecs/ComponentHolder.ipp \
 include/ecs/Registry.ipp include/ecs/EntityHandle.ipp \
 include/ecs/View.hpp include/ecs/View.ipp include/ecs/Api.ipp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/ecs/Api.cpp -o obj/Api.o

obj/EntityHandle.o: src/ecs/EntityHandle.cpp include/ecs/EntityHandle.hpp \
 include/ecs/Registry.hpp include/ecs/ComponentHolder.hpp \
 include/ecs/Generator.hpp include/ecs/Generator.ipp \
 include/ecs/ComponentHolder.ipp include/ecs/Registry.ipp \
 include/ecs/EntityHandle.ipp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/ecs/EntityHandle.cpp -o obj/EntityHandle.o

obj/Game.o: src/Game.cpp include/Engine.h include/Scene.hpp \
 include/ecs/EntityHandle.hpp include/ecs/Registry.hpp \
 include/ecs/ComponentHolder.hpp include/ecs/Generator.hpp \
 include/ecs/Generator.ipp include/ecs/ComponentHolder.ipp \
 include/ecs/Registry.ipp include/ecs/EntityHandle.ipp \
 include/ecs/Api.hpp include/ecs/View.hpp include/ecs/View.ipp \
 include/ecs/Api.ipp include/Components.hpp include/Vector.hpp \
 include/Tools.hpp include/Renderer.hpp include/EntityTypes.hpp \
 include/collision/CollisionTypes.hpp include/drawers/Drawers.hpp \
 include/drawers/PlayerDrawer.hpp include/drawers/EnemyDrawer.hpp \
 include/collision/CollisionManager.hpp \
 include/collision/CollisionResponce.hpp \
 include/event_system/EventSystem.hpp include/InputHandler.hpp \
 include/ObjectSpawn.hpp include/PlayerEventHandler.hpp \
 include/event_system/Events.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/Game.cpp -o obj/Game.o

obj/EnemyDrawer.o: src/drawers/EnemyDrawer.cpp \
 include/drawers/EnemyDrawer.hpp include/ecs/Api.hpp \
 include/ecs/EntityHandle.hpp include/ecs/Registry.hpp \
 include/ecs/ComponentHolder.hpp include/ecs/Generator.hpp \
 include/ecs/Generator.ipp include/ecs/ComponentHolder.ipp \
 include/ecs/Registry.ipp include/ecs/EntityHandle.ipp \
 include/ecs/View.hpp include/ecs/View.ipp include/ecs/Api.ipp \
 include/Renderer.hpp include/Engine.h include/Vector.hpp \
 include/Tools.hpp include/Components.hpp include/EntityTypes.hpp \
 include/collision/CollisionTypes.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/drawers/EnemyDrawer.cpp -o obj/EnemyDrawer.o

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
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/drawers/PlayerDrawer.cpp -o obj/PlayerDrawer.o

obj/Vector.o: src/Vector.cpp include/Vector.hpp include/Tools.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/Vector.cpp -o obj/Vector.o

obj/Engine.o: src/Engine.cpp include/Engine.h Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/Engine.cpp -o obj/Engine.o

obj/PlayerEventHandler.o: src/PlayerEventHandler.cpp \
 include/PlayerEventHandler.hpp include/ecs/Api.hpp \
 include/ecs/EntityHandle.hpp include/ecs/Registry.hpp \
 include/ecs/ComponentHolder.hpp include/ecs/Generator.hpp \
 include/ecs/Generator.ipp include/ecs/ComponentHolder.ipp \
 include/ecs/Registry.ipp include/ecs/EntityHandle.ipp \
 include/ecs/View.hpp include/ecs/View.ipp include/ecs/Api.ipp \
 include/event_system/Events.hpp include/Vector.hpp include/Tools.hpp \
 include/Components.hpp include/Renderer.hpp include/Engine.h \
 include/EntityTypes.hpp include/collision/CollisionTypes.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/PlayerEventHandler.cpp -o obj/PlayerEventHandler.o

obj/Renderer.o: src/Renderer.cpp include/Renderer.hpp include/Engine.h \
 include/Vector.hpp include/Tools.hpp Makefile
	g++ -I . -I ./include -I ./include/collision -I ./include/event_system -I ./include/ecs -I ./include/drawers -I ./src -I ./src/collision -I ./src/ecs -I ./src/drawers -Wall -std=c++17 -c ./src/Renderer.cpp -o obj/Renderer.o

