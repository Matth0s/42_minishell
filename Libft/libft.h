/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:31 by mmoreira          #+#    #+#             */
/*   Updated: 2021/09/21 22:37:16 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <sys/resource.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# define BUFFER_SIZE 42

typedef struct s_list
{
	struct s_list	*prev;
	void			*vol;
	struct s_list	*next;
}					t_list;

typedef struct s_flag
{
	int				sin;
	int				zero;
	int				width;
	int				press;
	int				j;
}					t_flag;

char				*ft_addchar(char *str, char c);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_itoa_base(int n, char *base);
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_utoa_base(unsigned int n, char *base);
char				*ft_utoa(unsigned int n);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);

void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstloop_start(t_list **lst);
void				ft_lstloop_stop(t_list **lst);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstnew(void *vol);
t_list				*ft_lstfirst(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);

double				ft_atod(const char *nptr);
int					ft_atoi(const char *nptr);
void				ft_bzero(void *s, size_t n);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);

size_t				str_len(char *s);
size_t				str_copy(char *dst, char *src, size_t size);
char				*str_join(char *s1, char *s2);
char				*str_dup(char *s);
int					get_next_line(int fd, char **line);

int					print_address(va_list args, int *i, t_flag flag);
int					print_char(int c, int *i, t_flag flag);
int					print_hex(va_list args, int *i, t_flag flag, int sig);
int					print_int(va_list args, int *i, t_flag flag);
int					print_string(va_list args, int *i, t_flag flag);
int					print_uint(va_list args, int *i, t_flag flag);
void				while_print(char *str, int len, int sig);
void				init_struct(t_flag *flag);
int					check_flags(const char *str, va_list args, int *i);
int					print_type(const char *str, va_list args, int *i,
						t_flag flag);
int					ft_printf(const char *str, ...);

int					ft_check_base(char *base);
void				ft_free_split(char **str);
char				*ft_multi_strjoin(int len, ...);
int					ft_numlen(int unsigned base, int n);

#endif
