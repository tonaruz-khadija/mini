/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:02:39 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/05 14:48:59 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
int ft_strlen(char *s)
{
    int i = 0;
    while(s && s[i])
        i++;
        return(i);
}
char	*ft_strttcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)

{
	char *srrc;
	char *dest;
	int i;

	srrc = (char *)src;
	i = 0;
	dest = (char *)malloc(sizeof(char) * ft_strlen(srrc) + 1);
	if (!dest)
		return (NULL);
	return (ft_strttcpy(dest, srrc));
}
char	*ft_strchr(const char *string, int r)
{
	char	*ptr;

	ptr = (char *)string;
	while (*ptr != (char)r && *ptr != '\0')
		ptr++;
	if (*ptr == (char)r)
		return (ptr);
	return (0);
}
char	*ft_strjoina(char  *s1, char  *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	p = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 2);
	while (p && s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (p && s2 && s2[j])
		p[i++] = s2[j++];
	if (p)
		p[i] = 0;
	return (p);
}



char	*ft_substr(char const *s, unsigned int start, size_t len)

{
	unsigned int j;
	char *str;

	if (!s)
		return (0);
	if (start >= strlen(s))
		return (strdup(""));
	else
	{
		if (len > strlen(s))
			len = strlen(s) - start;
		j = 0;
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (!str)
			return (NULL);
		while (s[start] && j < len)
			str[j++] = s[start++];
		str[j] = '\0';
	}
	return (str);
}
char    *trim_quotes(char *s,int *j,char c)
{
    int start= 0;
    int end = 0;
	char *str;
	if (c == '0')
	{
		start = *j;
   		while (s[*j] && s[*j] != '\"' && s[*j] != '\'')
        	(*j)++;
    	end = *j;
    	str = ft_substr(s, start, end - start);
    	if (s[*j])
        	(*j)--;
    	return (str);
	}
    (*j)++;
        start = *j;
        while (s[*j] != c)
            (*j)++;
        end = (*j);
        str = ft_substr(s, start, end - start);
        return (str);
}
char *skip_quot_exp(char *s)
{
    int i = 0;
	int j = 0;
    char *str;
    char *tmp;
    while(s[i])
    {
        if(s[i] == '\'')
        {
            tmp = ft_strjoina(str,trim_quotes(s,&i,'\''));
            str = tmp;
        }
        else if(s[i] == '\"')
        {
            tmp = ft_strjoina(str,trim_quotes(s,&i,'\"'));
            str = tmp;
        }
		else
		{
			printf("1\n");
			tmp =ft_strjoina(str,trim_quotes(s,&i,'0'));
			str = tmp;
		}
		if (s[i])
        	i++;
    }
    return(str);
   
}


int main()
{
    printf("   s : %s\n",skip_quot_exp("val"));
    return 0;
}


