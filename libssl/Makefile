LIBFT_DIR = ../libft
include ${LIBFT_DIR}/colors.mk ${LIBFT_DIR}/constants.mk

LIBFT_INCDIR = $(LIBFT_DIR)/includes

LIBSSL_NAME = libssl.a
LIBSSL_SRCDIR = sources
LIBSSL_INCDIR = includes

LIBSSL_HEADNAMES = ft_ssl structures arg_tools tools permutations
LIBSSL_HEADERS = $(patsubst %, $(LIBSSL_INCDIR)/%.h, $(LIBSSL_HEADNAMES))

LIBSSL_FILENAMES =	arg_parser options_parser num_parse arg_display in_out_tools \
					base64 des_core des_ecb des_cbc des_tools des_tools_more \
					permutations des3_ecb des3_cbc
LIBSSL_CFILES = $(patsubst %, $(LIBSSL_SRCDIR)/%.c, $(LIBSSL_FILENAMES))
LIBSSL_OFILES = $(patsubst %, $(ODIR)/%.o, $(LIBSSL_FILENAMES))

all: ${LIBSSL_NAME}

$(LIBSSL_NAME): $(ODIR) ${LIBSSL_OFILES} $(LIBSSL_HEADERS)
	@ar rc ${LIBSSL_NAME} ${LIBSSL_OFILES}
	@ranlib ${LIBSSL_NAME}

$(ODIR)/%.o: $(LIBSSL_SRCDIR)/%.c $(LIBSSL_HEADERS)
	@/bin/echo -n "."
	@$(CC) $(FLAGS) -o $@ -c $< -I$(LIBSSL_INCDIR) -I$(LIBFT_INCDIR)

$(ODIR):
	@mkdir -p $(ODIR)

clean:
	@echo ${RED}"[Removing *.o files]"${NC}
	@/bin/rm -rf $(ODIR)

fclean: clean
	@echo ${RED}"[Removing $(LIBSSL_NAME)]"${NC}
	@/bin/rm -f ${LIBSSL_NAME}

re: fclean all
