bin/RogueLike: bin-int/glm.o bin-int/Main.o bin-int/Window.o bin-int/stb_image.o bin-int/Map.o bin-int/Math.o bin-int/Time.o bin-int/Velocity.o bin-int/Rigidbody.o bin-int/Random.o bin-int/SpriteSheetManager.o bin-int/Shader.o bin-int/GameLoop.o bin-int/Input.o bin-int/Sprite.o bin-int/Renderer.o bin-int/MainMenu.o bin-int/GameScene.o bin-int/SpriteSheet.o bin-int/Animation.o bin-int/EntityManager.o bin-int/InteractSystem.o bin-int/CameraFollowSystem.o bin-int/PeonOrientationSystem.o bin-int/ItemPickupSystem.o bin-int/Entity.o 
	clang++  -lglfw -lGLEW -lGL   -o bin/RogueLike  bin-int/glm.o bin-int/Main.o bin-int/Window.o bin-int/stb_image.o bin-int/Map.o bin-int/Math.o bin-int/Time.o bin-int/Velocity.o bin-int/Rigidbody.o bin-int/Random.o bin-int/SpriteSheetManager.o bin-int/Shader.o bin-int/GameLoop.o bin-int/Input.o bin-int/Sprite.o bin-int/Renderer.o bin-int/MainMenu.o bin-int/GameScene.o bin-int/SpriteSheet.o bin-int/Animation.o bin-int/EntityManager.o bin-int/InteractSystem.o bin-int/CameraFollowSystem.o bin-int/PeonOrientationSystem.o bin-int/ItemPickupSystem.o bin-int/Entity.o 
bin-int/glm.o: ./deps/glm/include/glm/detail/glm.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./deps/glm/include/glm/detail/glm.cpp -o bin-int/glm.o
bin-int/Main.o: ./RogueLike/Source/Main.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Source/Main.cpp -o bin-int/Main.o
bin-int/Window.o: ./RogueLike/Source/Window.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Source/Window.cpp -o bin-int/Window.o
bin-int/stb_image.o: ./RogueLike/Vendor/stb_image/stb_image.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Vendor/stb_image/stb_image.cpp -o bin-int/stb_image.o
bin-int/Map.o: ./RogueLike/Headers/Map.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Map.cpp -o bin-int/Map.o
bin-int/Math.o: ./RogueLike/Headers/Math.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Math.cpp -o bin-int/Math.o
bin-int/Time.o: ./RogueLike/Headers/Time.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Time.cpp -o bin-int/Time.o
bin-int/Velocity.o: ./RogueLike/Headers/Components/Velocity.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Components/Velocity.cpp -o bin-int/Velocity.o
bin-int/Rigidbody.o: ./RogueLike/Headers/Components/Rigidbody.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Components/Rigidbody.cpp -o bin-int/Rigidbody.o
bin-int/Random.o: ./RogueLike/Headers/Random.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Random.cpp -o bin-int/Random.o
bin-int/SpriteSheetManager.o: ./RogueLike/Headers/SpriteSheetManager.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/SpriteSheetManager.cpp -o bin-int/SpriteSheetManager.o
bin-int/Shader.o: ./RogueLike/Headers/Shader.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Shader.cpp -o bin-int/Shader.o
bin-int/GameLoop.o: ./RogueLike/Headers/GameLoop.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/GameLoop.cpp -o bin-int/GameLoop.o
bin-int/Input.o: ./RogueLike/Headers/Input.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Input.cpp -o bin-int/Input.o
bin-int/Sprite.o: ./RogueLike/Headers/Sprite.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Sprite.cpp -o bin-int/Sprite.o
bin-int/Renderer.o: ./RogueLike/Headers/Renderer.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Renderer.cpp -o bin-int/Renderer.o
bin-int/MainMenu.o: ./RogueLike/Headers/Scenes/MainMenu.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Scenes/MainMenu.cpp -o bin-int/MainMenu.o
bin-int/GameScene.o: ./RogueLike/Headers/Scenes/GameScene.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Scenes/GameScene.cpp -o bin-int/GameScene.o
bin-int/SpriteSheet.o: ./RogueLike/Headers/SpriteSheet.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/SpriteSheet.cpp -o bin-int/SpriteSheet.o
bin-int/Animation.o: ./RogueLike/Headers/Animation.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Animation.cpp -o bin-int/Animation.o
bin-int/EntityManager.o: ./RogueLike/Headers/EntityManager.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/EntityManager.cpp -o bin-int/EntityManager.o
bin-int/InteractSystem.o: ./RogueLike/Headers/Systems/InteractSystem.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Systems/InteractSystem.cpp -o bin-int/InteractSystem.o
bin-int/CameraFollowSystem.o: ./RogueLike/Headers/Systems/CameraFollowSystem.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Systems/CameraFollowSystem.cpp -o bin-int/CameraFollowSystem.o
bin-int/PeonOrientationSystem.o: ./RogueLike/Headers/Systems/PeonOrientationSystem.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Systems/PeonOrientationSystem.cpp -o bin-int/PeonOrientationSystem.o
bin-int/ItemPickupSystem.o: ./RogueLike/Headers/Systems/ItemPickupSystem.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Systems/ItemPickupSystem.cpp -o bin-int/ItemPickupSystem.o
bin-int/Entity.o: ./RogueLike/Headers/Entity.cpp
	clang++ -std=c++17 -c -Ideps/GLEW/include -Ideps/GLFW/include -Ideps/glm/include -Ideps/irrKlang/include -IRogueLike/Vendor -ITabasco/src -IRogueLike/  ./RogueLike/Headers/Entity.cpp -o bin-int/Entity.o
