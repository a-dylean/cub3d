#include "cub3d.h"

// Function to check if a character is '1' or space
int is_valid_char(char c) {
    return c == '1' || c == ' ';
}

int	ft_strspn(const char *s, const char *accept)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (ft_strchr(accept, s[i]) == 0)
			break;
		++i;
	}
	return (i);
}

int empty_or_spaces_only(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!str)
        return (1);
    while (str[i])
    {
        while (SPACES[j])
        {
            if (str[i] != SPACES[j])
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int first_and_last_char_check(char *str)
{
    // int i;
    int line_len;

    // i = 0;
    line_len = ft_strlen(str);
    while (*str)
    {
      
        while(ft_isspace(*str))
            str++;
        if (*str != '1')
            return (0);
        str++;
    }
    printf("last_char: %c\n", str[line_len]);
    if (str[line_len] != '1')
            return (0);
    return (1);
}

void validate_map(char** map, int height)
{
    int i;
    // int j;

    i = 0;
    // j = 0;
    if (height == 0)
        exit_with_error("Empty map!");
    while(i < height)
    {
         printf("LINE[%d]: %s\n", i, map[i]);
        i++;
       
    }
}