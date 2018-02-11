EXENAME = ft_ssl
LIBFTSSLDIR = ./libft_ssl
LIBFTDIR = ./libft
ODIR = ./obj

FLAGS = -Wall -Wextra -Werror

# COLORS

BLACK = '\033[0;30m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
BROWN = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
LGRAY = '\033[0;37m'
DGRAY = '\033[1;30m'
LRED = '\033[1;31m'
LGREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
LCYAN = '\033[1;36m'
WHITE = '\033[1;37m'
NC = '\033[0m'

# LIBFT

LIBFT_DIR = libft
LIBFT_NAME = libft.a
LIBFT_SRCDIR = $(LIBFTDIR)/sources
LIBFT_INCDIR = $(LIBFTDIR)/includes

LIBFT_HEADNAMES =	libft \
					ft_printf
LIBFT_HEADERS = $(patsubst %, $(LIBFT_INCDIR)/%.h, $(LIBFT_HEADNAMES))

LIBFT_FILENAMES =	ft_putnbr ft_putchar ft_putstr ft_isalpha ft_atoi ft_bzero \
		ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_memccpy \
		ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_strchr ft_strcmp \
		ft_strlen ft_strncmp ft_strnstr ft_strstr ft_tolower ft_toupper \
		ft_strrchr ft_strdup ft_strcpy ft_strncpy  ft_strcat ft_strncat \
		ft_strlcat ft_memalloc ft_memdel ft_strnew ft_strdel ft_strclr \
		ft_striter ft_striteri  ft_strmap ft_strmapi ft_strequ  ft_strnequ \
		ft_strsub ft_strjoin ft_strtrim ft_strsplit ft_itoa  ft_putendl \
		ft_putnbr ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_lstnew \
		ft_lstdelone ft_lstdel  ft_lstadd ft_lstiter ft_lstmap ft_abs ft_atol \
		ft_strtol ft_ctoi_base ft_itoa_base ft_torot13 ft_isspace ft_lstappend \
		ft_putlst ft_lstsize ft_lstrev ft_lstfree ft_slen ft_strtok ft_strtoutf8 \
		ft_gnl ft_isupper ft_wchrlen ft_wcstombs ft_wctomb ft_wcslen ft_printf \
		ft_dprintf ft_sprintf ft_printf_convertors ft_printf_lst ft_printf_tools \
		ft_printf_parsers ft_printf_posargs ft_printf_put_misc ft_printf_put_numbers \
		ft_printf_put_strings ft_lstpush ft_startswith ft_endswith ft_sjoin

LIBFT_CFILES = $(patsubst %, $(LIBFT_SRCDIR)/%.c, $(LIBFT_FILENAMES))
LIBFT_OFILES = $(patsubst %, $(ODIR)/$(LIBFT_DIR)/%.o, $(LIBFT_FILENAMES))

# LIBFT_SSL

LIBSSL_DIR = libft_ssl
LIBSSL_NAME = libft_ssl.a
LIBSSL_SRCDIR = $(LIBFTSSLDIR)/sources
LIBSSL_INCDIR = $(LIBFTSSLDIR)/includes

LIBSSL_HEADNAMES = ft_ssl
LIBSSL_HEADERS = $(patsubst %, $(LIBSSL_INCDIR)/%.h, $(LIBSSL_HEADNAMES))

LIBSSL_FILENAMES =	arg_parse num_parse arg_display base64 des_ecb des_cbc
LIBSSL_CFILES = $(patsubst %, $(LIBSSL_SRCDIR)/%.c, $(LIBSSL_FILENAMES))
LIBSSL_OFILES = $(patsubst %, $(ODIR)/%.o, $(LIBSSL_FILENAMES))

all: $(LIBFT_NAME) $(LIBSSL_NAME) $(EXENAME)

$(LIBFT_NAME): $(ODIR) $(LIBFT_OFILES) $(LIBFT_HEADERS)
	@echo ${CYAN}"Compiling $(LIBFT_NAME)"${NC}
	@ar rc $(LIBFT_NAME) $(LIBFT_OFILES)
	@ranlib $(LIBFT_NAME)
	@echo ${GREEN}"[$(LIBFT_NAME) is up to date.]"${NC}

$(LIBSSL_NAME): $(ODIR) $(LIBSSL_OFILES) $(LIBSSL_HEADERS)
	@echo ${CYAN}[Compiling $(LIBSSL_NAME)]${NC}
	@ar rc $(LIBSSL_NAME) $(LIBSSL_OFILES)
	@ranlib $(LIBSSL_NAME)
	@echo ${GREEN}[$(LIBSSL_NAME) is up to date.]${NC}

$(ODIR)/%.o: $(LIBSSL_SRCDIR)/%.c $(LIBSSL_HEADERS)
	@gcc $(FLAGS) -o $@ -c $< -I$(LIBSSL_INCDIR) -I$(LIBFT_INCDIR)

$(ODIR)/$(LIBFT_DIR)/%.o: $(LIBFT_SRCDIR)/%.c $(LIBFT_HEADERS)
	@gcc $(FLAGS) -o $@ -c $< -I$(LIBFT_INCDIR)


$(ODIR):
	@mkdir -p $(ODIR)
	@mkdir -p $(ODIR)/$(LIBFT_DIR)
	@mkdir -p $(ODIR)/$(LIBSSL_DIR)

$(EXENAME): $(LIBSSL_NAME) $(LIBFT) main.c
	@echo ${CYAN}[Compiling $(EXENAME)]${NC}
	@gcc $(FLAGS) -o $(EXENAME) -I $(LIBSSL_INCDIR) -I$(LIBSSL_INCDIR) -I$(LIBFT_INCDIR) -L. -lft_ssl -lft main.c
	@echo ${GREEN}"[--------| $(EXENAME) is up to date. |---------]"${NC}

clean:
	@echo ${RED}"[Removing *.o files]"${NC}
	@/bin/rm -rf $(ODIR)

fclean:
	@echo ${RED}"[Removing $(LIBFT_NAME)]"${NC}
	@/bin/rm -f $(LIBFT_NAME)
	@echo ${RED}"[Removing $(LIBSSL_NAME)]"${NC}
	@/bin/rm -f $(LIBSSL_NAME)
	@echo ${RED}"[Removing $(EXENAME)]"${NC}
	@/bin/rm -f $(EXENAME)

re: fclean all
