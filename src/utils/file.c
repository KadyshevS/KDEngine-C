#include <utils/file.h>
#include <utils/logging.h>
#include <stb.h>

#include <stdio.h>
#include <stdlib.h>

char* file_to_str(const char* filename) 
{
    FILE *file = fopen(filename, "rb");
    if (!file) 
    {
        kdLog("Error: Failed to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) 
    {
        kdLog("Error: Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead < fileSize) 
    {
        if (feof(file)) 
        {
            kdLog("Error: End of file reached before expected size\n");
        } 
        else if (ferror(file)) 
        {
            kdLog("Error: Failed to read file");
        }

        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[fileSize] = '\0';
    fclose(file);

    return buffer;
}

kd_image* load_image(const char* filename)
{
    kd_image* img = malloc(sizeof(kd_image));
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, STBI_rgb_alpha);

    return img;
}
void free_image(kd_image* img)
{
    stbi_image_free(img->data);
    free(img);
}