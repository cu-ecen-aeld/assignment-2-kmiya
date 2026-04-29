#!/bin/env bash
set -euo pipefail

if [ ! $# -eq 2 ]; then
    echo "Usage: $0 write_file write_str" >&2
    exit 1
fi

writefile="$1"
writestr="$2"

# check if writefile is absolute path
if [[ "$writefile" != /* ]]; then
    echo "Error: write_file must be an absolute path" >&2
    exit 1
fi

parent_dir="$(dirname "$writefile")"
if ! mkdir -p "$parent_dir"; then
    echo "Error: cannot create directory '$parent_dir'" >&2
    exit 1
fi

if ! printf '%s\n' "$writestr" > "$writefile"; then
    echo "Error: cannot write to '$writefile'" >&2
    exit 1
fi
