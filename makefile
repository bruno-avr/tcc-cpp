CXX = g++

# Define as flags de compilação
# CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
CXXFLAGS = -pedantic -std=c++17 -O3

# Define o nome do executável a ser gerado
EXECUTABLE = a.out

# Define o diretório para armazenar os arquivos .o
OBJECTS_DIR = objects

# Cria a lista de diretórios, se não existirem
DIRECTORIES = $(OBJECTS_DIR)

# Define a lista de arquivos .cpp a serem compilados
SOURCES = $(wildcard *.cpp)

# Define a lista de arquivos .o a serem gerados
OBJECTS = $(patsubst %.cpp,$(OBJECTS_DIR)/%.o,$(notdir $(SOURCES)))

# Regra para criar diretórios
$(DIRECTORIES):
	mkdir -p $@

# Regra para compilar todos os arquivos .cpp
all: $(DIRECTORIES) $(EXECUTABLE)

# Regra para gerar o executável
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regra para compilar cada arquivo .cpp individualmente
$(OBJECTS_DIR)/%.o: %.cpp | $(DIRECTORIES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos .o e o executável gerado
clean:
	rm -rf $(OBJECTS_DIR) $(EXECUTABLE)

rebuild:
	make clean && make all