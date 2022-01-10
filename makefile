CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

Vulkan: Source/*.cpp Source/*.hpp
	g++ $(CFLAGS) -o Vulkan Source/*.cpp $(LDFLAGS)

.PHONY: test clean

test: 
	glslc Shaders/base_shader.vert -o Shaders/vert.spv
	glslc Shaders/base_shader.frag -o Shaders/frag.spv
	./Vulkan

clean:
	rm -f Vulkan
	rm -f Shaders/vert.spv
	rm -f Shaders/frag.spv
