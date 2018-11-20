EXENAME = ft_ssl
LIBFTSSLDIR = ./libft_ssl
LIBFT_DIR = ./libft

include ${LIBFT_DIR}/colors.mk ${LIBFT_DIR}/constants.mk

# LIBFT

LIBFT_NAME = libft.a
LIBFT_DEPENDENCY = ${LIBFT_DIR}/${LIBFT_NAME}
LIBFT_INCDIR = $(LIBFT_DIR)/includes

# LIBFT_SSL

LIBSSL_NAME = libssl.a
LIBSSL_DIR = libssl
LIBSSL_DEPENDENCY = $(LIBSSL_DIR)/$(LIBSSL_NAME)
LIBSSL_INCDIR = ${LIBSSL_DIR}/includes

all: $(LIBFT_DEPENDENCY) $(LIBSSL_DEPENDENCY) $(EXENAME)

$(LIBFT_DEPENDENCY):
	@make -C ${LIBFT_DIR}/

$(LIBSSL_DEPENDENCY):
	@echo ${CYAN}[Compiling $(LIBSSL_NAME)]${NC}
	@make -C ${LIBSSL_DIR}/
	@echo ""
	@echo ${GREEN}[$(LIBSSL_NAME) is up to date.]${NC}

$(EXENAME): $(LIBSSL_DEPENDENCY) $(LIBFT_DEPENDENCY) ${ODIR}/main.o
	@echo ${CYAN}[Compiling $(EXENAME)]${NC}
	@gcc $(FLAGS) -o $(EXENAME) -I $(LIBSSL_INCDIR) -I$(LIBSSL_INCDIR) -I$(LIBFT_INCDIR) -L${LIBSSL_DIR} -lssl -L ${LIBFT_DIR} -lft main.c
	@echo ${GREEN}"[--------| $(EXENAME) is up to date. |---------]"${NC}

$(ODIR)/%.o: %.c $(LIBSSL_HEADERS)
	@gcc $(FLAGS) -o $@ -c $< -I$(LIBSSL_INCDIR) -I$(LIBFT_INCDIR)

$(ODIR):
	@mkdir -p $(ODIR)

clean:
	@make clean -C ${LIBFT_DIR}
	@make clean -C ${LIBSSL_DIR}
	@echo ${RED}"[Removing *.o files]"${NC}
	@/bin/rm -rf $(ODIR)

fclean:
	@make fclean -C ${LIBFT_DIR}
	@make fclean -C ${LIBSSL_DIR}
	@echo ${RED}"[Removing $(EXENAME)]"${NC}
	@/bin/rm -f $(EXENAME)

re: fclean all
