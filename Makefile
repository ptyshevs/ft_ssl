EXENAME = ft_ssl
LIBFT_DIR = ./libft

include ${LIBFT_DIR}/colors.mk ${LIBFT_DIR}/constants.mk

# LIBFT

LIBFT_NAME = libft.a
LIBFT_DEPENDENCY = ${LIBFT_DIR}/${LIBFT_NAME}
LIBFT_INCDIR = $(LIBFT_DIR)/includes

# LIBFT_SSL

LIBSSL_SRCDIR = sources
LIBSSL_INCDIR = includes

LIBSSL_HEADNAMES = ft_ssl structures arg_tools tools permutations md5 sha
LIBSSL_INCDIR = includes
LIBSSL_HEADERS = $(addprefix $(LIBSSL_INCDIR)/, $(addsuffix .h, $(LIBSSL_HEADNAMES)))

LIBSSL_FILENAMES =	arg_parser options_parser num_parse dgst_parse \
					arg_display bit_tools sha256 \
					in_out_tools dgst_input_tools\
					base64 des_core des_ecb des_cbc des_tools des_tools_more \
					permutations des3_ecb des3_cbc \
					hash_dispatchers \
					md5 md5_communicate md5_hash_tools md5_setup \
					error_message main

LIBSSL_CFILES = $(patsubst %, $(LIBSSL_SRCDIR)/%.c, $(LIBSSL_FILENAMES))
LIBSSL_OFILES = $(addprefix $(ODIR)/, $(addsuffix .o, $(LIBSSL_FILENAMES)))


all: $(LIBFT_DEPENDENCY) $(ODIR) $(EXENAME)

$(LIBFT_DEPENDENCY):
	@make -C ${LIBFT_DIR}/

$(EXENAME): $(LIBSSL_DEPENDENCY) $(LIBFT_DEPENDENCY) ${LIBSSL_CFILES}
	@echo ${CYAN}[Compiling $(EXENAME)]${NC}
	@gcc $(FLAGS) -o $(EXENAME) $^ -I $(LIBSSL_INCDIR) \
	-I$(LIBFT_INCDIR) -L ${LIBFT_DIR} -lft
	@echo ${GREEN}"[--------| $(EXENAME) is up to date. |---------]"${NC}

$(ODIR)/%.o: libssl/sources/%.c $(LIBSSL_HEADERS)
	@gcc $(FLAGS) -o $@ -c $< -I$(LIBSSL_INCDIR) -I$(LIBFT_INCDIR)

$(ODIR):
	@mkdir -p $(ODIR)

clean:
	@make clean -C ${LIBFT_DIR}
	@echo ${RED}"[Removing *.o files]"${NC}
	@/bin/rm -rf $(ODIR)

fclean:
	@make fclean -C ${LIBFT_DIR}
	@echo ${RED}"[Removing $(EXENAME)]"${NC}
	@/bin/rm -f $(EXENAME)

re: fclean all
