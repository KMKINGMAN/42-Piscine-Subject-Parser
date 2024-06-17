#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poppler/glib/poppler.h>
#include <glib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>

void create_directories(const char *path) {
    char tmp[PATH_MAX];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);
    if (tmp[len - 1] == '/')
        tmp[len - 1] = '\0';

    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(tmp, S_IRWXU) != 0 && errno != EEXIST) {
                fprintf(stderr, "Error creating directory: %s\n", tmp);
                perror("mkdir");
                return;
            }
            *p = '/'; 
        }
    }

    if (mkdir(tmp, S_IRWXU) != 0 && errno != EEXIST) {
        fprintf(stderr, "Error creating directory: %s\n", tmp);
        perror("mkdir");
    }
}

char* extract_text_from_pdf(const char* pdf_path) {
    GError *error = NULL;
    PopplerDocument *document = poppler_document_new_from_file(pdf_path, NULL, &error);
    if (error) {
        fprintf(stderr, "Error opening PDF file: %s\n", error->message);
        g_error_free(error);
        return NULL;
    }

    int num_pages = poppler_document_get_n_pages(document);
    GString *text = g_string_new("");

    for (int i = 0; i < num_pages; i++) {
        PopplerPage *page = poppler_document_get_page(document, i);
        char *page_text = poppler_page_get_text(page);
        g_string_append(text, page_text);
        g_free(page_text);
        g_object_unref(page);
    }

    g_object_unref(document);
    return g_string_free(text, FALSE);
}

void process_pdf(const char *pdf_path) {
    char *text = extract_text_from_pdf(pdf_path);
    if (!text) {
        return;
    }
    char name[3];
    char chapter_prefix[4] = {'C'};
    char *turn_in_dir = NULL;
    char *files_to_turn_in = NULL;
    int d = 0;

    char *line = strtok(text, "\n");
    while (line) {
        printf("Processing line: %s\n", line);

        if ((strstr(line, "C 0") || strstr(line, "C 1")) && !d) {
            sscanf(line, "C %s", name);
            strcat(chapter_prefix, name);
            printf("Chapter prefix: %s\n", chapter_prefix);
            d = 1;
        }
        if (strstr(line, "Turn-in directory")) {
            turn_in_dir = strchr(line, ':') + 2;
            printf("Turn-in directory: %s\n", turn_in_dir);
        }
        if (strstr(line, "Files to turn in")) {
            files_to_turn_in = strchr(line, ':') + 2;
            printf("Files to turn in: %s\n", files_to_turn_in);
        }
        if (chapter_prefix[0] != '\0' && turn_in_dir && files_to_turn_in) {
            char full_dir_path[256];
            snprintf(full_dir_path, sizeof(full_dir_path), "%s/%s", chapter_prefix, turn_in_dir);
            printf("Creating directory: %s\n", full_dir_path);
            create_directories(full_dir_path);

            char full_file_path[256];
            snprintf(full_file_path, sizeof(full_file_path), "%s/%s", full_dir_path, files_to_turn_in);
            printf("Creating file: %s\n", full_file_path);
            FILE *file = fopen(full_file_path, "w");
            if (file) {
                fclose(file);
            } else {
                perror("Error creating file");
                return;
            }

            turn_in_dir = NULL;
            files_to_turn_in = NULL;
        }
        line = strtok(NULL, "\n");
    }

    free(text);
}

int main(int argc, char *argv[]) {
        if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file_path>\n", argv[0]);
        return 1;
    }

    char pdf_path[PATH_MAX];
    realpath(argv[1], pdf_path);
    char file_uri[PATH_MAX + 7];
    snprintf(file_uri, sizeof(file_uri), "file://%s", pdf_path);

    printf("PDF Path: %s\n", pdf_path);
    printf("File URI: %s\n", file_uri);

    process_pdf(file_uri);
    printf("Directories and files created successfully.\n");
    return 0;
}
