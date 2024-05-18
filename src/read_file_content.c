char *read_file_content(char *file_path)
{
    char    *line;
    char    *file_content;
    int     fd;
    char    *to_free;

    fd = open(file_path , O_RDONLY);
    if (fd < 0)
        perror("error reading file");
    line = get_next_line(fd);
    file_content = ft_strdup("");
    while(line)
    {
        to_free = file_content;
        file_content = ft_strjoin(file_content , line); 
        free(to_free);
        free(line);
        line = get_next_line(fd);
    }
    return file_content; 
}