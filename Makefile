# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::PATHS::

PROJ	:=	

ODIR	:=	objs

SDIR	:=	srcs

IDIR	:=	inc

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::TARGET::

NAME	:=	webserv

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::SOURCES::

SRCS	:=	webserv.cpp \
			Server.cpp \
			Epoll.cpp \
			Socket.cpp
			
OBJS	=	$(addprefix $(ODIR)/, $(SRCS:.cpp=.o))

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::COMPILERS::

CPP		:=	c++

WFLAGS	:=	-MMD -Wall -Wextra -Werror -std=c++98

WCONV	:=	-Wconversion

GFLAG	:=	-g3

SANFLAG	:=	-fsanitize=address

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::COLORS::

NO_COLOR		=	\033[m

BLACK			=	\033[0;30m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
ORANGE 		 	=	\033[0;33m
BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
CYAN			=	\033[0;36m
WHITE			= 	\033[0;37m

# High Intensty
HIGREEN			=	\033[0;92m
HIORANGE	 	=	\033[0;93m
HIPURPLE		=	\033[0;95m

# Bold
BORANGE 		=	\033[1;33m
BBLUE			=	\033[1;34m
BPURPLE			=	\033[1;35m
BCYAN			=	\033[1;36m

# Bold High Intensity
BHIBLACK		=	\033[1;30m
BHIRED			=	\033[1;91m
BHIGREEN		=	\033[1;92m
BHIORANGE		=	\033[1;33m
BHIYELLOW	 	=	\033[1;93m
BHIBLUE		 	=	\033[1;94m
BHIPURPLE		=	\033[1;35m
BHIPINK			=	\033[1;95m
BHICYAN			=	\033[1;96m
BHIWHITE		=	\033[1;37m

# Italic
ICYAN			=	\033[3;36m

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::PARAMS::

INCLUDE_FLAGS		= $(addprefix -I , $(IDIR))
DEPS				= $(OBJS:.o=.d)

vpath %.cpp $(SDIR)
vpath %.o $(ODIR)

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::MANDATORY::

all:			header h2 message $(NAME)

$(ODIR)/%.o:	%.cpp
	@$(CPP) $(WFLAGS) $(INCLUDE_FLAGS) -c $< -o $@ 
	@echo "$(HIGREEN)compilation:\t\t\t\t\t\t[OK]$(NO_COLOR)"

$(NAME):		$(OBJS)	
	@$(CPP) $(WFLAGS) $(OBJS) -o $(NAME)
	@echo "$(HIGREEN)mandatory exe:\t\t\t\t\t\t[OK]$(NO_COLOR)"

$(OBJS):		| $(ODIR)

$(ODIR):
	@mkdir -p $(ODIR)
	@echo "$(HIGREEN)objs folder:\t\t\t\t\t\t[OK]$(NO_COLOR)"
	

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::RULES::

update:		header fclean
	@git pull

push:		header fclean
	@echo "$(HIGREEN)"
	@git add .
	@git commit --quiet
	@git push --quiet
	@echo "$(HIGREEN)git push:\t\t\t\t\t\t[OK]$(NO_COLOR)"

clean:		header
	@rm -rf $(ODIR)
	@echo "$(HIORANGE)objs folder:\t\t\t\t\t\t[RM]$(NO_COLOR)"

fclean:		header clean
	@rm -f $(NAME)
	@echo "$(HIORANGE)$(NAME) bin:\t\t\t\t\t\t[RM]$(NO_COLOR)"

header:
	@echo " ______________________________________________________"
	@echo "|\     $(BHIRED)__________    ________    ___   ___    _______ $(NO_COLOR) \ "
	@echo "| \   $(BHIORANGE)/\         \  /\   __  \  /\  \ /\  \  /\  ____\ $(NO_COLOR) \ "
	@echo "|  \  $(BHIGREEN)\ \  \ _/\  \ \ \   __  \ \ \  \ /_ /_ \ \  _\_/_ $(NO_COLOR) \ "
	@echo "|   \  $(BHIBLUE)\ \__\_/ \__\ \ \__\-\__\ \ \__\  \__\ \ \______\ $(NO_COLOR) \ "
	@echo "|    \  $(BHIPURPLE)\/__/  \/__/  \/__/ /__/  \/__/ \/__/  \/______/ $(NO_COLOR)  \ "
	@echo "|     \_____________________________________________________\ "
	@echo "|     /$(BLACK)///////////////////////////////////////////////////$(NO_COLOR)/$(BLACK)/$(NO_COLOR)/ "
	@echo "|    /                   S E O Z C A N                   / / "
	@echo "|   /                   N F A U C O N N                 / / "
	@echo "|  /                   A T H I E R R Y                 / / "
	@echo "| /___________________________________________________/ / "
	@echo "|/____________________________________________________\/ "
	@echo ""

h2:
	@echo "\n$(BHIPURPLE):::::::::::::::::::::::::::::::::::::::::::::::::::WEBSERV::\n$(NO_COLOR)"

message:
	@make -q $(NAME) && echo "$(BHIGREEN)All files are already up to date$(NO_COLOR)" || true

re:		header fclean 
	@make all 

-include $(DEPS)

.PHONY:	all bonus clean fclean re push update o_dir h1 h2 header 
