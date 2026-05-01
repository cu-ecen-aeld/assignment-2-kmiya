#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

static void log_error(const char* msg) {
  syslog(LOG_ERR, "%s", msg);
  fprintf(stderr, "Error: %s\n", msg);  // NOLINT(cert-err33-c)
}

static void safe_fclose(FILE* fp) {
  if (fp == NULL) {
    return;
  }
  if (fclose(fp) != 0) {
    syslog(LOG_ERR, "Fail to close file");
  }
}

int main(int argc, char** argv) {
  openlog(NULL, 0, LOG_USER);

  if (argc != 3) {
    // NOLINTNEXTLINE(cert-err33-c)
    fprintf(stderr, "Usage: %s write_file write_str\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char* write_file_path = argv[1];
  const char* write_str = argv[2];

  FILE* write_file = NULL;
  int ret = EXIT_FAILURE;

  write_file = fopen(write_file_path, "w");
  if (!write_file) {
    log_error("Cannot open file");
    goto cleanup;
  }

  syslog(LOG_DEBUG, "Writing %s to %s", write_str, write_file_path);
  fprintf(write_file, "%s\n", write_str);  // NOLINT(cert-err33-c)

  ret = EXIT_SUCCESS;

cleanup:
  safe_fclose(write_file);
  closelog();
  return ret;
}
