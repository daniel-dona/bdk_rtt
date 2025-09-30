#! /bin/bash
# Usage: format_code.sh [directory] [--check]
# Formats C/C++ source code using clang-format
# If --check is specified, only checks formatting without making changes
# Works from both project root and subdirectories

# Get the script directory and project root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"

# Source build include if available
if [ -f "$SCRIPT_DIR/build_include.sh" ]; then
    source "$SCRIPT_DIR/build_include.sh"
fi

CHECK_ONLY=false
TARGET_DIR="."

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --check)
            CHECK_ONLY=true
            shift
            ;;
        *)
            TARGET_DIR="$1"
            shift
            ;;
    esac
done

# Resolve target directory relative to project root
if [ "$TARGET_DIR" = "." ]; then
    TARGET_DIR="$PROJECT_ROOT"
else
    TARGET_DIR="$(cd "$PROJECT_ROOT" && cd "$TARGET_DIR" && pwd)"
fi

# Validate target directory exists
if [ ! -d "$TARGET_DIR" ]; then
    echo "Error: Directory '$TARGET_DIR' does not exist"
    exit 1
fi

# Check if .clang-format exists in project root
if [ ! -f "$PROJECT_ROOT/.clang-format" ]; then
    echo "Error: .clang-format file not found in project root ($PROJECT_ROOT)"
    echo "Please ensure you're running this script from within the BDK RTT project"
    exit 1
fi

# Check if clang-format is available
if ! command -v clang-format &> /dev/null; then
    echo "Error: clang-format is not installed or not in PATH"
    echo "Please install clang-format to use code formatting"
    exit 1
fi

# Find all C/C++ source files
echo "Finding C/C++ source files in $TARGET_DIR..."
FILES=$(find "$TARGET_DIR" -type f \( -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.hpp" \) \
    ! -path "*/build/*" \
    ! -path "*/output/*" \
    ! -path "*/libs/*" \
    ! -path "*/.git/*")

if [ -z "$FILES" ]; then
    echo "No C/C++ source files found in $TARGET_DIR"
    exit 0
fi

echo "Found $(echo "$FILES" | wc -l) files to format"

if [ "$CHECK_ONLY" = true ]; then
    echo "Checking code formatting..."
    HAS_ERRORS=false
    for file in $FILES; do
        clang-format --dry-run --Werror "$file" >/dev/null 2>&1
        if [ $? -ne 0 ]; then
            echo "✗ $file needs formatting"
            HAS_ERRORS=true
        fi
    done
    
    if [ "$HAS_ERRORS" = false ]; then
        echo "✓ All files are properly formatted"
        exit 0
    else
        echo "✗ Some files need formatting. Run without --check to fix."
        exit 1
    fi
else
    echo "Formatting code..."
    FORMATTED_COUNT=0
    for file in $FILES; do
        #clang-format -i "$file"
        timeout 10s clang-format -i "$file"
    
        if [ $? -eq 124 ]; then
            echo "TIMEOUT: $file took too long, skipping..."
        fi

        if [ $? -eq 0 ]; then
            FORMATTED_COUNT=$((FORMATTED_COUNT + 1))
        fi
    done
    
    echo "✓ Code formatting completed successfully ($FORMATTED_COUNT files formatted)"
    exit 0
fi