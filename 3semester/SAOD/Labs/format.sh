#!/bin/bash

excluded_dirs=("build" "vcpkg_installed")

files=()
while IFS= read -r -d $'\0' file; do
    files+=("$file")
done < <(find . -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -print0 | \
    grep -zZvE "$(IFS='|'; echo "${excluded_dirs[*]/#/.*\/}")")

format_file() {
    local file="$1"
    if clang-format -i "$file"; then
        echo "Formatted: $file"
    else
        echo "Failed to format: $file" >&2
    fi
}

export -f format_file

num_cores=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

printf '%s\0' "${files[@]}" | xargs -0 -P "$num_cores" -I {} bash -c 'format_file "$@"' _ {}

echo "Formatting complete!"