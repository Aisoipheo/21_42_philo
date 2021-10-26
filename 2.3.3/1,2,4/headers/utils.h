#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

size_t					my_strlen(const char *s);
int						is_num(char c);
int						my_atoi(const char *s, int *nb);
void					go_sleep(unsigned long long int ms);
unsigned long long int	get_unix_time(void);

#endif
