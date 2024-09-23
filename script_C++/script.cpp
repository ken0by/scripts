#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void field_hpp(std::string path, std::string filename) {
	std::ofstream file(path + filename + ".hpp");
	if (!file) {
		std::cerr << "Error creating file: " << path << std::endl;
	}
	file << "#ifndef " << filename << "_HPP\n";
	file << "#define " << filename << "_HPP\n\n";
	file << "#include <iostream>\n";
	file << "#include <iomanip>\n\n";
	file << "class " << filename << "\n";
	file << "{\n";
	file << "    private:\n\n";
	file << "    public:\n";
	file << "        " << filename << "();\n";
	file << "        " << filename << "(const " << filename << "& constrCopy);\n";
	file << "        " << filename << "& operator=(const " << filename << "& constrCopy);\n";
	file << "        ~" << filename << "();\n";
	file << "};\n\n";
	file << "std::ostream& operator<<(std::ostream &output, const " << filename << "& constrCopy);\n\n";
	file << "#endif\n";
	file.close();
}

void field_cpp(std::string path, std::string filename) {
	std::ofstream file(path + filename + ".cpp");
	if (!file) {
		std::cerr << "Error creating file: " << path << std::endl;
	}
	file << "#include \"../include/" << filename << ".hpp\"\n\n";
	file << filename << "::" << filename << "()\n"
		 << "{\n"
		 << "}\n\n"; // Constructor
	file << filename << "::" << filename << "()\n"
		 << "{\n"
		 << "}\n\n";																   // Constructor parameter
	file << filename << "::" << filename << "(const " << filename << "& constrCopy)\n{\n\n}\n\n";  // Copy constructor
	file << filename << "& " << filename << "::operator=(const " << filename << "& constrCopy)\n"; // Assigned operator
	file << "{\n    if (this != &constrCopy)\n    {\n\n    }\n\n    return (*this);\n}\n\n";
	file << filename << "::" << "~" << filename << "()\n"
		 << "{\n"
		 << "}\n\n"; // Destructor
	file.close();
}

void create_main(std::string path, std::string filename) {
	std::ofstream file(path + "/src/main.cpp");
	if (!file) {
		std::cerr << "Error creating file: " << path << std::endl;
	}
	file << "#include \"../inc/" + filename + ".hpp\"\n\n";
	file << "int main() {\n	std::cout << \"Hello, " + filename + "!\" << std::endl;\n";
	file << "	return 0;\n}\n";
	file.close();
}

void create_makefile(std::string path, std::string name, std::string filename) {
	std::ofstream file(path + "/Makefile");
	if (!file) {
		std::cerr << "Error creating file: " << path << std::endl;
	}
	file << "RM	=	rm -f\n\n";
	file << "CC	=	g++\n";
	file << "CFLAGS	=	-Wall -Werror -Wextra -std=c++98 -I ./inc\n";
	file << "DEBUG	=	-g3 -fsanitize=address\n\n";
	file << "NAME	=	" + name + "\n\n";
	file << "SRC	=	main.cpp " + filename + ".cpp\n";
	file << "SRC_DIR	=	src/\n\n";
	file << "OBJ_DIR	=	./obj/\n";
	file << "OBJ_FILES	=	$(SRC:.cpp=.o)\n";
	file << "OBJ	=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))\n\n";
	file << "##########COLORES##########\n";
	file << "DEF_COLOR = \\033[0;39m\n";
	file << "CUT = \\033[K\n";
	file << "R = \\033[31;1m\n";
	file << "G = \\033[32;1m\n";
	file << "Y = \\033[33;1m\n";
	file << "B = \\033[34;1m\n";
	file << "P = \\033[35;1m\n";
	file << "GR = \\033[30;1m\n";
	file << "END = \\033[0m\n\n";
	file << "##########REGLAS##########\n";
	file << "all: $(OBJ_DIR) $(NAME)\n";
	file << "$(OBJ_DIR):\n";
	file << "	@mkdir -p $(OBJ_DIR)\n";
	file << "$(OBJ_DIR)\%.o:$(SRC_DIR)\%.cpp\n";
	file << "	@$(CC) $(CFLAGS) -c $< -o $@\n\n";
	file << "$(NAME): $(OBJ)\n";
	file << "	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)\n";
	file << "	@echo \"\n$(G)Program compiled!$(DEF_COLOR)-> $@\\n\"\n\n";
	file << "clean:\n";
	file << "	@$(RM) $(OBJ)\n";
	file << "	@$(RM) $(OBJ_DIR)\n";
	file << "	@echo \"$(R)All .o files removed$(DEF_COLOR)\\n\"\n\n";
	file << "fclean: clean\n";
	file << "	@$(RM) $(NAME)\n";
	file << "	@rm -rf $(OBJ_DIR)\n";
	file << "	@echo \"$(R)OBJ directory removed$(DEF_COLOR)\\n\"\n\n";
	file << "re: fclean all\n\n";
	file << ".PHONY: all clean fclean re\n";
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " <directory> <filename> <ejecutable_name>" << std::endl;
		return 1;
	}

	std::string project_path = argv[1];
	std::string filename = argv[2];
	std::string name = argv[3];

	// Create directories
	fs::create_directories(project_path + "/inc");
	fs::create_directories(project_path + "/src");

	// Create .hpp file
	field_hpp(project_path + "/inc/", filename);

	// Create .cpp file
	field_cpp(project_path + "/src/", filename);

	// Create main.cpp
	create_main(project_path, filename);

	// Create Makefile
	create_makefile(project_path, name, filename);

	std::cout << "Project structure created successfully!" << std::endl;

	return 0;
}
