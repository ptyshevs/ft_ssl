EXENAME = ft_ssl
LIBFTSSLDIR = ./libft_ssl
LIBFT_DIR = ./libft
ODIR = ./obj

include ${LIBFT_DIR}/colors.mk

FLAGS = -Wall -Wextra -Werror

# LIBFT

LIBFT_NAME = libft.a
LIBFT_INCDIR = $(LIBFT_DIR)/includes

# LIBFT_SSL

LIBSSL_DIR = libft_ssl
LIBSSL_NAME = libft_ssl.a
LIBSSL_SRCDIR = $(LIBFTSSLDIR)/sources
LIBSSL_INCDIR = $(LIBFTSSLDIR)/includes

LIBSSL_HEADNAMES = ft_ssl structures arg_tools tools permutations
LIBSSL_HEADERS = $(patsubst %, $(LIBSSL_INCDIR)/%.h, $(LIBSSL_HEADNAMES))

LIBSSL_FILENAMES =	arg_parser options_parser num_parse arg_display in_out_tools \
					base64 des_core des_ecb des_cbc des_tools des_tools_more \
					permutations des3_ecb des3_cbc
LIBSSL_CFILES = $(patsubst %, $(LIBSSL_SRCDIR)/%.c, $(LIBSSL_FILENAMES))
LIBSSL_OFILES = $(patsubst %, $(ODIR)/%.o, $(LIBSSL_FILENAMES))

all: $(LIBFT_NAME) $(LIBSSL_NAME) $(EXENAME)

$(LIBFT_NAME):
	@make -C ${LIBFT_DIR}/

$(LIBSSL_NAME): $(ODIR) $(LIBSSL_OFILES) $(LIBSSL_HEADERS)
	@echo ${CYAN}[Compiling $(LIBSSL_NAME)]${NC}
	@ar rc $(LIBSSL_NAME) $(LIBSSL_OFILES)
	@ranlib $(LIBSSL_NAME)
	@echo ${GREEN}[$(LIBSSL_NAME) is up to date.]${NC}

$(ODIR)/%.o: $(LIBSSL_SRCDIR)/%.c $(LIBSSL_HEADERS)
	@gcc $(FLAGS) -o $@ -c $< -I$(LIBSSL_INCDIR) -I$(LIBFT_INCDIR)

$(ODIR):
	@mkdir -p $(ODIR)

$(EXENAME): $(LIBSSL_NAME) $(LIBFT_NAME) main.c
	@echo ${CYAN}[Compiling $(EXENAME)]${NC}
	@gcc $(FLAGS) -o $(EXENAME) -I $(LIBSSL_INCDIR) -I$(LIBSSL_INCDIR) -I$(LIBFT_INCDIR) -L. -lft_ssl -L ${LIBFT_DIR} -lft main.c
	@echo ${GREEN}"[--------| $(EXENAME) is up to date. |---------]"${NC}

clean:
	@make clean -C ${LIBFT_DIR}
	@echo ${RED}"[Removing *.o files]"${NC}
	@/bin/rm -rf $(ODIR)

fclean:
	@make fclean -C ${LIBFT_DIR}
	@echo ${RED}"[Removing $(LIBSSL_NAME)]"${NC}
	@/bin/rm -f $(LIBSSL_NAME)
	@echo ${RED}"[Removing $(EXENAME)]"${NC}
	@/bin/rm -f $(EXENAME)

re: fclean all
